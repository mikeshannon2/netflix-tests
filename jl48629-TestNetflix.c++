// --------------------------------
// projects/netflix/TestNetflix.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("23758:\n");
  int i;
  int j;
  bool k;
  const bool b = netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ(23758, i);
  ASSERT_TRUE(k);
}

TEST(NetflixFixture, read_2) {
  istringstream r("100\n");
  int i;
  int j;
  bool k;
  const bool b = netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ(100, j);
  ASSERT_FALSE(k);
}

TEST(NetflixFixture, read_3) {
  istringstream r("500:\n");
  int i;
  int j;
  bool k;
  const bool b = netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ(500, i);
  ASSERT_TRUE(k);
}

// ------------
// eval
// ------------

TEST(NetflixFixture, eval_1) {
  float rmse = 0;
  float rating = netflix_eval(4.9, 3.5, 4, rmse);
  ASSERT_FLOAT_EQ(4.7, rating);
}

TEST(NetflixFixture, eval_2) {
  float rmse = 0;
  float rating = netflix_eval(3.6, 3.1, 4, rmse);
  ASSERT_FLOAT_EQ(3.0, rating);
}

TEST(NetflixFixture, eval_3) {
  float rmse = 0;
  float rating = netflix_eval(4.7, 2.7, 4, rmse);
  ASSERT_FLOAT_EQ(3.7, rating);
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  netflix_print(w, 3.04, 2, 1);
  ASSERT_EQ("2:\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  netflix_print(w, 1.24, 1, 0);
  ASSERT_EQ("1.2\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  netflix_print(w, 4.39, 234543, 0);
  ASSERT_EQ("4.3\n", w.str());
}


// ------
//  rmse
// ------

TEST(NetflixFixture, rmse_1) {
  ostringstream w;
  netflix_rmse(w, 5, 2);
  ASSERT_EQ("RMSE: 1.58\n", w.str());
}

TEST(NetflixFixture, rmse_2) {
  ostringstream w;
  netflix_rmse(w, 2, 1);
  ASSERT_EQ("RMSE: 1.41\n", w.str());
}

TEST(NetflixFixture, rmse_3) {
  ostringstream w;
  netflix_rmse(w, 9888, 561);
  ASSERT_EQ("RMSE: 4.19\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1: \n1 2\n");
  ostringstream w;

  float movie_avg_rating_cache[] = {0.0, 3.7};
  unordered_map<string, float> customer_avg_rating_cache;
  customer_avg_rating_cache["1"] = 3.7;
  customer_avg_rating_cache["2"] = 3.7;
  unordered_map<string, unordered_map<string, float>> solution_cache;
  solution_cache["1"]["1"] = 3.7;
  solution_cache["1"]["2"] = 3.7;

  netflix_solve(r, w, movie_avg_rating_cache, customer_avg_rating_cache, solution_cache);
  ASSERT_EQ("1:\n3.7\n3.7\nRMSE: 0.00\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("1: 1 2");
  ostringstream w;

  float movie_avg_rating_cache[] = {0.0, 4};
  unordered_map<string, float> customer_avg_rating_cache;
  customer_avg_rating_cache["1"] = 3.7;
  customer_avg_rating_cache["2"] = 3.4;
  unordered_map<string, unordered_map<string, float>> solution_cache;
  solution_cache["1"]["1"] = 4;
  solution_cache["1"]["2"] = 3.7;

  netflix_solve(r, w, movie_avg_rating_cache, customer_avg_rating_cache, solution_cache);
  ASSERT_EQ("1:\n4.0\n3.7\nRMSE: 0.00\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("1: 1 2 2: 1 2");
  ostringstream w;

  float movie_avg_rating_cache[] = {0.0, 4.0, 5.0};
  unordered_map<string, float> customer_avg_rating_cache;
  customer_avg_rating_cache["1"] = 4;
  customer_avg_rating_cache["2"] = 2;
  unordered_map<string, unordered_map<string, float>> solution_cache;
  solution_cache["1"]["1"] = 4.0;
  solution_cache["1"]["2"] = 3.0;
  solution_cache["2"]["1"] = 5.0;
  solution_cache["2"]["2"] = 3.0;

  netflix_solve(r, w, movie_avg_rating_cache, customer_avg_rating_cache, solution_cache);
  ASSERT_EQ("1:\n4.3\n2.3\n2:\n5.3\n3.3\nRMSE: 0.43\n", w.str());
}

