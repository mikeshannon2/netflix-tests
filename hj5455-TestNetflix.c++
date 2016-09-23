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
#include <list>
#include <sstream> // istringtstream, ostringstream
#include <string>  // string
#include <utility> // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----
TEST(NetflixFixture, eval1) {
  avg_movie[10042] = 3;
avg_customer[2155386] = 3.7;
double ans = netflix_eval(10042, 2155386);
  ASSERT_EQ(ans, 3);
}

TEST(NetflixFixture, eval2) {
  avg_movie[10042] = 2;
avg_customer[1292687] = 2;
double ans = netflix_eval(10042, 1292687);
  ASSERT_EQ(ans, 1);
}

TEST(NetflixFixture, eval3) {
 avg_movie[10036] = 4;
avg_customer[2008955] = 2;
  double ans = netflix_eval(10036, 2008955);
  ASSERT_EQ(ans, 2.3);
}

TEST(NetflixFixture, eval4) {
  avg_customer[2008955] = 3;
  avg_movie[10036] = 3;
  double ans = netflix_eval(10036, 2008955);
  ASSERT_EQ(ans, 2.3);
}

TEST(NetflixFixture, eval5) {
  avg_customer[200888] = 4.9;
  avg_movie[10036] = 3.9;
  double ans = netflix_eval(10036, 200888);
  ASSERT_EQ(ans, 5);
}


TEST(NetflixFixture, eval6) {
  avg_customer[200888] = 5;
  avg_movie[10036] = 5;
  double ans = netflix_eval(10036, 200888);
  ASSERT_EQ(ans, 5);
}


TEST(NetflixFixture, eval7) {
  avg_customer[185555] = 2.9;
  avg_movie[9999] = 0.8;
  double ans = netflix_eval(9999, 185555);
  ASSERT_EQ(ans, 1);
}


TEST(NetflixFixture, eval8) {
  avg_customer[200788] = 3.7;
  avg_movie[10030] = 4;
  double ans = netflix_eval(10030, 200788);
  ASSERT_EQ(ans, 4);
}


TEST(NetflixFixture, eval9) {
  avg_customer[200887] = 3.7;
  avg_movie[10035] = 3;
  double ans = netflix_eval(10035, 200887);
  ASSERT_EQ(ans, 3);
}
