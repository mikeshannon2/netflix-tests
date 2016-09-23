// --------------------------------
// CS371p/TestNetflix.c++
// Ryan Freeman
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

TEST(NetflixFixture, read1) {
  istringstream r("2202464\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("2202464", i);
}

TEST(NetflixFixture, read2) {
  istringstream r("985:\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("985:", i);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
  const int v = netflix_eval("985:");
  ASSERT_EQ(-1, v);
}

// -----
// print
// -----

TEST(NetflixFixture, print) {
  ostringstream w;
  netflix_print(w, "985:", -1);
  ASSERT_EQ("985:\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
  istringstream r("1:\n30878\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1:\n3.6\nRMSE: 0.4\n", w.str());
}