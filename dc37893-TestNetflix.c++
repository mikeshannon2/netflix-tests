// --------------------------------
// projects/netflix/Testnetflix.c++
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
#include <map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("1\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("1", i);}

TEST(NetflixFixture, read_2) {
    istringstream r("2\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("2", i);}

TEST(NetflixFixture, read_3) {
    istringstream r("3\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("3", i);}

TEST(NetflixFixture, read_4) {
    istringstream r("4\n");
    string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("4", i);}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
    ostringstream w;
    map<string, double> avgmRating;
    map<string, double> mstd;
    map<int, double> uavgd;
    map<string, int> user2rating; 
    int y = 378466;
    string x = "1:";
    avgmRating[x] = 4.04;
    mstd[x] = 1.13;
    uavgd[y] = 1.75;
    user2rating["378466"] = 4;

    double b = netflix_eval (w, x, y, avgmRating, mstd, uavgd, user2rating);
    ASSERT_DOUBLE_EQ(b, 36.210306250000002);}

TEST(NetflixFixture, eval_2) {
    ostringstream w;
    map<string, double> avgmRating;
    map<string, double> mstd;
    map<int, double> uavgd;
    map<string, int> user2rating; 
    int y = 43921;
    string x = "10:";
    avgmRating[x] = 3.07;
    mstd[x] = -.07;
    uavgd[y] = 1.06;
    user2rating["43921"] = 3;

    double b = netflix_eval (w, x, y, avgmRating, mstd, uavgd, user2rating);
    ASSERT_DOUBLE_EQ(b, 8.9748176399999995);}

TEST(NetflixFixture, eval_3) {
    ostringstream w;
    map<string, double> avgmRating;
    map<string, double> mstd;
    map<int, double> uavgd;
    map<string, int> user2rating; 
    int y = 232348;
    string x = "1:";
    avgmRating[x] = 2.67;
    mstd[x] = 0.57;
    uavgd[y] = 0.96;
    user2rating["232348"] = 4;

    double b = netflix_eval (w, x, y, avgmRating, mstd, uavgd, user2rating);
    ASSERT_DOUBLE_EQ(b, 10.35037584);}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("10:\n1952305\n1531863\n");
    ostringstream w;
    istringstream arCache("10 1952305 3\n10 1531863 3\n");
    istringstream mCache("10 3.04\n");
    istringstream mvCache("10 1.2806\n");
    istringstream usCache("1952305 0.755\n 1531863 -0.2686\n");
    netflix_solve(r, w, arCache, mCache, mvCache, usCache);
    ASSERT_EQ("10:\n3.9\n2.7\nRMSE: 0.66\n", w.str());}

TEST(NetflixFixture, solve_2) {
    istringstream r("1:\n30878\n2647871\n");
    ostringstream w;
    istringstream arCache("1 30878 4\n1 2647871 4\n");
    istringstream mCache("1 3.17\n");
    istringstream mvCache("1 0.954\n");
    istringstream usCache("30878 -1.25\n 2647871 0.118\n");
    netflix_solve(r, w, arCache, mCache, mvCache, usCache);
    ASSERT_EQ("1:\n1.9\n3.3\nRMSE: 1.54\n", w.str());}

TEST(NetflixFixture, solve_3) {
    istringstream r("1000:\n2326571\n977808\n");
    ostringstream w;
    istringstream arCache("1000 2326571 3\n1000 977808 3\n");
    istringstream mCache("1000 2.27\n");
    istringstream mvCache("1000 1.59\n");
    istringstream usCache("2326571 1.32\n 977808 0.873\n");
    netflix_solve(r, w, arCache, mCache, mvCache, usCache);
    ASSERT_EQ("1000:\n3.9\n3.4\nRMSE: 0.71\n", w.str());}

TEST(NetflixFixture, solve_4) {
    istringstream r("10000:\n200206\n534108\n");
    ostringstream w;
    istringstream arCache("10000 200206 5\n10000 523108 4\n");
    istringstream mCache("10000 3.77\n");
    istringstream mvCache("10000 0.98\n");
    istringstream usCache("200206 -0.67\n 534108 -0.2686\n");
    netflix_solve(r, w, arCache, mCache, mvCache, usCache);
    ASSERT_EQ("10000:\n3.1\n3.5\nRMSE: 2.82\n", w.str());}
