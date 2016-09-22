#include "gtest/gtest.h"
#include "Netflix.h"

// data_cache_test.c++
// Unit tests for DataCache


using namespace std;

class DataCacheTest : public ::testing::Test {
protected:
  DataCacheTest() : c() {}

  virtual void SetUp() {
    c.set_customer(1, 1.0f, 1.0f);
    c.set_customer(2, 2.0f, 2.0f);
    c.set_customer(3, 3.0f, 3.0f);
    c.set_customer(4, 4.0f, 4.0f);
    c.set_customer(5, 5.0f, 5.0f);
    c.set_customer(6, 6.0f, 6.0f);
    c.set_movie(1, 1.0f, 1.0f);
    c.set_movie(2, 2.0f, 2.0f);
    c.set_movie(3, 3.0f, 3.0f);
    c.set_movie(4, 4.0f, 4.0f);
    c.set_movie(5, 5.0f, 5.0f);
    c.set_movie(6, 6.0f, 6.0f);
  }

  DataCache c;
};

TEST_F(DataCacheTest, GetCustomerOne) {
  auto& cust = c.get_customer(1);
  EXPECT_EQ(1.0f, cust.rating_avg);
  EXPECT_EQ(1.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerTwo) {
  auto& cust = c.get_customer(2);
  EXPECT_EQ(2.0f, cust.rating_avg);
  EXPECT_EQ(2.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerThree) {
  auto& cust = c.get_customer(3);
  EXPECT_EQ(3.0f, cust.rating_avg);
  EXPECT_EQ(3.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerFour) {
  auto& cust = c.get_customer(4);
  EXPECT_EQ(4.0f, cust.rating_avg);
  EXPECT_EQ(4.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerFive) {
  auto& cust = c.get_customer(5);
  EXPECT_EQ(5.0f, cust.rating_avg);
  EXPECT_EQ(5.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerSix) {
  auto& cust = c.get_customer(6);
  EXPECT_EQ(6.0f, cust.rating_avg);
  EXPECT_EQ(6.0f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieOne) {
  auto& movie = c.get_movie(1);
  EXPECT_EQ(1.0f, movie.rating_avg);
  EXPECT_EQ(1.0f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieTwo) {
  auto& movie = c.get_movie(2);
  EXPECT_EQ(2.0f, movie.rating_avg);
  EXPECT_EQ(2.0f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieThree) {
  auto& movie = c.get_movie(3);
  EXPECT_EQ(3.0f, movie.rating_avg);
  EXPECT_EQ(3.0f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieFour) {
  auto& movie = c.get_movie(4);
  EXPECT_EQ(4.0f, movie.rating_avg);
  EXPECT_EQ(4.0f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieFive) {
  auto& movie = c.get_movie(5);
  EXPECT_EQ(5.0f, movie.rating_avg);
  EXPECT_EQ(5.0f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieSix) {
  auto& movie = c.get_movie(6);
  EXPECT_EQ(6.0f, movie.rating_avg);
  EXPECT_EQ(6.0f, movie.rating_stdev);
}
// truth_cache_test.c++
// Unit tests for predict


using namespace std;

class TruthCacheTest : public ::testing::Test {
protected:
  TruthCacheTest() : c() {}

  virtual void SetUp() {
    map<uint32_t, uint32_t> movie1_ratings;
    map<uint32_t, uint32_t> movie2_ratings;

    movie1_ratings[1] = 1;
    movie1_ratings[2] = 2;
    movie1_ratings[3] = 3;

    movie2_ratings[4] = 4;
    movie2_ratings[5] = 5;
    movie2_ratings[6] = 6;

    c.set_ratings(1, movie1_ratings);
    c.set_ratings(2, movie2_ratings);
  }

  TruthCache c;
};

TEST_F(TruthCacheTest, GetMovie1Rating1) {
  uint32_t rating = c.get_rating(1, 1);
  ASSERT_EQ(1, rating);
}

TEST_F(TruthCacheTest, GetMovie1Rating2) {
  uint32_t rating = c.get_rating(2, 1);
  ASSERT_EQ(2, rating);
}

TEST_F(TruthCacheTest, GetMovie1Rating3) {
  uint32_t rating = c.get_rating(3, 1);
  ASSERT_EQ(3, rating);
}

TEST_F(TruthCacheTest, GetMovie2Rating4) {
  uint32_t rating = c.get_rating(4, 2);
  ASSERT_EQ(4, rating);
}

TEST_F(TruthCacheTest, GetMovie2Rating5) {
  uint32_t rating = c.get_rating(5, 2);
  ASSERT_EQ(5, rating);
}

TEST_F(TruthCacheTest, GetMovie2Rating6) {
  uint32_t rating = c.get_rating(6, 2);
  ASSERT_EQ(6, rating);
}
// predict_test.c++
// Unit tests for predict


using namespace std;

class DataMock : public ::testing::Test {
protected:
  DataMock() : c(), p(c) {
    c.set_customer(1, 1.0f, 1.0f);
    c.set_customer(2, 2.0f, 2.0f);
    c.set_customer(3, 3.0f, 3.0f);
    c.set_customer(4, 4.0f, 4.0f);
    c.set_customer(5, 5.0f, 5.0f);
    c.set_customer(6, 6.0f, 6.0f);
    c.set_movie(1, 1.0f, 1.0f);
    c.set_movie(2, 2.0f, 2.0f);
    c.set_movie(3, 3.0f, 3.0f);
    c.set_movie(4, 4.0f, 4.0f);
    c.set_movie(5, 5.0f, 5.0f);
    c.set_movie(6, 6.0f, 6.0f);
  }

  virtual void SetUp() {
    p = Predictor(c);
  }

  DataCache c;
  Predictor p;
};

class TruthMock : public ::testing::Test {
protected:
  TruthMock() : c(), v(c) {}

  virtual void SetUp() {
    map<uint32_t, uint32_t> movie1_ratings;
    map<uint32_t, uint32_t> movie2_ratings;

    movie1_ratings[1] = 1;
    movie1_ratings[2] = 2;
    movie1_ratings[3] = 3;

    movie2_ratings[4] = 4;
    movie2_ratings[5] = 5;
    movie2_ratings[6] = 6;

    c.set_ratings(1, movie1_ratings);
    c.set_ratings(2, movie2_ratings);  

    v = Verifier(c);
  }

  TruthCache c;
  Verifier v;
};

/*
  DataMock tests
*/
TEST_F(DataMock, PredictCustomerOne) {
  EXPECT_EQ(2.0f, p.predict(1, 1));
}

TEST_F(DataMock, PredictCustomerTwo) {
  EXPECT_EQ(6.0f, p.predict(2, 2));
}

TEST_F(DataMock, PredictCustomerThree) {
  EXPECT_EQ(12.0f, p.predict(3, 3));
}

TEST_F(DataMock, PredictCustomerFour) {
  EXPECT_EQ(20.0f, p.predict(4, 4));
}

TEST_F(DataMock, PredictCustomerFive) {
  EXPECT_EQ(30.0f, p.predict(5, 5));
}

TEST_F(DataMock, PredictCustomerSix) {
  EXPECT_EQ(42.0f, p.predict(6, 6));
}

TEST_F(DataMock, PredictCustomerOneAlt) {
  EXPECT_EQ(3.0f, p.predict(1, 2));
}

TEST_F(DataMock, PredictCustomerTwoAlt) {
  EXPECT_EQ(8.0f, p.predict(2, 3));
}

TEST_F(DataMock, PredictCustomerThreeAlt) {
  EXPECT_EQ(15.0f, p.predict(3, 4));
}

TEST_F(DataMock, PredictCustomerFourAlt) {
  EXPECT_EQ(24.0f, p.predict(4, 5));
}

/*
  TruthMock tests
*/

TEST_F(TruthMock, RMSE11) {
  v.add_prediction(1, 1, 2.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE12) {
  v.add_prediction(2, 1, 2.0f);
  ASSERT_EQ(0.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE112) {
  v.add_prediction(2, 1, 2.0f);
  v.add_prediction(1, 1, 1.0f);
  ASSERT_EQ(0.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE1123) {
  v.add_prediction(1, 1, 0.0f);
  v.add_prediction(2, 1, 1.0f);
  v.add_prediction(3, 1, 4.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE123) {
  v.add_prediction(2, 1, 3.0f);
  v.add_prediction(3, 1, 2.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE24) {
  v.add_prediction(4, 2, 2.0f);
  ASSERT_EQ(2.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE25) {
  v.add_prediction(5, 2, 7.0f);
  ASSERT_EQ(2.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE245) {
  v.add_prediction(4, 2, 3.0f);
  v.add_prediction(5, 2, 4.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE2456) {
  v.add_prediction(4, 2, 3.0f);
  v.add_prediction(5, 2, 4.0f);
  v.add_prediction(6, 2, 5.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE256) {
  v.add_prediction(5, 2, 4.0f);
  v.add_prediction(6, 2, 5.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}

TEST_F(TruthMock, RMSE123456) {
  v.add_prediction(1, 1, 0.0f);
  v.add_prediction(2, 1, 1.0f);
  v.add_prediction(3, 1, 4.0f);
  v.add_prediction(4, 2, 3.0f);
  v.add_prediction(5, 2, 4.0f);
  v.add_prediction(6, 2, 5.0f);
  ASSERT_EQ(1.0f, v.get_rmse());
}
// solve_test.c++
// Unit tests for solve


using namespace std;

