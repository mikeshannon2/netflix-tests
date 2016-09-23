// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>   // vector/list

#include "gtest/gtest.h"

#include "Netflix.h"

#define TRUNC_VAL 100

using namespace std;

extern vector<double> errors_squared;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("1:\n30878\n");
  int movie_id;
  vector<int> user_ids;
  const bool b = netflix_read(r, movie_id, user_ids);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, movie_id);
  ASSERT_EQ(1, user_ids.size());
}

TEST(NetflixFixture, read_2) {
  istringstream r("1:\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
  int movie_id;
  vector<int> user_ids;
  const bool b = netflix_read(r, movie_id, user_ids);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, movie_id);
  ASSERT_EQ(10, user_ids.size());
}

TEST(NetflixFixture, read_3) {
  istringstream r("1000:\n100\n200\n300\n400\n500");
  int movie_id;
  vector<int> user_ids;
  const bool b = netflix_read(r, movie_id, user_ids);
  ASSERT_TRUE(b);
  ASSERT_EQ(1000, movie_id);
  ASSERT_EQ(5, user_ids.size());
}

TEST(NetflixFixture, read_4) {
  istringstream r("69420:\n9000\n69\n420\n");
  int movie_id;
  vector<int> user_ids;
  const bool b = netflix_read(r, movie_id, user_ids);
  ASSERT_TRUE(b);
  ASSERT_EQ(69420, movie_id);
  ASSERT_EQ(3, user_ids.size());
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
  const int movie_id = 124;
  const vector<int> user_ids = {16, 18, 19, 43};
  const vector<double> result = netflix_eval(movie_id, user_ids);
  ASSERT_EQ(user_ids.size(), result.size());
}

TEST(NetflixFixture, eval_2) {
  const int movie_id = 404;
  const vector<int> user_ids = {69, 420, 8, 96, 9};
  const vector<double> result = netflix_eval(movie_id, user_ids);
  ASSERT_EQ(user_ids.size(), result.size());
}

TEST(NetflixFixture, eval_3) {
  const int movie_id = 1;
  const vector<int> user_ids = {1, 2, 3, 4, 5};
  const vector<double> result = netflix_eval(movie_id, user_ids);
  ASSERT_EQ(user_ids.size(), result.size());
}

TEST(NetflixFixture, eval_4) {
  const int movie_id = 9000;
  const vector<int> user_ids = {324, 4678, 234, 5789, 23467, 2, 27, 2341, 4};
  const vector<double> result = netflix_eval(movie_id, user_ids);
  ASSERT_EQ(user_ids.size(), result.size());
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  const int movie_id = 124;
  const vector<double> user_ratings = {3, 3, 3};
  netflix_print(w, movie_id, user_ratings);
  ASSERT_EQ("124:\n3\n3\n3\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  const int movie_id = 69420;
  const vector<double> user_ratings = {69, 420, 500};
  netflix_print(w, movie_id, user_ratings);
  ASSERT_EQ("69420:\n69\n420\n500\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  const int movie_id = 345;
  const vector<double> user_ratings = {5, 4, 2, 9, 4, 3, 0};
  netflix_print(w, movie_id, user_ratings);
  ASSERT_EQ("345:\n5\n4\n2\n9\n4\n3\n0\n", w.str());
}

TEST(NetflixFixture, print_4) {
  ostringstream w;
  const int movie_id = 9999;
  const vector<double> user_ratings = {1, 2, 3, 4, 5, 6, 7};
  netflix_print(w, movie_id, user_ratings);
  ASSERT_EQ("9999:\n1\n2\n3\n4\n5\n6\n7\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1618:\n432\n326\n7890\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1618:\n1\n1\n1\nRMSE: 1\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("1826:\n1\n2\n3\n4\n5\n200:\n1\n2\n3\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1826:\n1\n1\n1\n1\n1\n200:\n1\n1\n1\nRMSE: 1\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("69420:\n5\n4\n3\n2\n1\n404:\n3\n2\n1");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("69420:\n1\n1\n1\n1\n1\n404:\n1\n1\n1\nRMSE: 1\n", w.str());
}

TEST(NetflixFixture, solve_4) {
  istringstream r("300:\n7890\n326\n432\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("300:\n1\n1\n1\nRMSE: 1\n", w.str());
}

// ------------
// store_errors
// ------------

TEST(NetflixFixture, errors_1) {
  double actual_rating = 1.00;
  double predicted_rating = 1.00;
  double result = netflix_store_errors(actual_rating, predicted_rating);
  ASSERT_EQ(result, 0);
}

TEST(NetflixFixture, errors_2) {
  double actual_rating = 5.00;
  double predicted_rating = 4.00;
  double result = netflix_store_errors(actual_rating, predicted_rating);
  ASSERT_EQ(result, 1.00);
}

TEST(NetflixFixture, errors_3) {
  double actual_rating = 1.00;
  double predicted_rating = 0.5;
  double result = netflix_store_errors(actual_rating, predicted_rating);
  ASSERT_EQ(result, 0.25);
}

TEST(NetflixFixture, errors_4) {
  double actual_rating = 2.00;
  double predicted_rating = 4.00;
  double result = netflix_store_errors(actual_rating, predicted_rating);
  ASSERT_EQ(result, 4.00);
}

// --------------
// calculate_rmse
// --------------

TEST(NetflixFixture, rmse_1) {
  errors_squared.clear();
  netflix_store_errors(1.00, 1.00);
  netflix_store_errors(5.00, 4.00);
  netflix_store_errors(1.00, 0.5);
  netflix_store_errors(2.00, 4.00);
  double result = netflix_calculate_rmse();
  result = (double)((int)(result * TRUNC_VAL)) / TRUNC_VAL;
  ASSERT_EQ(result, 1.13);
}

TEST(NetflixFixture, rmse_2) {
  errors_squared.clear();
  netflix_store_errors(1.00, 1.00);
  netflix_store_errors(2.00, 2.00);
  netflix_store_errors(3.00, 3.00);
  netflix_store_errors(4.00, 4.00);
  double result = netflix_calculate_rmse();
  result = (double)((int)(result * TRUNC_VAL)) / TRUNC_VAL;
  ASSERT_EQ(result, 0);
}

TEST(NetflixFixture, rmse_3) {
  errors_squared.clear();
  netflix_store_errors(1.00, 2.00);
  netflix_store_errors(2.00, 3.00);
  netflix_store_errors(3.00, 4.00);
  double result = netflix_calculate_rmse();
  result = (double)((int)(result * TRUNC_VAL)) / TRUNC_VAL;
  ASSERT_EQ(result, 1.00);
}

TEST(NetflixFixture, rmse_4) {
  errors_squared.clear();
  netflix_store_errors(5.00, 4.00);
  netflix_store_errors(2.00, 4.20);
  netflix_store_errors(3.00, 0.5);
  double result = netflix_calculate_rmse();
  result = (double)((int)(result * TRUNC_VAL)) / TRUNC_VAL;
  ASSERT_EQ(result, 2.00);
}

// --------------
// get_prediction
// --------------

TEST(NetflixFixture, prediction_1) {
  double usr_average = 4.00;
  double movie_average = 4.00;
  double result = netflix_get_prediction(usr_average, movie_average);
  ASSERT_EQ(result, 4.30);
}

TEST(NetflixFixture, prediction_2) {
  double usr_average = 5.00;
  double movie_average = 4.00;
  double result = netflix_get_prediction(usr_average, movie_average);
  ASSERT_EQ(result, 5.00);
}

TEST(NetflixFixture, prediction_3) {
  double usr_average = 0.5;
  double movie_average = 1.00;
  double result = netflix_get_prediction(usr_average, movie_average);
  ASSERT_EQ(result, 1.00);
}
