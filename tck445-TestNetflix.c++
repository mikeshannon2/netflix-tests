// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------
// used for skeleton of projects/netflix/TestNetflix.c++

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"


/*
 * 
 * float user_avg = data_cache.get_customer(*user).rating_avg;
      float movie_avg = data_cache.get_movie(*movie).rating_avg;
      float guess = truncate_to_2_dec((user_avg + movie_avg) / 2);
      //maintain list of errors
      float actual = truth_cache.get_rating(*user, *movie);
      */
class MockTC : public TC{
  public:
  MockTC(){
  }
  uint32_t get_rating(uint32_t customer_id, uint32_t movie_id) {
    return 3;
  }
};

class MockDC : public DC {
  public:
  AggregatedRating r;
  MockDC() : r(){
  }
  AggregatedRating& get_customer(uint32_t customer_id) {
    r = AggregatedRating();
    return r;
  }
  AggregatedRating& get_movie(uint32_t movie_id) {
    r = AggregatedRating();
    return r;
  }
};

using namespace std;

const string DATA_CACHE_LOCATION = "/u/downing/public_html/netflix-cs371p/xz4493-data-cache.bin";
const string PROBE_CACHE_LOCATION = "/u/downing/public_html/netflix-cs371p/az5385-probe-lookup.bin";

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  MockDC data_cache = MockDC();
  MockTC truth_cache = MockTC();
  istringstream r("10424:\n71390\n");
  ostringstream w;
  netflix_solve(r, w, data_cache, truth_cache);
  ASSERT_EQ("10424:\n0\nRMSE : 3\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  MockDC data_cache = MockDC();
  MockTC truth_cache = MockTC();
  istringstream r("10422:\n729704\n1346514\n");
  ostringstream w;
  netflix_solve(r, w, data_cache, truth_cache);
  ASSERT_EQ("10422:\n0\n0\nRMSE : 3\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  MockDC data_cache = MockDC();
  MockTC truth_cache = MockTC();
  istringstream r("10424:\n371781\n88897:\n1716862");
  ostringstream w;
  netflix_solve(r, w, data_cache, truth_cache);
  ASSERT_EQ("10424:\n0\n88897:\n0\nRMSE : 3\n", w.str());
}

// -----
// truncate_to_2_dec
// -----

TEST(NetflixFixture, truncate_to_2_dec_1) {
  float f = truncate_to_2_dec(100.999);
  ASSERT_EQ(100.99f, f);
}

TEST(NetflixFixture, truncate_to_2_dec_2) {
  float f = truncate_to_2_dec(0.511);
  ASSERT_EQ(0.51f, f);
}

TEST(NetflixFixture, truncate_to_2_dec_3) {
  float f = truncate_to_2_dec(52000);
  ASSERT_EQ(52000, f);
}

// -----
// rmse
// -----

TEST(NetflixFixture, rmse_1) {
  vector<float> err;
  err.push_back(3);
  ASSERT_EQ(3, rmse(err));
}

TEST(NetflixFixture, rmse_2) {
  vector<float> err;
  err.push_back(3);
  err.push_back(5);
  err.push_back(1);
  ASSERT_EQ(3.41f, rmse(err));
}

TEST(NetflixFixture, rmse_3) {
  vector<float> err;
  err.push_back(2);
  err.push_back(2);
  err.push_back(2);
  err.push_back(2);
  ASSERT_EQ(2, rmse(err));
}

// -----
// ends_with_colon
// -----

TEST(NetflixFixture, ends_with_colon_1) {
  string s = "101";
  ASSERT_EQ(false, ends_with_colon(s));
}

TEST(NetflixFixture, ends_with_colon_2) {
  string s = "101\n";
  ASSERT_EQ(false, ends_with_colon(s));
}

TEST(NetflixFixture, ends_with_colon_3) {
  string s = "101:";
  ASSERT_EQ(true, ends_with_colon(s));
}
// -----
// netflix_read
// -----

TEST(NetflixFixture, netflix_read_1) {
  istringstream r("10424:\n71390\n");
  vector<int> v;
  map<int,vector<int>> m;
  
  netflix_read(r,v,m);
  
  ASSERT_EQ(v[0], 10424);
  ASSERT_EQ((*m.find(10424)).second[0],71390);
}

TEST(NetflixFixture, netflix_read_2) {
  istringstream r("10422:\n729704\n1346514\n");
  vector<int> v;
  map<int,vector<int>> m;
  
  netflix_read(r,v,m);
  
  ASSERT_EQ(v[0], 10422);
  ASSERT_EQ((*m.find(10422)).second[0],729704);
  ASSERT_EQ((*m.find(10422)).second[1],1346514);
}

TEST(NetflixFixture, netflix_read_3) {
  istringstream r("10424:\n371781\n88897:\n1716862");
  vector<int> v;
  map<int,vector<int>> m;
  
  netflix_read(r,v,m);
  
  ASSERT_EQ(v[0], 10424);
  ASSERT_EQ(v[1], 88897);
  ASSERT_EQ((*m.find(10424)).second[0],371781);
  ASSERT_EQ((*m.find(88897)).second[0],1716862);
}

