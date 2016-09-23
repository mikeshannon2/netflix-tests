// test cases for Netflix challenge

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, read1) {
  istream r("42:\n");
  int i, j;
  const bool b = netflix_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(42, i);
}

TEST(NetflixFixture, read2) {
  istream r("172842\n");
  int i, j;
  const bool b = netflix_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(172842, i);
}

TEST(NetflixFixture, read3) {
  istream r("960374\n");
  int i, j;
  const bool b = netflix_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(960374, i);
}

TEST(NetflixFixture, read4) {
  istream r("121234\n");
  int i, j;
  const bool b = netflix_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(121234, i);
}

TEST(NetflixFixture, print1) {
  ostringstream w;
  float v = 0.4;
  netflix_print(w, v);
  ASSERT_EQ("0.4\n", w.str());
}

TEST(NetflixFixture, print2) {
  ostringstream w;
  float v = 1.1;
  netflix_print(w, v);
  ASSERT_EQ("1.1\n", w.str());
}

TEST(NetflixFixture, print3) {
  ostringstream w;
  float v = 3.2;
  netflix_print(w, v);
  ASSERT_EQ("3.2\n", w.str());
}

TEST(NetflixFixture, print4) {
  ostringstream w;
  float v = 4.3;
  netflix_print(w, v);
  ASSERT_EQ("4.3\n", w.str());
}

TEST(NetflixFixture, rmse1) {
  float sqerr = 98;
  int num = 2;
  float rmse_result = netflix_rmse(sqerr, num);
  ASSERT_EQ(7f, rmse_result);
}

TEST(NetflixFixture, rmse2) {
  float sqerr = 128;
  int num = 2;
  float rmse_result = netflix_rmse(sqerr, num);
  ASSERT_EQ(64f, rmse_result);
}

TEST(NetflixFixture, rmse3) {
  float sqerr = 27;
  int num = 3;
  float rmse_result = netflix_rmse(sqerr, num);
  ASSERT_EQ(9f, rmse_result);
}