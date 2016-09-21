// --------------------------------
// TestNetflix.c++
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
  istringstream r("1\n");
  string s;
  const bool b = netflix_read(r, s);
  ASSERT_TRUE(b);
  ASSERT_EQ("1", s);
}

TEST(NetflixFixture, read_2) {
  istringstream r("42:\n");
  string s;
  const bool b = netflix_read(r, s);
  ASSERT_TRUE(b);
  ASSERT_EQ("42:", s);
}

TEST(NetflixFixture, read_3) {
  istringstream r("ReallyBigStringNStuffTest:\n");
  string s;
  const bool b = netflix_read(r, s);
  ASSERT_TRUE(b);
  ASSERT_EQ("ReallyBigStringNStuffTest:", s);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
  vector<double> vect;
  const double v = netflix_eval(1, 548064, vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("3.57", val);
}

TEST(NetflixFixture, eval_2) {
  vector<double> vect;
  const double v = netflix_eval(6946, 1261894, vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("2.79", val);
}

TEST(NetflixFixture, eval_3) {
  vector<double> vect;
  const double v = netflix_eval(16326, 433517, vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("3.02", val);
}

// ---------
// rmse_calc
// ---------

TEST(NetflixFixture, rmse_calc_1) {
  vector<double> vect = {0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  const double v = rmse_calc(vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("1.73", val);
}

TEST(NetflixFixture, rmse_calc_2) {
  vector<double> vect = {1.0, 2.0, 3.0, 40, 90, 100};
  const double v = rmse_calc(vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("6.28", val);
}

TEST(NetflixFixture, rmse_calc_3) {
  vector<double> vect = {42.0, 42.0, 42.0, 42.0, 42.0};
  const double v = rmse_calc(vect);
  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(2) << v;
  string val = ss.str();
  ASSERT_EQ("7.10", val);
}


// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  string s = "1";
  netflix_print(w, s);
  ASSERT_EQ("1\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  string s = "The best string ever, but printed.";
  netflix_print(w, s);
  ASSERT_EQ("The best string ever, but printed.\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  string s = "The second best string ever with a newline.";
  netflix_print(w, s);
  ASSERT_EQ("The second best string ever with a newline.\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1:\n548064\n1095:\n453352\n1877477\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1:\n3.56\n1095:\n2.43\n2.80\nRMSE: 1.19\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("17236:\n477855\n1620428\n375352\n339109\n1465796\n1282081\n1199881\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("17236:\n2.14\n2.23\n1.99\n2.54\n2.71\n3.07\n2.25\nRMSE: 0.97\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("6905:\n246618\n1305872\n345476\n5427:\n129710\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("6905:\n3.82\n3.25\n2.53\n5427:\n2.78\nRMSE: 1.28\n", w.str());
}