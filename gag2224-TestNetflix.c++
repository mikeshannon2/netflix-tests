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

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -----------
// print_movie
// -----------

TEST(NetflixFixture, print_movie_1) {
  ostringstream w;
  netflix_print_movie(w, 1);
  ASSERT_EQ("1:\n", w.str());
}

TEST(NetflixFixture, print_movie_2) {
  ostringstream w;
  netflix_print_movie(w, 125);
  ASSERT_EQ("125:\n", w.str());
}

TEST(NetflixFixture, print_movie_3) {
  ostringstream w;
  netflix_print_movie(w, 89);
  ASSERT_EQ("89:\n", w.str());
}

TEST(NetflixFixture, print_movie_4) {
  ostringstream w;
  netflix_print_movie(w, 32768);
  ASSERT_EQ("32768:\n", w.str());
}

// ------------
// print_rating
// ------------

TEST(NetflixFixture, print_rating_1) {
  ostringstream w;
  netflix_print_rating(w, 1.222222);
  ASSERT_EQ("1.2\n", w.str());
}

TEST(NetflixFixture, print_rating_2) {
  ostringstream w;
  netflix_print_rating(w, 4.9000);
  ASSERT_EQ("4.9\n", w.str());
}

TEST(NetflixFixture, print_rating_3) {
  ostringstream w;
  netflix_print_rating(w, 2.541890);
  ASSERT_EQ("2.5\n", w.str());
}

TEST(NetflixFixture, print_rating_4) {
  ostringstream w;
  netflix_print_rating(w, 3.9199999);
  ASSERT_EQ("3.9\n", w.str());
}

// ----------
// print_rmse
// ----------

TEST(NetflixFixture, print_rmse_1) {
  ostringstream w;
  netflix_print_rmse(w, 1.222222);
  ASSERT_EQ("RMSE: 1.22\n", w.str());
}

TEST(NetflixFixture, print_rmse_2) {
  ostringstream w;
  netflix_print_rmse(w, 4.9000);
  ASSERT_EQ("RMSE: 4.90\n", w.str());
}

TEST(NetflixFixture, print_rmse_3) {
  ostringstream w;
  netflix_print_rmse(w, 2.562890);
  ASSERT_EQ("RMSE: 2.56\n", w.str());
}

TEST(NetflixFixture, print_rmse_4) {
  ostringstream w;
  netflix_print_rmse(w, 3.9929999);
  ASSERT_EQ("RMSE: 3.99\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("2043:\n1");
  ostringstream w;
  istringstream actual("3 4\n");
  istringstream averages("3.65 3.65\n");
  netflix_solve(r, w, actual, averages);
  ASSERT_EQ("2043:\n3.5\nRMSE: 0.44\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("2043:\n1\n10851:\n1417435\n");
  ostringstream w;
  istringstream actual("4 3 4 3\n");
  istringstream averages("3.65 3.65 3.65 3.65\n");
  netflix_solve(r, w, actual, averages);
  ASSERT_EQ("2043:\n3.5\n10851:\n3.5\nRMSE: 0.54\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("2043:\n1\n10851:\n1417435\n2312054\n");
  ostringstream w;
  istringstream actual("4 3 4 4 3\n");
  istringstream averages("3.65 3.65 3.65 3.65 3.65\n");
  netflix_solve(r, w, actual, averages);
  ASSERT_EQ("2043:\n3.5\n10851:\n3.5\n3.5\nRMSE: 0.51\n", w.str());
}

TEST(NetflixFixture, solve_4) {
  istringstream r("2043:\n1417435\n2312054\n10851:\n1417435\n2312054\n462685\n");
  ostringstream w;
  istringstream actual("3 4 3 4 3 4 3\n");
  istringstream averages("3.65 3.65 3.65 3.65 3.65 3.65 3.65\n");
  netflix_solve(r, w, actual, averages);
  ASSERT_EQ("2043:\n3.5\n3.5\n10851:\n3.5\n3.5\n3.5\nRMSE: 0.50\n", w.str());
}
