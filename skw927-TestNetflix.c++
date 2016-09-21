#include "Netflix.h"

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

using namespace std;

class ConstModel : public Model {
  int c;

public:
  ConstModel(int c) : c(c) {}
  virtual double predict(unsigned int user, unsigned int movie) {
    return this->c;
  }
};

TEST(NetflixTest, run) {
  istringstream r("1:\n1\n2\n5\n7\n");
  ostringstream w;
  istringstream ans("1 1 3\n1 2 3\n1 5 3\n1 7 3\n");

  ConstModel model(2);
  run(r, w, ans, &model);
  ASSERT_EQ("1:\n2.0\n2.0\n2.0\n2.0\nRMSE: 1.00\n", w.str());
}

TEST(NetflixTest, run_stats) {
  istringstream r("1:\n1\n2\n5\n7\n");
  ostringstream w;
  istringstream ans("1 1 3\n1 2 3\n1 5 3\n1 7 3\n");

  istringstream users("1 0\n2 1\n5 -0.3\n7 0.2");
  istringstream movies("1 4.0 1.0\n");
  StatsModel model(users, movies);
  run(r, w, ans, &model);
  ASSERT_EQ("1:\n4.0\n5.0\n3.7\n4.2\nRMSE: 1.32\n", w.str());
}

TEST(NetflixTest, run_empty) {
  istringstream r;
  ostringstream w;
  istringstream ans("1 1 3\n1 2 3\n1 5 3\n1 7 3\n");

  ConstModel model(2);
  run(r, w, ans, &model);
  ASSERT_EQ("RMSE: N/A\n", w.str());
}

TEST(NetflixTest, answerModel_constructor) {
  istringstream r("1 1 1\n2 2 2\n3 4 5\n");
  AnswerModel model(r);
  ASSERT_EQ(1, model.answers["1:1"]);
  ASSERT_EQ(2, model.answers["2:2"]);
  ASSERT_EQ(5, model.answers["3:4"]);
}

TEST(NetflixTest, answerModel) {
  istringstream r("1 1 1\n2 2 2\n3 4 5\n");
  AnswerModel model(r);
  ASSERT_EQ(1, model.predict(1, 1));
  ASSERT_EQ(5, model.predict(4, 3));
}

TEST(NetflixTest, answerModel_empty) {
  istringstream r("1 1 1\n");
  AnswerModel model(r);
  ASSERT_EQ(-1, model.predict(5, 5));
}

TEST(NetflixTest, statsModel_constructor) {
  istringstream users("1 0\n");
  istringstream movies("1 4.0 1.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(0, model.userNorm[1]);
  ASSERT_EQ(4.0, model.movieAvg[1]);
  ASSERT_EQ(1.0, model.movieStd[1]);
  ASSERT_EQ(3.0, model.movieAvg[2]);
  ASSERT_EQ(0.5, model.movieStd[2]);
}

TEST(NetflixTest, statsModel_1) {
  istringstream users("1 0\n");
  istringstream movies("1 4.0 1.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(4.0, model.predict(1, 1));
  ASSERT_EQ(3.0, model.predict(1, 2));
}

TEST(NetflixTest, statsModel_2) {
  istringstream users("1 1\n2 -1\n");
  istringstream movies("1 4.0 0.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(4.0, model.predict(1, 1));
  ASSERT_EQ(4.0, model.predict(2, 1));
  ASSERT_EQ(3.5, model.predict(1, 2));
  ASSERT_EQ(2.5, model.predict(2, 2));
}

TEST(NetflixTest, statsModel_3) {
  istringstream users("1 0.1\n");
  istringstream movies("1 4.0 1.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(4.1, model.predict(1, 1));
  ASSERT_EQ(3.05, model.predict(1, 2));
}

TEST(NetflixTest, statsModel_empty_1) {
  istringstream users("1 0\n");
  istringstream movies("1 4.0 1.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(-1, model.predict(1, 3));
}

TEST(NetflixTest, statsModel_empty_2) {
  istringstream users("1 0\n");
  istringstream movies("1 4.0 1.0\n 2 3.0 0.5\n");
  StatsModel model(users, movies);
  ASSERT_EQ(-1, model.predict(2, 1));
}