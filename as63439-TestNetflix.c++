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
#include <vector>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ------------
// split
// ------------

TEST(NetflixFixture, split_1) {
    string s = "123 456";
    char c = ' ';
    int size = 2;
    vector<string> string_vector = split(s, c);
    ASSERT_EQ(string_vector[0], "123");
    ASSERT_EQ(string_vector[1], "456");
    ASSERT_EQ(string_vector.size(), size);
}

TEST(NetflixFixture, split_2) {
  string s = "123";
  char c = ' ';
  int size = 1;
  vector <string> string_vector = split(s, c);
  ASSERT_EQ(string_vector[0], "123");
  ASSERT_EQ(string_vector.size(), size);
}

TEST(NetflixFixture, split_3) {
  string s = "abc:123 456:xyz: ";
  char c = ':';
  int size = 4;
  vector <string> string_vector = split(s, c);
  ASSERT_EQ(string_vector[0], "abc");
  ASSERT_EQ(string_vector[1], "123 456");
  ASSERT_EQ(string_vector[2], "xyz");
  ASSERT_EQ(string_vector[3], " ");
  ASSERT_EQ(string_vector.size(), size);
}

TEST(NetflixFixture, split_4) {
  string s = "";
  char c = ' ';
  int size = 0;
  vector <string> string_vector = split(s, c);
  ASSERT_EQ(string_vector.size(), size);
}

TEST(NetflixFixture, split_5) {
  string s = "1 1";
  char c = ' ';
  int size = 2;
  vector <string> string_vector = split(s, c);
  ASSERT_EQ(string_vector[0], "1");
  ASSERT_EQ(string_vector[1], "1");
  ASSERT_EQ(string_vector.size(), size);
}

TEST(NetflixFixture, split_6) {
  string s = "1.0 asdf ";
  char c = ' ';
  int size = 2;
  vector <string> string_vector = split(s, c);
  ASSERT_EQ(string_vector[0], "1.0");
  ASSERT_EQ(string_vector[1], "asdf");
  ASSERT_EQ(string_vector.size(), size);
}
// ------------
// parse_cache
// ------------

TEST(NetflixFixture, parse_cache_1) {
  char const* url[] = {"www.cs.utexas.edu", "/users/downing/netflix-cs371p/cyt276-as63439-avg-movie-ratings-testing.txt"};
  map<int, double> map;
  ostringstream w;
  int result = parse_cache(url, map, w);
  ASSERT_EQ(result, 0);
}

TEST(NetflixFixture, parse_cache_2) {
  char const* url[] = {"www.cs.utexas.edu", "/users/downing/netflix-cs371p/cyt276-as63439-avg-customer-ratings-testing.txt"};
  map<int, double> map;
  ostringstream w;
  int result = parse_cache(url, map, w);
  ASSERT_EQ(result, 0);
}

TEST(NetflixFixture, parse_cache_3) {
  char const* url[] = {"www.cs.utexas.edu", "/users/downing/netflix-cs371p/cyt276-as63439-avg-customer-ratings2.txt"};  // Bad URL
  map<int, double> map;
  ostringstream w;
  int result = parse_cache(url, map, w);
  ASSERT_EQ(result, 1);
}

// ------------
// parse_actual_cache
// ------------

TEST(NetflixFixture, parse_actual_cache_1) {
  char const* url[] = {"www.cs.utexas.edu", "/users/downing/netflix-cs371p/cyt276-as63439-ids-and-actual-ratings-testing.txt"};
  map<int, map<int, int>> map;
  ostringstream w;
  int result = parse_actual_cache(url, map, w);
  ASSERT_EQ(result, 0);
}

TEST(NetflixFixture, parse_acutal_cache_3) {
  char const* url[] = {"www.cs.utexas.edu", "/users/downing/netflix-cs371p/cyt276-as63439-ids-and-ratings.txt"};  // Bad URL
  map<int, map<int, int>> map;
  ostringstream w;
  int result = parse_actual_cache(url, map, w);
  ASSERT_EQ(result, 1);
}

// ------------
// netflix_predict
// ------------

TEST(NetflixFixture, netflix_predict_1) {
  istringstream r("1002:\n2174660");
  ostringstream w;
  netflix_predict(r, w);
  ASSERT_EQ(w.str(), "1002:\n3.1\nRMSE: 0.89\n");
}
