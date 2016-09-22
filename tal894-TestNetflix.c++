// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <list>
#include <sstream> // istringtstream, ostringstream
#include <string>  // string
#include <utility> // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, truncate_1) {
  double r = truncate_n_dig(5.123, 1);
  ASSERT_EQ(r, 5.1);
}

TEST(NetflixFixture, truncate_2) {
  double r = truncate_n_dig(3.1415926535, 3);
  ASSERT_EQ(r, 3.141);
}

TEST(NetflixFixture, truncate_3) {
  double r = truncate_n_dig(200.0, 0);
  ASSERT_EQ(r, 200.0);
}

TEST(NetflixFixture, truncate_4) {
  double r = truncate_n_dig(0.9999, 0);
  ASSERT_EQ(r, 0.0);
}

TEST(NetflixFixture, predict_1) {
  map<int, Movie> movies = {{1, Movie(1, 2000)}};
  map<int, Customer> customers = {{1, Customer(1)}};
  movies[1].average = 3.0;
  customers[1].average = 3.0;
  double r = predict(1, 1, 3.0, 3.0, movies, customers);
  ASSERT_EQ(r, 3.0);
}

TEST(NetflixFixture, predict_2) {
  map<int, Movie> movies = {{1, Movie(1, 2000)}};
  map<int, Customer> customers = {{1, Customer(1)}};
  movies[1].average = 3.0;
  customers[1].average = 3.1;
  double r = predict(1, 1, 3.0, 3.0, movies, customers);
  ASSERT_EQ(r, 3.1);
}

TEST(NetflixFixture, predict_3) {
  map<int, Movie> movies = {{1, Movie(1, 2000)}};
  map<int, Customer> customers = {{1, Customer(1)}};
  movies[1].average = 4.0;
  customers[1].average = 3.0;
  double r = predict(1, 1, 3.0, 3.0, movies, customers);
  ASSERT_EQ(r, 4.1);
}

TEST(NetflixFixture, average_data_1) {
  map<int, Movie> movies = {{1, Movie(1, 2000)}, {2, Movie(2, 2000)}};
  movies[1].average = 4.0;
  movies[2].average = 3.0;
  double r = average_data(movies);
  ASSERT_EQ(r, 3.5);
}

TEST(NetflixFixture, average_data_2) {
  map<int, Customer> customers = {{1, Customer(1)}, {2, Customer(2)}};
  customers[1].average = 4.0;
  customers[2].average = 3.0;
  double r = average_data(customers);
  ASSERT_EQ(r, 3.5);
}

TEST(NetflixFixture, average_data_3) {
  map<int, Customer> customers = {
      {1, Customer(1)}, {2, Customer(2)}, {3, Customer(3)}};
  customers[1].average = 4.0;
  customers[2].average = 3.0;
  customers[3].average = 2.0;
  double r = average_data(customers);
  ASSERT_EQ(r, 3.0);
}

TEST(NetflixFixture, average_data_4) {
  map<int, Movie> movies = {
      {1, Movie(1, 2000)}, {2, Movie(2, 2000)}, {3, Movie(3, 2000)}};
  movies[1].average = 4.0;
  movies[2].average = 3.0;
  movies[3].average = 2.0;
  double r = average_data(movies);
  ASSERT_EQ(r, 3.0);
}

TEST(NetflixFixture, RMSE_1) {
  list<double> predictions = {1.0, 2.0, 3.0};
  list<double> actual = {1.0, 2.0, 3.0};
  double r = RMSE(predictions.begin(), predictions.end(), actual.begin());
  ASSERT_EQ(r, 0.0);
}

TEST(NetflixFixture, RMSE_2) {
  list<double> predictions = {1.0, 2.0, 3.0};
  list<double> actual = {2.0, 3.0, 4.0};
  double r = RMSE(predictions.begin(), predictions.end(), actual.begin());
  ASSERT_EQ(r, 1.0);
}

TEST(NetflixFixture, RMSE_3) {
  list<double> predictions = {1.0, 2.0, 3.0};
  list<double> actual = {1.5, 1.5, 3.5};
  double r = RMSE(predictions.begin(), predictions.end(), actual.begin());
  ASSERT_EQ(r, 0.5);
}

TEST(NetflixFixture, RMSE_4) {
  list<double> predictions = {2.0, 2.0, 2.0};
  list<double> actual = {4.0, 4.0, 4.0};
  double r = RMSE(predictions.begin(), predictions.end(), actual.begin());
  ASSERT_EQ(r, 2.0);
}

TEST(NetflixFixture, solve_1) {
  istringstream r("1:\n1\n");
  ostringstream w;
  map<int, Movie> movies = {{1, Movie(1, 2000)}};
  map<int, Customer> customers = {{1, Customer(1)}};
  map<int, map<int, int>> probe = {{1, {{1, 3}}}};
  movies[1].average = 3.0;
  customers[1].average = 3.0;
  netflix_solve(r, w, movies, customers, probe);
  ASSERT_EQ("1:\n3.0\nRMSE: 0.00\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("1:\n1\n");
  ostringstream w;
  map<int, Movie> movies = {{1, Movie(1, 2000)}};
  map<int, Customer> customers = {{1, Customer(1)}};
  map<int, map<int, int>> probe = {{1, {{1, 4}}}};
  movies[1].average = 3.0;
  customers[1].average = 3.0;
  netflix_solve(r, w, movies, customers, probe);
  ASSERT_EQ("1:\n3.0\nRMSE: 1.00\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("1:\n1\n");
  ostringstream w;
  map<int, Movie> movies = {{1, Movie(1, 2000)}, {2, Movie(2, 1995)}};
  map<int, Customer> customers = {{1, Customer(1)}, {2, Customer(2)}};
  map<int, map<int, int>> probe = {{1, {{1, 4}}}};
  movies[1].average = 3.0;
  customers[1].average = 3.0;
  movies[2].average = 4.0;
  customers[2].average = 4.0;
  netflix_solve(r, w, movies, customers, probe);
  ASSERT_EQ("1:\n2.4\nRMSE: 1.60\n", w.str());
}

TEST(NetflixFixture, rmse_print_1) {
  ostringstream w;
  rmse_print(w, 1.53);
  ASSERT_EQ("RMSE: 1.53\n", w.str());
}

TEST(NetflixFixture, rmse_print_2) {
  ostringstream w;
  rmse_print(w, 0.955);
  ASSERT_EQ("RMSE: 0.95\n", w.str());
}

TEST(NetflixFixture, rmse_print_3) {
  ostringstream w;
  rmse_print(w, 0.999);
  ASSERT_EQ("RMSE: 0.99\n", w.str());
}
