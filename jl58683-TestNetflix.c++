// --------------------------------
// TestNetflix.c++
// Bradon Stotmeister
// Jia Li
// --------------------------------

// --------
// includes
// --------

#include "gtest/gtest.h"
#include <fstream>  //reading probe.txt
#include <iostream> // cout, endl
#include <map>
#include <sstream> // istringtstream, ostringstream
#include <string>  // string
#include <utility>

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read1) {
  // Passing a movie ID with ":"
  istringstream r("2043:");
  string b = netflix_read(r);
  ASSERT_EQ("2043:", b);
}

TEST(NetflixFixture, read2) {
  // Movie ID with newline
  istringstream r("2043:\n");
  string b = netflix_read(r);
  ASSERT_EQ("2043:", b);
}

TEST(NetflixFixture, read3) {
  // Passing a customer ID
  istringstream r("30878");
  string b = netflix_read(r);
  ASSERT_EQ("30878", b);
}

TEST(NetflixFixture, read4) {
  // Customer ID with newline
  istringstream r("30878\n");
  string b = netflix_read(r);
  ASSERT_EQ("30878", b);
}

// ----
// eval
// Only thing we can guarantee is that the guess is between 1 and 5
// ----

TEST(NetflixFixture, eval_1) {
  const float v = netflix_eval("1", "30878");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, eval_2) {
  const float v = netflix_eval("1", "2647871");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, eval_3) {
  const float v = netflix_eval("100", "1952305");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, eval_4) {
  const float v = netflix_eval("10", "195230");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, eval_5) {
  const float v = netflix_eval("23", "1952305");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, eval_6) {
  const float v = netflix_eval("10001", "1952305");
  const bool b = (v >= 1) && (v <= 5);
  ASSERT_TRUE(b);
}

// ----
// RMSE
// ----

TEST(NetflixFixture, rmse1) {
  map<pair<string, string>, float> e;
  ostringstream w;

  e[make_pair("test1", "test1")] = 4.0;
  e[make_pair("test2", "test2")] = 4.0;
  e[make_pair("test3", "test3")] = 4.0;

  netflix_rmse(e, w);
  ASSERT_EQ("RMSE: 4.00\n", w.str());
}

TEST(NetflixFixture, rmse2) {
  map<pair<string, string>, float> e;
  ostringstream w;

  e[make_pair("test1", "test1")] = 3.0;
  e[make_pair("test2", "test2")] = 3.0;
  e[make_pair("test3", "test3")] = 3.0;

  netflix_rmse(e, w);
  ASSERT_EQ("RMSE: 3.00\n", w.str());
}

TEST(NetflixFixture, rmse3) {
  map<pair<string, string>, float> e;
  ostringstream w;

  e[make_pair("test1", "test1")] = 1.2;
  e[make_pair("test2", "test2")] = 1.2;
  e[make_pair("test3", "test3")] = 1.2;

  netflix_rmse(e, w);
  ASSERT_EQ("RMSE: 1.20\n", w.str());
}

// -----
// print
// -----

TEST(NetflixFixture, print1) {
  ostringstream w;
  netflix_print(w, 1.2);
  ASSERT_EQ("1.2\n", w.str());
}

TEST(NetflixFixture, print2) {
  ostringstream w;
  netflix_print(w, 5.0);
  ASSERT_EQ("5.0\n", w.str());
}

TEST(NetflixFixture, print3) {
  ostringstream w;
  netflix_print(w, 3.37);
  ASSERT_EQ("3.3\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve1) {
  istringstream r("1:\n30878\n");
  ostringstream w;
  ifstream f1("1 3.2\n");
  ifstream f2("30878 3.3\n");
  ifstream f3("1 30878 3.2\n");

  netflix_solve(r, w, f1, f2, f3);
  ASSERT_NE(w.str().find("1:\n"), -1);
  ASSERT_NE(w.str().find("RMSE: "), -1);
}

TEST(NetflixFixture, solve2) {
  istringstream r("2000:\n1777883\n");
  ostringstream w;
  ifstream f1("2000 3.2\n");
  ifstream f2("1777883 3.3\n");
  ifstream f3("2000 1777883 3.2\n");

  netflix_solve(r, w, f1, f2, f3);
  ASSERT_NE(w.str().find("2000:\n"), -1);
  ASSERT_NE(w.str().find("RMSE: "), -1);
}

TEST(NetflixFixture, solve3) {
  istringstream r("458:\n16356\n459:\n1533721\n");
  ostringstream w;
  ifstream f1("458 3.2\n459 4.1\n");
  ifstream f2("16356 3.3\n1533721 4.7\n");
  ifstream f3("458 16356 3.3\n459 1533721 4.5\n");

  netflix_solve(r, w, f1, f2, f3);
  ASSERT_NE(w.str().find("458:\n"), -1);
  ASSERT_NE(w.str().find("459:\n"), -1);
  ASSERT_NE(w.str().find("RMSE: "), -1);
}