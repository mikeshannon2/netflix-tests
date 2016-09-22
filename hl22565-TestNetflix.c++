#include <sstream> // istringtstream, ostringstream

#include "Netflix.h"
#include "gtest/gtest.h"

using namespace std;

TEST(NetflixFixture, trunc_1) {
  const double v = netflix_truncate(2.33333333, 1);
  ASSERT_EQ((double)2.3, v);
}

TEST(NetflixFixture, trunc_2) {
  const double v = netflix_truncate(1.0011, 1);
  ASSERT_EQ((double)1.0, v);
}

TEST(NetflixFixture, trunc_3) {
  const double v = netflix_truncate(3.45, 1);
  ASSERT_EQ((double)3.4, v);
}

TEST(NetflixFixture, trunc_4) {
  const double v = netflix_truncate(1.3402578375, 1);
  ASSERT_EQ((double)1.3, v);
}

TEST(NetflixFixture, trunc_5) {
  const double v = netflix_truncate(0.000, 1);
  ASSERT_EQ((double)0.0, v);
}

TEST(NetflixFixture, trunc_6) {
  const double v = netflix_truncate(0.9999999999, 2);
  ASSERT_EQ((double)0.99, v);
}

TEST(NetflixFixture, predict_1) {
  movie_avgs[5] = 3.7;
  user_avgs[2] = 3.7;
  const double v = predict(5, 2);
  ASSERT_EQ((double)3.7, v);
}

TEST(NetflixFixture, predict_2) {
  movie_avgs[8] = 4.0;
  user_avgs[10] = 3.8;
  const double v = predict(8, 10);
  ASSERT_EQ((double)4.1, v);
}

TEST(NetflixFixture, predict_3) {
  movie_avgs[8] = 0.5;
  user_avgs[10] = 0.2;
  const double v = predict(8, 10);
  ASSERT_EQ((double)1.0, v);
}

TEST(NetflixFixture, predict_4) {
  movie_avgs[8] = 5.0;
  user_avgs[10] = 5.0;
  const double v = predict(8, 10);
  ASSERT_EQ((double)5.0, v);
}

TEST(NetflixFixture, run_1) {
  movie_avgs[8] = 3.5;
  movie_avgs[9] = 3.5;
  user_avgs[1] = 3.0;
  user_avgs[2] = 3.0;
  user_avgs[3] = 3.0;
  user_avgs[4] = 3.0;
  actual_ratings[8][1] = 2;
  actual_ratings[8][2] = 3;
  actual_ratings[9][3] = 4;
  actual_ratings[9][4] = 5;
  istringstream r("8:\n1\n2\n9:\n3\n4");
  ostringstream w;
  run(r, w);

  ASSERT_EQ("8:\n2.8\n2.8\n9:\n2.8\n2.8\nRMSE: 1.31\n", w.str());
}

TEST(NetflixFixture, run_2) {
  movie_avgs[10] = 1.0;
  movie_avgs[11] = 1.0;
  user_avgs[5] = 1.0;
  user_avgs[6] = 1.0;
  user_avgs[7] = 1.0;
  user_avgs[8] = 1.0;
  actual_ratings[10][5] = 1;
  actual_ratings[10][6] = 1;
  actual_ratings[11][7] = 5;
  actual_ratings[11][8] = 5;
  istringstream r("10:\n5\n6\n11:\n7\n8");
  ostringstream w;
  run(r, w);

  ASSERT_EQ("10:\n1\n1\n11:\n1\n1\nRMSE: 2.82\n", w.str());
}

TEST(NetflixFixture, run_3) {
  movie_avgs[12] = 1.3;
  movie_avgs[13] = 4.4;
  user_avgs[9] = 1.8;
  user_avgs[10] = 2.4;
  user_avgs[11] = 5.0;
  user_avgs[12] = 3.3;
  actual_ratings[8][1] = 2;
  actual_ratings[8][2] = 3;
  actual_ratings[9][3] = 1;
  actual_ratings[9][4] = 1;
  istringstream r("12:\n9\n10\n13:\n11\n12");
  ostringstream w;
  run(r, w);

  ASSERT_EQ("12:\n1\n1\n13:\n5\n4\nRMSE: 3.27\n", w.str());
}

TEST(NetflixFixture, populate_cache) { populateCache(1); }
