// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, netflix_read) {
  istringstream r("1:\n");
  std::string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("1:", i);
}

//---------
//cust_avg
//---------

TEST(NetflixFixture, cust_avg_1) {
  const float v = get_cust_rating("0000008");
  ASSERT_EQ("4.210000", std::to_string(v));
}


TEST(NetflixFixture, cust_avg_2) {
  const float v = get_cust_rating("1174466");
  ASSERT_EQ("3.160000", std::to_string(v));
}

TEST(NetflixFixture, cust_avg_3) {
  const float v = get_cust_rating("2649429");
  ASSERT_EQ("4.180000", std::to_string(v));
}

TEST(NetflixFixture, cust_avg_4) {
  const float v = get_cust_rating("0000006");
  ASSERT_EQ("3.420000", std::to_string(v));
}


//----------
//movie_avg
//----------

TEST(NetflixFixture, movie_avg_1) {
  const float v = get_movie_rating("2");
  ASSERT_EQ("3.560000", std::to_string(v));
}

TEST(NetflixFixture, movie_avg_2) {
  const float v = get_movie_rating("5");
  ASSERT_EQ("3.920000", std::to_string(v));
}

TEST(NetflixFixture, movie_avg_3) {
  const float v = get_movie_rating("15802");
  ASSERT_EQ("4.040000", std::to_string(v));
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
  const float v = netflix_eval("15802", "30878");
  ASSERT_EQ("4.070000", std::to_string(v));
}

TEST(NetflixFixture, eval_2) {
  const float v = netflix_eval("1", "30878");
  ASSERT_EQ("3.780000", std::to_string(v));
}

TEST(NetflixFixture, eval_3) {
  const float v = netflix_eval("1000", "79755");
  ASSERT_EQ("3.810000", std::to_string(v));
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  netflix_print(w, "1", "10", 3.4);
  ASSERT_EQ("1 10 3.4\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  netflix_print(w, "30000000", "130123", 4.89);
  ASSERT_EQ("30000000 130123 4.89\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  netflix_print(w, "1", "1", 2);
  ASSERT_EQ("1 1 2\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("10014:\n1626179\n1359761\n839609\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("10014 1626179 3.13\n10014 1359761 4.02\n10014 839609 3.1\nRMSE: 0.505734\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("10014:\n1626179\n1359761\n839609\n1002:\n2174660\n1685301\n988266\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("10014 1626179 3.13\n10014 1359761 4.02\n10014 839609 3.1\n1002 2174660 3.23\n1002 1685301 2.83\n1002 988266 3.47\nRMSE: 0.961769\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("10014:\n1626179\n1359761\n839609\n1002:\n2174660\n1685301\n988266\n10:\n1952305\n1531863\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("10014 1626179 3.13\n10014 1359761 4.02\n10014 839609 3.1\n1002 2174660 3.23\n1002 1685301 2.83\n1002 988266 3.47\n10 1952305 2.99\n10 1531863 2.73\nRMSE: 0.946243\n", w.str());
}