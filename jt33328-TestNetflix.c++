// --------------------------------------------------------
// Name: Jeannette Tang & Jared Churchman
// UTEID: jt33328 & jlc5526
// GitHub Name: jeannettetang & Jchurchman100
// Email: jeannette.tang@utexas.edu & jchurchman@utexas.edu
// --------------------------------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  float printThis = 1;
  netflix_print(w, printThis);
  ASSERT_EQ("1\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  float printThis = 3.6;
  netflix_print(w, printThis);
  ASSERT_EQ("3.6\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  float printThis = 2346.0000;
  netflix_print(w, printThis);
  ASSERT_EQ("2346\n", w.str());
}

// --------
// truncate
// --------

TEST(NetflixFixture, truncate_1) {
  float num = netflix_truncate(353);
  ASSERT_EQ(353.00, num);
}

TEST(NetflixFixture, truncate_2) {
  float num = netflix_truncate(23.3);
  EXPECT_NEAR(23.30, num, 0.01);
}

TEST(NetflixFixture, truncate_3) {
  float num = netflix_truncate(23.43425);
  EXPECT_NEAR(23.43, num, 0.01);
}

// ------
// actual
// ------

TEST(NetflixFixture, actual_1) {
  istringstream actualCacheFile("10947: 1062491,5\n1843: 122268,3\n");
  MovieInfo cache = netflix_actual(actualCacheFile);
  EXPECT_FLOAT_EQ(5, cache["10947"]["1062491"]);
}

TEST(NetflixFixture, actual_2) {
  istringstream actualCacheFile("10947: 1062491,5\n1843: 122268,3\n");
  MovieInfo cache = netflix_actual(actualCacheFile);
  EXPECT_FLOAT_EQ(3, cache["1843"]["122268"]);
}

TEST(NetflixFixture, actual_3) {
  istringstream actualCacheFile("1007: 95090,4\n10: 1952305,3\n");
  MovieInfo cache = netflix_actual(actualCacheFile);
  EXPECT_FLOAT_EQ(4, cache["1007"]["95090"]);
}

// -----
// cache
// -----

TEST(NetflixFixture, cache_1) {
  istringstream movieCacheFile("10947 4.30887\n1843 3.21917\n");
  Cache cache = netflix_cache(movieCacheFile);
  EXPECT_FLOAT_EQ(4.30887, cache["10947"]);
}

TEST(NetflixFixture, cache_2) {
  istringstream customerCacheFile("1062491 3.84\n122268 4.54\n");
  Cache cache = netflix_cache(customerCacheFile);
  EXPECT_FLOAT_EQ(3.84, cache["1062491"]);
}

TEST(NetflixFixture, cache_3) {
  istringstream customerCacheFile("1062491 3.84\n122268 4.54\n");
  Cache cache = netflix_cache(customerCacheFile);
  EXPECT_FLOAT_EQ(4.54, cache["122268"]);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
  istringstream r("1843:\n2339194\n13117:\n1084702\n");
  Cache movieCache;
  movieCache["1843"] = 3.21917;
  movieCache["13117"] = 3.01899;
  Cache customerCache;
  customerCache["2339194"] = 3.58;
  customerCache["1084702"] = 3.22;
  MovieInfo actualCache;
  actualCache["1843"]["2339194"] = 4;
  actualCache["13117"]["1084702"] = 2;
  ostringstream w;
  float rmse = netflix_eval(r, movieCache, customerCache, actualCache, w);
  EXPECT_FLOAT_EQ(0.72969204, rmse);
}

TEST(NetflixFixture, eval_2) {
  istringstream r("3864:\n634075\n1202:\n1989338\n");
  Cache movieCache;
  movieCache["3864"] = 4.2367;
  movieCache["1202"] = 3.77066;
  Cache customerCache;
  customerCache["634075"] = 2.38;
  customerCache["1989338"] = 2.98;
  MovieInfo actualCache;
  actualCache["3864"]["634075"] = 3;
  actualCache["1202"]["1989338"] = 3;
  ostringstream w;
  float rmse = netflix_eval(r, movieCache, customerCache, actualCache, w);
  EXPECT_FLOAT_EQ(1.0059123, rmse);
}

TEST(NetflixFixture, eval_3) {
  istringstream r("1007:\n95090\n10:\n1952305\n");
  Cache movieCache;
  movieCache["1007"] = 3.25472;
  movieCache["10"] = 3.18072;
  Cache customerCache;
  customerCache["95090"] = 3.46;
  customerCache["1952305"] = 3.41;
  MovieInfo actualCache;
  actualCache["1007"]["95090"] = 4;
  actualCache["10"]["1952305"] = 3;
  ostringstream w;
  float rmse = netflix_eval(r, movieCache, customerCache, actualCache, w);
  EXPECT_FLOAT_EQ(0.52108157, rmse);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1007:\n95090\n10:\n1952305\n");
  ostringstream w;
  istringstream movieCacheFile("1007 3.25472\n10 3.18072\n");
  istringstream customerCacheFile("95090 3.46\n1952305 3.41\n");
  istringstream actualCacheFile("1007: 95090,4\n10: 1952305,3\n");
  netflix_solve(r, movieCacheFile, customerCacheFile, actualCacheFile, w);
  ASSERT_EQ("1007:\n3.27972\n10:\n3.15572\nRMSE: 0.521082\n", w.str());
}


TEST(NetflixFixture, solve_2) {
  istringstream r("3864:\n634075\n1202:\n1989338\n");
  ostringstream w;
  istringstream movieCacheFile("3864 4.2367\n1202 3.77066\n");
  istringstream customerCacheFile("634075 2.38\n1989338 2.98\n");
  istringstream actualCacheFile("3864: 634075,3\n1202: 1989338,3\n");
  netflix_solve(r, movieCacheFile, customerCacheFile, actualCacheFile, w);
  ASSERT_EQ("3864:\n3.9367\n1202:\n4.07066\nRMSE: 1.00591\n", w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("1843:\n2339194\n13117:\n1084702\n");
  ostringstream w;
  istringstream movieCacheFile("1843 3.21917\n13117 3.01899\n");
  istringstream customerCacheFile("2339194 3.58\n1084702 3.22\n");
  istringstream actualCacheFile("1843: 2339194,4\n13117: 1084702,2\n");
  netflix_solve(r, movieCacheFile, customerCacheFile, actualCacheFile, w);
  ASSERT_EQ("1843:\n3.39917\n13117:\n2.83899\nRMSE: 0.729692\n", w.str());
}