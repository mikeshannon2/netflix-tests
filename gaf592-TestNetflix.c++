/** \file TestNetflix.c++
 * File that runs the unit tests for the netflix program
 */

// --------
// includes
// --------

#include <cmath> // abs, pow, sqrt
#include <map>
#include <string> // string, to_string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------
// fixtures
// --------

/**
 * @brief Fixture that populates caches with mock data
 */
class NetflixFixture : public ::testing::Test {
protected:
  map<customer_id_t, movie_rating_t> test_customer_cache = {
      {0, RATING_AVERAGE}, // Used by basic tests
      {1, 1.3},
      {2, 2.0},
      {3, 4.5}};

  map<movie_id_t, movie_rating_t> test_movie_cache = {
      {0, RATING_AVERAGE}, // Used by basic tests
      {1, 3.1},
      {2, 1.3},
      {3, 3.0}};

  // Leaving this empty since it is never accessed from unit tests
  TruthCache truth_cache;

  virtual void SetUp() {
    load_caches(&test_customer_cache, &test_movie_cache, &truth_cache);
  }
};

// -------
// helpers
// -------

/**
 * @brief Helper function that checks if number precision is correct
 * @param num The number to be checked
 * @param precision The desired precision
 * @return True if the actual precision is less than the desired precision
 */
template <typename T> bool is_precision_correct(T num, unsigned int precision) {
  string num_str = to_string(num);

  size_t index_of_period = num_str.find('.');

  // No decimal point was found, so precision must be correct
  if (index_of_period == string::npos)
    return true;

  // Needed b/c to_string adds zeroes to the end
  size_t index_of_last_significant_digit = num_str.find_last_not_of('0');
  size_t num_digits_after_period =
      index_of_last_significant_digit - index_of_period - 1;

  return (num_digits_after_period <= precision);
}

// -----
// tests
// -----

TEST_F(NetflixFixture, test_predict_rating_basic) {
  movie_id_t m_id = 0;
  customer_id_t c_id = 0;

  movie_rating_t prediction = predict_rating(m_id, c_id);

  ASSERT_DOUBLE_EQ(RATING_AVERAGE, prediction);
  ASSERT_TRUE(is_precision_correct(prediction, MOVIE_RATING_PRECISION));
}

TEST_F(NetflixFixture, test_predict_rating_logic) {
  movie_id_t m_id = 1;
  customer_id_t c_id = 1;

  movie_rating_t m_offset = test_movie_cache[m_id] - RATING_AVERAGE;
  movie_rating_t c_offset = test_customer_cache[c_id] - RATING_AVERAGE;

  movie_rating_t prediction = predict_rating(m_id, c_id);

  // Check that the prediction logic is working correctly
  ASSERT_DOUBLE_EQ(RATING_AVERAGE + m_offset + c_offset, prediction);
}

TEST_F(NetflixFixture, test_predict_rating_precision) {
  movie_id_t m_id = 2;
  movie_id_t c_id = 2;

  movie_rating_t prediction = predict_rating(m_id, c_id);

  ASSERT_TRUE(is_precision_correct(prediction, MOVIE_RATING_PRECISION));
}

TEST_F(NetflixFixture, test_populate_predictions_basic) {
  movie_customer_ratings_store_t predictions;
  vector<customer_id_t> customer_ids;
  movie_id_t m_id = 1;
  customer_ids.push_back(1);
  customer_ids.push_back(2);

  populate_predictions(m_id, customer_ids, predictions);
  ASSERT_DOUBLE_EQ(predictions[1][1], .7);
  ASSERT_DOUBLE_EQ(predictions[1][2], 1.4);
}

TEST_F(NetflixFixture, test_populate_predictions_empty) {
  movie_customer_ratings_store_t predictions;
  vector<customer_id_t> customer_ids;
  movie_id_t m_id = 1;

  populate_predictions(m_id, customer_ids, predictions);

  ASSERT_EQ(predictions.size(), 0);
}

TEST_F(NetflixFixture, test_populate_predictions_precision) {
  movie_customer_ratings_store_t predictions;
  vector<customer_id_t> customer_ids;
  movie_id_t m_id = 1;
  customer_ids.push_back(1);
  customer_ids.push_back(2);

  populate_predictions(m_id, customer_ids, predictions);
  ASSERT_TRUE(is_precision_correct(predictions[1][1], MOVIE_RATING_PRECISION));
  ASSERT_TRUE(is_precision_correct(predictions[1][2], MOVIE_RATING_PRECISION));
}

TEST_F(NetflixFixture, test_calculate_rmse_basic) {
  movie_id_t m_id = 666;
  customer_id_t c_id = 4;
  movie_rating_t actual_rating = 2;
  movie_rating_t prediction = RATING_AVERAGE;

  // Manually store prediction
  movie_customer_ratings_store_t prediction_store;
  prediction_store[m_id][c_id] = prediction;

  rmse_t actual_rmse = abs(actual_rating - prediction);

  actual_movie_customer_ratings_store_t actual_store;
  actual_store[m_id][c_id] = actual_rating;

  rmse_t rmse = calculate_rmse(prediction_store, &actual_store);

  ASSERT_TRUE(is_precision_correct(rmse, RMSE_RATING_PRECISION));
  ASSERT_DOUBLE_EQ(actual_rmse, rmse);
}

TEST_F(NetflixFixture, test_calculate_rmse_logic) {
  movie_id_t m_id = 3;
  customer_id_t f_c_id = 2;
  customer_id_t s_c_id = 2;
  movie_rating_t actual_rating = 2;

  movie_customer_ratings_store_t prediction_store;
  prediction_store[m_id][f_c_id] = 3.4;
  prediction_store[m_id][s_c_id] = 2.5;

  // Calculate the expected rmse
  rmse_t actual_rmse = 0;
  actual_rmse += pow(actual_rating - prediction_store[m_id][f_c_id], 2);
  actual_rmse += pow(actual_rating - prediction_store[m_id][s_c_id], 2);
  actual_rmse = sqrt(actual_rmse / 2);

  actual_movie_customer_ratings_store_t actual_store;
  actual_store[m_id][f_c_id] = actual_rating;
  actual_store[m_id][s_c_id] = actual_rating;

  rmse_t rmse = calculate_rmse(prediction_store, &actual_store);

  ASSERT_TRUE(is_precision_correct(rmse, RMSE_RATING_PRECISION));
  ASSERT_DOUBLE_EQ(actual_rmse, rmse);
}

TEST_F(NetflixFixture, test_calculate_rmse_edge) {
  // Leave these two empty
  movie_customer_ratings_store_t prediction_store;
  actual_movie_customer_ratings_store_t actual_store;

  // Pass in empty data structures
  rmse_t rmse = calculate_rmse(prediction_store, &actual_store);

  ASSERT_DOUBLE_EQ(0, rmse);
}
