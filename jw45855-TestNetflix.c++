// --------------------------------
// Jasper Wu
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream>      // cout, endl
#include <sstream>       // istringtstream, ostringstream
#include <string>        // string
#include <utility>       // pair
#include <unordered_map> // unordered map

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("1:\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "1:", i);}

TEST(NetflixFixture, read_2) {
    istringstream r("9999:");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "9999:", i);}


TEST(NetflixFixture, read_3) {
    istringstream r("12345");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ( "12345", i);}

// ----
// rsme
// ----
TEST(NetflixFixture, rsme_1) {
    const bool b = netflix_rsme(1.0);
    ASSERT_FALSE(b);}

TEST(NetflixFixture, rsme_2) {
    const bool b = netflix_rsme(3.0);
    ASSERT_FALSE(b);}

TEST(NetflixFixture, rsme_3) {
    const bool b = netflix_rsme(5.0);
    ASSERT_FALSE(b);}

// // ----
// // eval
// // ----

TEST(NetflixFixture, eval_1) {
    const float v = netflix_eval("100:");
    ASSERT_EQ(-1 ,v);}

TEST(NetflixFixture, eval_2) {
    const float v = netflix_eval("1:");
    ASSERT_EQ(-1 ,v);}

TEST(NetflixFixture, eval_3) {
    const float v = netflix_eval("9999:");
    ASSERT_EQ(-1 ,v);}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream w;
    netflix_print(w, "100:", -1, 2);
    ASSERT_EQ("100:\n", w.str());}

TEST(NetflixFixture, print_2) {
    ostringstream w;
    netflix_print(w, "test", 3.01, 1);
    ASSERT_EQ("3.0\n", w.str());}

TEST(NetflixFixture, print_3) {
    ostringstream w;
    netflix_print(w, "test2", 4.452, 1);
    ASSERT_EQ("4.5\n", w.str());}

// -----
// cache
// -----

TEST(NetflixFixture, cache_1) {
    const bool b = netflix_cache();
    ASSERT_TRUE(b);}

TEST(NetflixFixture, cache_2) {
    const bool b = netflix_cache();
    ASSERT_TRUE(b);}

TEST(NetflixFixture, cache_3) {
    const bool b = netflix_cache();
    ASSERT_TRUE(b);}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("1:\n30878\n2647871\n1283744\n");
    ostringstream w;
    netflix_solve(r, w);
    ASSERT_TRUE( w.str().find("RSME:") != string::npos);}

TEST(NetflixFixture, solve_2) {
    istringstream r("10:\n1952305\n1531863\n");
    ostringstream w;
    netflix_solve(r, w);
    ASSERT_TRUE( w.str().find("RSME:") != string::npos);}

TEST(NetflixFixture, solve_3) {
    istringstream r("1000:\n2326571\n977808\n1010534\n");
    ostringstream w;
    netflix_solve(r, w);
    ASSERT_TRUE( w.str().find("RSME:") != string::npos);}
