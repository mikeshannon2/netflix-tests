// ----------------
// Brenda A.Salazar
// Netflix Project
// UTEid: 3789
// ----------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // stirng
#include <utility>  //pair
#include <map>      //map

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -----------
// print_movie
// -----------

TEST(NetflixFixture, print_movie_1) {
  ostringstream w;
  print_movie(w, 6789);
  ASSERT_EQ("6789:\n", w.str());
}

TEST(NetflixFixture, print_movie_2) {
  ostringstream w;
  print_movie(w, 89470);
  ASSERT_EQ("89470:\n", w.str());
}

TEST(NetflixFixture, print_movie_3) {
  ostringstream w;
  print_movie(w, 3893351);
  ASSERT_EQ("3893351:\n", w.str());
}

// ------------
// print_rating
// ------------

TEST(NetflixFixture, print_rating_1) {
  ostringstream w;
  print_rating(w, 1.2345);
  ASSERT_EQ("1.2\n", w.str());
}

TEST(NetflixFixture, print_rating_2) {
  ostringstream w;
  print_rating(w, 4.78);
  ASSERT_EQ("4.7\n", w.str());
}

TEST(NetflixFixture, print_rating_3) {
  ostringstream w;
  print_rating(w, 2.6);
  ASSERT_EQ("2.6\n", w.str());
}

// ----------
// print_rmse
// ----------

TEST(NetflixFixture, print_rmse_1) {
  ostringstream w;
  print_rmse(w, 1.949);
  ASSERT_EQ("RMSE: 1.94\n", w.str());
}

TEST(NetflixFixture, print_rmse_2) {
  ostringstream w;
  print_rmse(w, 0.76);
  ASSERT_EQ("RMSE: 0.76\n", w.str());
}

TEST(NetflixFixture, print_rmse_3) {
  ostringstream w;
  print_rmse(w, 2.543125);
  ASSERT_EQ("RMSE: 2.54\n", w.str());
}

// ----------
// read_movie
// ----------

TEST(NetflixFixture, read_movie_1) {
  istringstream r("4567:\n");
  int movie_id;
  const bool b = read_movie(r, movie_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(4567, movie_id);
}

TEST(NetflixFixture, read_movie_2) {
  istringstream r("1:\n 7");
  int movie_id;
  const bool b = read_movie(r, movie_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, movie_id);
}

TEST(NetflixFixture, read_movie_3) {
  istringstream r("784795:\n 4646");
  int movie_id;
  const bool b = read_movie(r, movie_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(784795, movie_id);
}

// -------------
// read_customer
// -------------

TEST(NetflixFixture, read_customer_1) {
  istringstream r("8475924\n");
  int customer_id;
  const bool b = read_customer(r, customer_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(8475924, customer_id);
}

TEST(NetflixFixture, read_customer_2) {
  istringstream r("4284:\n");
  int customer_id;
  const bool b = read_customer(r, customer_id);
  ASSERT_FALSE(b);
}

TEST(NetflixFixture, read_customer_3) {
  istringstream r("\n");
  int customer_id;
  const bool b = read_customer(r, customer_id);
  ASSERT_FALSE(b);
}

// ---------------
// netflix_predict
// ---------------

TEST(NetflixFixture, netflix_predict_1) {
  const double prediction = netflix_predict(4, 3.4, 3.2);
  ASSERT_DOUBLE_EQ(2.9, prediction);
}

TEST(NetflixFixture, netflix_predict_2) {
  const double prediction = netflix_predict(5, 4.2, 3);
  ASSERT_DOUBLE_EQ(3.5, prediction);
}

TEST(NetflixFixture, netflix_predict_3) {
  const double prediction = netflix_predict(3, 2.8, 4.6);
  ASSERT_DOUBLE_EQ(3.7, prediction);
}

// -------------
// netflix_solve
// -------------

TEST(NetflixFixture, netflix_solve_1) {
  ostringstream w;
  istringstream r("1:\n12\n");
  map<pair<int, int>, int> a;
  pair<int, int> tmp(1, 12);
  a[tmp] = 4;
  map<int, double> m;
  m[1] = 3.4;
  map<int, double> c;
  c[12] = 3.2;
  netflix_solve(r, w, a, m, c);
  ASSERT_EQ("1:\n2.9\nRMSE: 1.13\n", w.str());
}

TEST(NetflixFixture, netflix_solve_2) {
  ostringstream w;
  istringstream r("7:\n8\n");
  map<pair<int, int>, int> a;
  pair<int, int> tmp(7, 8);
  a[tmp] = 5;
  map<int, double> m;
  m[7] = 4.2;
  map<int, double> c;
  c[8] = 3;
  netflix_solve(r, w, a, m, c);
  ASSERT_EQ("7:\n3.5\nRMSE: 1.21\n", w.str());
}

TEST(NetflixFixture, netflix_solve_3) {
  ostringstream w;
  istringstream r("56:\n78\n");
  map<pair<int, int>, int> a;
  pair<int, int> tmp(56, 78);
  a[tmp] = 3;
  map<int, double> m;
  m[56] = 2.8;
  map<int, double> c;
  c[78] = 4.6;
  netflix_solve(r, w, a, m, c);
  ASSERT_EQ("56:\n3.6\nRMSE: 1.14\n", w.str());
}
