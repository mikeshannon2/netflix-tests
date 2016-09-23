#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

TEST(NetflixFixture, netflix_load_cache1) {
  string ms = "500 4.5\n";
  string cs = "60 3.5\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
}
TEST(NetflixFixture, netflix_load_cache2) {
  string ms = "500 4.5\n623412 2.2\n";
  string cs = "60 3.5\n12333 1.1\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
}
TEST(NetflixFixture, netflix_eval_one1) {
  string ms = "500 4.5\n";
  string cs = "60 3.5\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
  double v = netflix_eval_one(500, 60);
  ASSERT_EQ(v, 4.3);
}

TEST(NetflixFixture, netflix_eval_one2) {
  string ms = "5001 1.1\n";
  string cs = "6660 2.2\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
  double v = netflix_eval_one(5001, 6660);
  ASSERT_EQ(v, 1.0);
}

TEST(NetflixFixture, netflix_eval_one3) {
  string ms = "1155 4.5\n";
  string cs = "7123 4.8\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
  double v = netflix_eval_one(1155, 7123);
  ASSERT_EQ(v, 5.0);
}

TEST(NetflixFixture, netflix_eval_one4) {
  string ms = "1155 3.0\n";
  string cs = "7123 3.0\n";
  istringstream imss(ms);
  istringstream icss(cs);
  netflix_load_cache(icss, imss);
  double v = netflix_eval_one(1155, 7123);
  ASSERT_EQ(v, 2.3);
}
TEST(NetflixFixture, netflix_solve) {
  string ms = "5000 3.6";
  string cs = "3000 3.8";
  string is = "5000:\n3000";
  string os = "";
  istringstream imss(ms);
  istringstream icss(cs);
  istringstream iiss(is);
  ostringstream oss(os);
  list<int> m = {};
  list<int> c = {};
  list<double> r = {};
  netflix_solve(iiss, oss, icss, imss, m, c, r);
  list<double>::iterator i = r.begin();
  double v = *i;
  ASSERT_EQ(v, 3.7);
}
