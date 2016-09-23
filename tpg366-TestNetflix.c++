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
// netflix_read
// ----

TEST(NetflixFixture, netflix_read1) {
  istringstream r1("14675:");
  string test1 = "";
  const bool a = netflix_read(r1, test1);
  ASSERT_TRUE(a);
}

TEST(NetflixFixture, netflix_read2) {
  istringstream r2("8764362");
  string test2 = "";
  const bool b = netflix_read(r2, test2);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, netflix_read3) {
  istringstream r3("wheeee");
  string test3 = "";
  const bool c = netflix_read(r3, test3);
  ASSERT_TRUE(c);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval1) {
  const string movie = netflix_eval("76543:");
  ASSERT_EQ("76543:", movie);
}

TEST(NetflixFixture, eval2) {
  const string calc1 = netflix_eval("76543");
  ASSERT_EQ("3.7",calc1);
}

TEST(NetflixFixture, eval3) {
  const string calc2 = netflix_eval("50");
  ASSERT_EQ("3.7",calc2);
}


// ---------------
// netflix_get_ans
// ---------------

TEST(NetflixFixture, get_ans1) {
  key.insert(pair<string, int>("1_1", 4));
  const int rating1 = netflix_get_ans(1, 1);
  ASSERT_EQ(4, rating1);
}

TEST(NetflixFixture, get_ans2) {
  key.insert(pair<string, int>("1_1", 4));
  key.insert(pair<string, int>("1_2", 1));
  const int rating2 = netflix_get_ans(1, 2);
  ASSERT_EQ(1,rating2);
}

TEST(NetflixFixture, get_ans3) {
  const int rating3 = netflix_get_ans(100, 4);
  ASSERT_EQ(0,rating3);
}

// ------------
// netflix_rmse
// ------------

TEST(NetflixFixture, netflix_rmse1) {
  running_error = 1;
  number_error = 1;
  const double test1 = 1;
  const double calc1= netflix_rmse();
  ASSERT_EQ(0, (int) test1 - (int) calc1);
}

TEST(NetflixFixture, netflix_rmse2) {
  running_error = 2;
  number_error = 5;
  const double test2 = 0.63;
  const double calc2 = netflix_rmse();
  ASSERT_EQ(0, (int) test2 - (int) calc2);
}

TEST(NetflixFixture, netflix_rmse3) {
  running_error = 6;
  number_error = 3;
  const double test3 = 1.41;
  const double calc3= netflix_rmse();
  ASSERT_DOUBLE_EQ(0, (int) test3 - (int) calc3);
}

// ------------
// rmse_print
// ------------

TEST(NetflixFixture, print_rmse1) {
  ostringstream w;
  const double test1 = 6.00;
  rmse_print(w, test1);
  ASSERT_EQ("RMSE: 6\n", w.str());
}

TEST(NetflixFixture, print_rmse2) {
  ostringstream w;
  const double test2 = 7.32;
  rmse_print(w, test2);
  ASSERT_EQ("RMSE: 7.32\n", w.str());
}

TEST(NetflixFixture, print_rmse3) {
  ostringstream w;
  const double test3 = 1;
  rmse_print(w, test3);
  ASSERT_EQ("RMSE: 1\n", w.str());
}

// -------------
// split
// -------------

TEST(NetflixFixture, split1) {
  const vector<string> sep1 = split("1 328139 2139811", ' ');
  ASSERT_EQ("1", sep1.at(0));
  ASSERT_EQ("328139", sep1.at(1));
  ASSERT_EQ("2139811", sep1.at(2));
}

TEST(NetflixFixture, split2) {
  const vector<string> sep2 = split("1213213 1 0", ' ');
  ASSERT_EQ("1213213", sep2.at(0));
  ASSERT_EQ("1", sep2.at(1));
  ASSERT_EQ("0", sep2.at(2));
}

TEST(NetflixFixture, split3) {
  const vector<string> sep3 = split("0 21 6546", ' ');
  ASSERT_EQ("0", sep3.at(0));
  ASSERT_EQ("21", sep3.at(1));
  ASSERT_EQ("6546", sep3.at(2));
}

// -----
// netflix_print
// -----

TEST(NetflixFixture, netflix_print1) {
  ostringstream w;
  netflix_print(w, "6372673632");
  ASSERT_EQ("6372673632\n", w.str());
}

TEST(NetflixFixture, netflix_print2) {
  ostringstream w;
  netflix_print(w, ":");
  ASSERT_EQ(":\n", w.str());
}

TEST(NetflixFixture, netflix_print3) {
  ostringstream w;
  netflix_print(w, "");
  ASSERT_EQ("\n", w.str());
}
