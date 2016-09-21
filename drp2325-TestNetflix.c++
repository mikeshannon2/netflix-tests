// --------------------------------
// projects/netflix/TestNetflix.c++
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>   // vector

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -----
// error
// -----
// --------------------------------
// projects/netflix/TestNetflix.c++
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>   // vector

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -------
// predict
// -------

TEST(NetflixFixture, predict_1) {
  const float v = netflix_predict(1, 1337);
  ASSERT_GE(v, 1);
  ASSERT_LE(v, 5);
}

TEST(NetflixFixture, predict_2) {
  const float v = netflix_predict(2, 1337);
  ASSERT_GE(v, 1);
  ASSERT_LE(v, 5);
}

TEST(NetflixFixture, predict_3) {
  const float v = netflix_predict(3, 13371);
  ASSERT_GE(v, 1);
  ASSERT_LE(v, 5);
}

TEST(NetflixFixture, predict_4) {
  const float v = netflix_predict(4, 13372);
  ASSERT_GE(v, 1);
  ASSERT_LE(v, 5);
}

TEST(NetflixFixture, predict_5) {
  const float v = netflix_predict(1, 1337);
  ASSERT_GE(v, 1);
  ASSERT_LE(v, 5);
}

// ---------
// readcache
// ---------

/* Check movie average ratings cache */
/* first line in cache */
TEST(NetflixFixture, readcache_1) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(mavg[15802], 4.04);
}

TEST(NetflixFixture, readcache_2) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(mavg[11237], 3.86);
}

/* last line in cache */
TEST(NetflixFixture, readcache_3) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(mavg[15762], 3.22);
}

/* Check user average ratings cache */
/* first line in cache */
TEST(NetflixFixture, readcache_4) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(uavg[1174466], 3.16);
}

TEST(NetflixFixture, readcache_5) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(uavg[1543642], 3.85);
}

/* last line in cache */
TEST(NetflixFixture, readcache_6) {
  netflix_readcache();
  ASSERT_FLOAT_EQ(uavg[233827], 3.58);
}

/* Check actual movie ratings cache */
/* first line in cache */
TEST(NetflixFixture, readcache_7) {
  netflix_readcache();
  ASSERT_EQ(actual[1][30878], 4);
}

TEST(NetflixFixture, readcache_8) {
  netflix_readcache();
  ASSERT_EQ(actual[9996][1720226], 3);
}

/* last line in cache */
TEST(NetflixFixture, readcache_9) {
  netflix_readcache();
  ASSERT_EQ(actual[9999][1473765], 2);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  string s;

  istringstream iss("1337:\n920882");
  ostringstream oss;
  netflix_solve(iss, oss);
  istringstream output(oss.str());

  getline(output, s);
  ASSERT_EQ("1337:", s);
  getline(output, s);
  ASSERT_EQ(s.size(), 3);
  getline(output, s);
  ASSERT_EQ(s.size(), 10);
}

TEST(NetflixFixture, solve_2) {
  string s;

  istringstream iss("1337:\n920882\n2559917\n800491\n2028870\n1379178\n");
  ostringstream oss;
  netflix_solve(iss, oss);
  istringstream output(oss.str());

  getline(output, s);
  ASSERT_EQ("1337:", s);
  getline(output, s);
  getline(output, s);
  getline(output, s);
  getline(output, s);
  getline(output, s);
  ASSERT_EQ(s.size(), 3);
  getline(output, s);
  ASSERT_EQ(s.size(), 10);
}
