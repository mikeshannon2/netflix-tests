#include <cmath>
#include <regex>
#include <sstream>
#include <sstream>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

class NetflixPredictorTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    stringstream actuals("1 123 3\n"
                         "1 234 5\n"
                         "1 345 2\n"
                         "1 14756 4\n"
                         "1 30878 4\n"
                         "1 317050 5\n"
                         "1 470861 5\n"
                         "1376 27822 5\n"
                         "1376 109127 5\n"
                         "1376 212424 5\n"
                         "1376 355278 5\n"
                         "2043 22537 4\n"
                         "2043 32229 4\n"
                         "2043 65883 2\n"
                         "2043 92970 4\n");
    stringstream movieAverage("1 3.234\n"
                              "1376 3.78866\n"
                              "2043 3.77766\n");
    stringstream customerDiff("123 0.123\n"
                              "234 -0.234\n"
                              "345 0.345\n"
                              "14756 0.03962\n"
                              "109127 0.00861\n"
                              "212424 1.18284\n"
                              "355278 -0.1406\n"
                              "22537 -0.19083\n"
                              "32229 0.37876\n"
                              "65883 0.00899\n"
                              "92970 0.72659\n"
                              "30878 0.02933\n"
                              "317050 0.04087\n"
                              "470861 0.85026\n"
                              "27822 0.2218\n");
    predictor = NetflixPredictor(actuals, movieAverage, customerDiff);
  }

  NetflixPredictor predictor;
};

bool compareFloats(float a, float b) { return abs(a - b) < .001; }

TEST(Netflix, compareFloats) { EXPECT_TRUE(compareFloats(1.0, 1.0)); }

TEST(Netflix, compareFloats_2) { EXPECT_FALSE(compareFloats(1.0, 2.0)); }

TEST(Netflix, compareFloats_3) { EXPECT_TRUE(compareFloats(1.0, 1.000000001)); }

TEST(Netflix, rmse) {
  EXPECT_EQ(0, calculateRMSE({1}, {1}));
  EXPECT_EQ(6, calculateRMSE({1}, {7}));
}

TEST(Netflix, rmse_2) {
  EXPECT_EQ(0, calculateRMSE({1, 1, 1}, {1, 1, 1}));
  EXPECT_EQ(1, calculateRMSE({1, 1, 1}, {2, 2, 2}));
  EXPECT_EQ(1, calculateRMSE({2, 2, 2}, {1, 1, 1}));
  EXPECT_EQ(3, calculateRMSE({1, 1, 1}, {4, 4, 4}));
  EXPECT_EQ(3, calculateRMSE({4, 4, 4}, {1, 1, 1}));
}

TEST(Netflix, rmse_3) {
  EXPECT_TRUE(
      compareFloats(sqrt(14.0 / 3.0), calculateRMSE({1, 1, 1}, {2, 3, 4})));
}

TEST_F(NetflixPredictorTest, solve_format) {
  istringstream input("1:\n123");
  stringstream output("");
  predictor.solve(input, output);

  string word;

  output >> word;
  EXPECT_EQ("1:", word);

  output >> word;
  EXPECT_TRUE(isdigit(word[0]));
  EXPECT_EQ(word[1], '.');
  EXPECT_TRUE(isdigit(word[2]));

  output >> word;
  EXPECT_EQ(word, "RMSE:");
  output >> word;
  EXPECT_TRUE(isdigit(word[0]));
  EXPECT_EQ(word[1], '.');
  EXPECT_TRUE(isdigit(word[2]));
  EXPECT_TRUE(isdigit(word[3]));
}

TEST_F(NetflixPredictorTest, solve_format_2) {
  istringstream input("1:\n123");
  stringstream output("");
  predictor.solve(input, output);

  string word;

  output >> word;
  EXPECT_EQ("1:", word);

  output >> word;
  EXPECT_EQ("3.4", word);

  output >> word;
  EXPECT_EQ(word, "RMSE:");

  output >> word;
  EXPECT_EQ("0.36", word);
}

TEST_F(NetflixPredictorTest, prediction) {
  int value = predictor.getPrediction(1, 123);
  EXPECT_TRUE(value >= 1.0);
  EXPECT_TRUE(value <= 5.0);
}

TEST_F(NetflixPredictorTest, prediction_2) {
  int value = predictor.getPrediction(1, 234);
  EXPECT_TRUE(value >= 1.0);
  EXPECT_TRUE(value <= 5.0);
}

TEST_F(NetflixPredictorTest, prediction_3) {
  int value = predictor.getPrediction(1, 345);
  EXPECT_TRUE(value >= 1.0);
  EXPECT_TRUE(value <= 5.0);
}

TEST_F(NetflixPredictorTest, prediction_rmse) {
  const int movieId = 2043;
  map<RatingId, float> predictions = {{{movieId, 22537}, 3.0},
                                      {{movieId, 32229}, 3.0},
                                      {{movieId, 65883}, 3.0},
                                      {{movieId, 92970}, 3.0}};
  EXPECT_EQ(1, predictor.calculatePredictionRMSE(predictions));
}

TEST_F(NetflixPredictorTest, prediction_rmse_2) {
  const int movieId = 1;
  map<RatingId, float> predictions = {{{movieId, 14756}, 3.0},
                                      {{movieId, 30878}, 3.0},
                                      {{movieId, 317050}, 3.0},
                                      {{movieId, 470861}, 3.0}};
  EXPECT_TRUE(compareFloats(sqrt(5.0 / 2.0),
                            predictor.calculatePredictionRMSE(predictions)));
}

TEST_F(NetflixPredictorTest, prediction_rmse_3) {
  const int movieId = 1376;
  map<RatingId, float> predictions = {{{movieId, 27822}, 3.0},
                                      {{movieId, 109127}, 3.0},
                                      {{movieId, 212424}, 3.0},
                                      {{movieId, 355278}, 3.0}};
  EXPECT_EQ(2, predictor.calculatePredictionRMSE(predictions));
}
