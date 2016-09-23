#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

//Testing netflix_read
TEST(NetflixFixture, read_1) {
    istringstream r("1\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "1", i);
}

TEST(NetflixFixture, read_2) {
    istringstream r("17770\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "17770", i);
}

TEST(NetflixFixture, read_3) {
    istringstream r("3\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "3", i);
}

//Testing netflix_eval
TEST(NetflixFixture, eval_1) {
    const double v = netflix_eval(1, 5);
    ASSERT_EQ(2.3, v);}

TEST(NetflixFixture, eval_2) {
    const double v = netflix_eval(2.4, 3.4);
    ASSERT_EQ(2.1, v);}

TEST(NetflixFixture, eval_3) {
    const double v = netflix_eval(4.2, 1.9);
    ASSERT_EQ(2.4, v);}

TEST(NetflixFixture, solve_caches_1) {
    istringstream r("12:\n18\n32");
    ostringstream w;
    istringstream movieCache("12 4.3\n44 3.4\n");
    istringstream userCache("18 2.4\n32 1.8\n");
    istringstream ratingsKey("12 18 3\n12 32 2\n");
    netflix_solve_caches(r, w, movieCache, userCache, ratingsKey);
    ASSERT_EQ("12:\n3.0\n2.4\nRMSE: 0.28\n", w.str());}

TEST(NetflixFixture, solve_caches_2) {
    istringstream r("15:\n24\n25");
    ostringstream w;
    istringstream movieCache("15 4.9\n65 2.4\n");
    istringstream userCache("24 2.1\n25 4.6\n");
    istringstream ratingsKey("15 24 3\n15 25 2\n");
    netflix_solve_caches(r, w, movieCache, userCache, ratingsKey);
    ASSERT_EQ("15:\n3.3\n5.0\nRMSE: 2.13\n", w.str());}

TEST(NetflixFixture, solve_caches_3) {
    istringstream r("12:\n18\n");
    ostringstream w;
    istringstream movieCache("12 1\n");
    istringstream userCache("18 1\n");
    istringstream ratingsKey("12 18 1\n");
    netflix_solve_caches(r, w, movieCache, userCache, ratingsKey);
    ASSERT_EQ("12:\n1.0\nRMSE: 0.00\n", w.str());}

TEST(NetflixFixture, solve_caches_4) {
    istringstream r("22:\n55\n");
    ostringstream w;
    istringstream movieCache("22 2.4\n");
    istringstream userCache("55 3.6\n");
    istringstream ratingsKey("22 55 1\n");
    netflix_solve_caches(r, w, movieCache, userCache, ratingsKey);
    ASSERT_EQ("22:\n2.3\nRMSE: 1.30\n", w.str());}

TEST(NetflixFixture, cache_1) {
    istringstream r("12 2.5");
    map<string, double> cache = getCache(r);
    ASSERT_EQ(cache["12"], 2.5);}

TEST(NetflixFixture, cache_2) {
    istringstream r("22 1.5");
    map<string, double> cache = getCache(r);
    ASSERT_EQ(cache["22"], 1.5);}

TEST(NetflixFixture, cache_3) {
    istringstream r("12 2.5\n34 1.7\n88 2.9");
    map<string, double> cache = getCache(r);
    ASSERT_EQ(cache["12"], 2.5);
    ASSERT_EQ(cache["34"], 1.7);
    ASSERT_EQ(cache["88"], 2.9);}

TEST(NetflixFixture, cache_4) {
    istringstream r("12 2.5\n33 3.9");
    map<string, double> cache = getCache(r);
    ASSERT_EQ(cache["12"], 2.5);
    ASSERT_EQ(cache["33"], 3.9);
}

TEST(NetflixFixture, rcache_1) {
    istringstream r("12 2 2");
    map<string, map<string, int> > cache = getRatingCache(r);
    ASSERT_EQ(cache["12"]["2"], 2);}

TEST(NetflixFixture, rcache_2) {
    istringstream r("22 11 1");
    map<string, map<string, int> > cache = getRatingCache(r);
    ASSERT_EQ(cache["22"]["11"], 1);}

TEST(NetflixFixture, rcache_3) {
    istringstream r("12 22 3\n34 17 2\n88 29 1");
    map<string, map<string, int> > cache = getRatingCache(r);
    ASSERT_EQ(cache["12"]["22"], 3);
    ASSERT_EQ(cache["34"]["17"], 2);
    ASSERT_EQ(cache["88"]["29"], 1);}

TEST(NetflixFixture, rcache_4) {
    istringstream r("12 2 5\n33 39 2");
    map<string, map<string, int> > cache = getRatingCache(r);
    ASSERT_EQ(cache["12"]["2"], 5);
    ASSERT_EQ(cache["33"]["39"], 2);
}