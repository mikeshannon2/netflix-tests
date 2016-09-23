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


TEST(NetflixFixture, truncate_1) {
  const double v = truncate(9.745, 1);
  ASSERT_EQ(9.7, v);
}

TEST(NetflixFixture, truncate_2) {
  const double v = truncate(0.43621, 3);
  ASSERT_EQ(0.436, v);
}

TEST(NetflixFixture, truncate_3) {
  const double v = truncate(3.10985, 1);
  ASSERT_EQ(3.1, v);
}

TEST(NetflixFixture, truncate_4) {
  const double v = truncate(9.74527, 4);
  ASSERT_EQ(9.7452, v);
}

TEST(NetflixFixture, truncate_5) {
  const double v = truncate(5.555, 2);
  ASSERT_EQ(5.55, v);
}

TEST(NetflixFixture, truncate_6) {
  const double v = truncate(12.6789, 4);
  ASSERT_EQ(12.6789, v);
}

TEST(NetflixFixture, truncate_7) {
  const double v = truncate(10.78901121, 5);
  ASSERT_EQ(10.78901, v);
}

TEST(NetflixFixture, truncate_8) {
  const double v = truncate(5.6799, 3);
  ASSERT_EQ(5.679, v);
}

TEST(NetflixFixture, truncate_9) {
  const double v = truncate(234.12345, 2);
  ASSERT_EQ(234.12, v);
}

TEST(NetflixFixture, mean_1) {
  const double v = error_square_mean(14.8, 4);
  ASSERT_EQ(3.7, v);
}

TEST(NetflixFixture, mean_2) {
  const double v = error_square_mean(15, 2);
  ASSERT_EQ(7.5, v);
}

TEST(NetflixFixture, mean_3) {
  const double v = error_square_mean(16.4, 4);
  ASSERT_EQ(4.1, v);
}

TEST(NetflixFixture, mean_4) {
  const double v = error_square_mean(12.6, 3);
  ASSERT_EQ(4.2, v);
}

TEST(NetflixFixture, mean_5) {
  const double v = error_square_mean(12, 1);
  ASSERT_EQ(12.0, v);
}

TEST(NetflixFixture, mean_6) {
  const double v = error_square_mean(16.6, 4);
  ASSERT_EQ(4.15, v);
}

TEST(NetflixFixture, mean_7) {
  const double v = error_square_mean(12, 8);
  ASSERT_EQ(1.5, v);
}

TEST(NetflixFixture, mean_8) {
  const double v = error_square_mean(15.5, 5);
  ASSERT_EQ(3.1, v);
}

TEST(NetflixFixture, mean_9) {
  const double v = error_square_mean(14, 10);
  ASSERT_EQ(1.4, v);
}

TEST(NetflixFixture, solve_1) {
  istringstream r("1:\n10\n20\n30");
  istringstream movies_file("1 3.75\n");
  istringstream users_file("10 3.5\n20 3.9\n30 3.7\n");
  istringstream users_std_file("10 0.01\n20 0.1\n30 0.11\n");
  istringstream probe_actual_file("1:\n3\n4\n4\n");
  ostringstream w;
  netflix_solve(r, w, movies_file, users_file, users_std_file, probe_actual_file);
  ASSERT_EQ("1:\n3.6\n3.8\n3.7\nRMSE: 0.4\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("5:\n20\n30\n40\n");
  istringstream movies_file("5 4.5\n");
  istringstream users_file("20 4.1\n30 4.9\n40 4.3\n");
  istringstream users_std_file("20 0.0132\n30 0.12\n40 0.05\n");
  istringstream probe_actual_file("5:\n4\n4\n4\n");
  ostringstream w;
  netflix_solve(r, w, movies_file, users_file, users_std_file, probe_actual_file);
  ASSERT_EQ("5:\n4.3\n4.7\n4.4\nRMSE: 0.49\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("10:\n21\n31\n41\n60:\n21\n31\n41\n");
  istringstream movies_file("10 4.5\n60 3.5\n");
  istringstream users_file("21 4.2\n31 4.7\n41 3.4\n");
  istringstream users_std_file("21 0.005\n31 0.0145\n41 0.0156\n");
  istringstream probe_actual_file("10:\n4\n4\n4\n60:\n3\n4\n5\n");
  ostringstream w;
  netflix_solve(r, w, movies_file, users_file, users_std_file, probe_actual_file);
  ASSERT_EQ("10:\n4.3\n4.6\n3.9\n60:\n3.8\n4.1\n3.4\nRMSE: 0.78\n", w.str());
}


