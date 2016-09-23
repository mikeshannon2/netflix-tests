// --------------------------------
// projects/netflix/TestNetflix.c++
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
std::map<int,double> movAvg;
std::map<int,double> usrAvg;
TEST(NetflixFixture, read) {
    istringstream r("1:\n30878\n2647871\n");
    ostringstream w;
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    usrAvg[30878] = 3.7;
    usrAvg[2647871] = 3.7;
    double i = 0;
    int j = 0;
    bool b = netflix_read(r, w, &usrAvg, &movAvg, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(2, j);}

// ----
// eval
// ----
//TODO: add fake "actualRatings" cache for tests to match netflix.c++ parameters


TEST(NetflixFixture, eval_1) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(1, 1, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(4.1-v, 0.00000001);}

TEST(NetflixFixture, eval_2) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(2, 2, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(1.6-v, 0.00000001);}

TEST(NetflixFixture, eval_3) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(3, 3, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(2.5-v, 0.00000001);}

TEST(NetflixFixture, eval_4) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(4, 4, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(1-v, 0.00000001);}

TEST(NetflixFixture, eval_5) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(5, 5, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(2-v, 0.00000001);}

TEST(NetflixFixture, eval_6) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(6, 6, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(2.5-v, 0.00000001);}

TEST(NetflixFixture, eval_7) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(7, 7, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(3-v, 0.00000001);}

TEST(NetflixFixture, eval_8) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    double tempA = 0;
    int tempB = 0;
    const double v = netflix_eval(8, 8, &usrAvg, &movAvg, 3, tempA, tempB);
    ASSERT_LE(4-v, 0.00000001);}

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    movAvg[5] = 2.0;
    movAvg[6] = 2.5;
    movAvg[7] = 3.0;
    movAvg[8] = 4.0;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    usrAvg[5] = 3.7;
    usrAvg[6] = 3.7;
    usrAvg[7] = 3.7;
    usrAvg[8] = 3.7;
    usrAvg[30878] = 3.7;
    usrAvg[2647871] = 3.7;
    istringstream r("1:\n30878\n2647871\n");
    ostringstream w;
    netflix_solve(r, w, &usrAvg, &movAvg);
    ASSERT_EQ("1:\n4.2\n4.2\nRMSE: 0.2\n", w.str());}
