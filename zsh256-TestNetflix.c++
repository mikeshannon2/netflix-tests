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

TEST(NetflixFixture, read) {
    istringstream r("1 10\n");
    int           i;
    int           j;
    const bool b = netflix_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ( 1, i);
    ASSERT_EQ(10, j);}

// ----
// eval
// ----
std::map<int,double> movAvg;
std::map<int,double> usrAvg;
//TODO: add fake "actualRatings" cache for tests to match netflix.c++ parameters


TEST(NetflixFixture, eval_1) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    const double v = netflix_eval(1, 1, &usrAvg, &movAvg);
    //cout<< v << endl << endl << endl << endl << endl;
    ASSERT_LE(4.1-v, 0.00000001);}

TEST(NetflixFixture, eval_2) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    const double v = netflix_eval(2, 2, &usrAvg, &movAvg);
    //cout<< v << endl << endl << endl << endl << endl;
    ASSERT_LE(1.6-v, 0.00000001);}

TEST(NetflixFixture, eval_3) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    const double v = netflix_eval(3, 3, &usrAvg, &movAvg);
    ASSERT_LE(2.5-v, 0.00000001);}

TEST(NetflixFixture, eval_4) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    const double v = netflix_eval(4, 4, &usrAvg, &movAvg);
    ASSERT_LE(1-v, 0.00000001);}

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
    movAvg[1] = 4.2;
    movAvg[2] = 3.0;
    movAvg[3] = 2.0;
    movAvg[4] = 1.5;
    usrAvg[1] = 3.6;
    usrAvg[2] = 2.3;
    usrAvg[3] = 4.2;
    usrAvg[4] = 1.1;
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    netflix_solve(r, w, &usrAvg, &movAvg);
    ASSERT_EQ("1 10 1\n100 200 1\n201 210 1\n900 1000 1\n", w.str());}
