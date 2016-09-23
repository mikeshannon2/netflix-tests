// --------------------------------
// projects/collatz/TestCollatz.c++
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

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("1:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("1:", i);
}

TEST(NetflixFixture, read_2) {
  istringstream r("1111:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("1111:", i);
}

TEST(NetflixFixture, read_3) {
  istringstream r("30878\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("30878", i);
}

TEST(NetflixFixture, read_4) {
  istringstream r("9999:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("9999:", i);
}

TEST(NetflixFixture, read_5) {
  istringstream r("1473765\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("1473765", i);
}

TEST(NetflixFixture, read_6) {
  istringstream r("9989:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("9989:", i);
}

TEST(NetflixFixture, read_7) {
  istringstream r("736005\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("736005", i);
}

TEST(NetflixFixture, read_8) {
  istringstream r("3340:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("3340:", i);
}

// ----
// RMSE
// ----

TEST(NetflixFixture, rmse_true_1) {
  RMSE rmse;
  const float v = rmse.trueRating(1712165, 994);
  ASSERT_EQ(2, v);
}

TEST(NetflixFixture, rmse_true_2) {
  RMSE rmse;
  const float v = rmse.trueRating(1026776, 9940);
  ASSERT_EQ(5, v);
}

TEST(NetflixFixture, rmse_true_3) {
  RMSE rmse;
  const float v = rmse.trueRating(1841072, 9948);
  ASSERT_EQ(3, v);
}

TEST(NetflixFixture, rmse_true_4) {
  RMSE rmse;
  const float v = rmse.trueRating(2090239, 2173);
  ASSERT_EQ(5, v);
}
// ----
// lookup
// ----

TEST(NetflixFixture, lookup_1) {
  const float v = netflix_calc_rating("30878", "1");
  ASSERT_EQ(3.68f, v);
}

TEST(NetflixFixture, lookup_2) {
  const float v = netflix_calc_rating("2328102", "9938");
  ASSERT_EQ(3.62f, v);
}

TEST(NetflixFixture, lookup_3) {
  const float v = netflix_calc_rating("741249", "5290");
  ASSERT_EQ(4.1f, v);
}

TEST(NetflixFixture, lookup_4) {
  const float v = netflix_calc_rating("1483361", "9937");
  ASSERT_EQ(3.08f, v);
}

TEST(NetflixFixture, lookup_5) {
  const float v = netflix_calc_rating("1871967", "9938");
  ASSERT_EQ(2.68f, v);
}

TEST(NetflixFixture, lookup_6) {
  const float v = netflix_calc_rating("1358865", "9932");
  ASSERT_EQ(2.16f, v);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1:\n30878\n2647871\n1283744\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1:\n3.68\n3.28\n3.59\nRMSE: 0.57\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("5292:\n1145353\n2452192\n688484\n10:");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("5292:\n3.91\n4.46\n5.14\n10:\nRMSE: 1.69\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("9935:\n1805961\n1711785\n71923\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("9935:\n4.7\n3.41\n4.08\nRMSE: 0.61\n", w.str());
}

TEST(NetflixFixture, solve_4) {
  istringstream r("9936:\n2612889\n2500699\n1097721\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("9936:\n3.63\n2.72\n3.52\nRMSE: 0.49\n", w.str());
}

TEST(NetflixFixture, solve_5) {
  istringstream r("9937:\n1533038\n1483361\n742428\n9936:");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("9937:\n3.57\n3.08\n3.67\n9936:\nRMSE: 1.13\n", w.str());
}

TEST(NetflixFixture, solve_6) {
  istringstream r("994:\n339448\n808135\n960348\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("994:\n3.21\n3.24\n3.84\nRMSE: 0.49\n", w.str());
}
