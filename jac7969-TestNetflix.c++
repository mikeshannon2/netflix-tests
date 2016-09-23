// --------------------------------
// projects/Netflix.c++
// Copyright (C) 2016
// Jacque Corona and Nikita Zamwar 
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <unordered_map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

/*TEST(NetflixFixture, read) {
    istringstream r("1 10\n");
    int           i;
    int           j;
    const bool b = Netflix_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ( 1, i);
    ASSERT_EQ(10, j);}
*/
// ----
// predict
// ----

TEST(NetflixFixture, predict_1) {
    std::unordered_map<int,double> movie_avg;
    std::unordered_map<int,double> customer_avg;
    
    movie_avg[10043] = 4.10;
    customer_avg[202667] = 3.21;

    // movie_avg.insert({10043, 4.10});
    // customer_avg.insert({202667, 3.21});

    double v = Netflix_predict(10043, 202667, movie_avg, customer_avg);
    ASSERT_TRUE(3.61 != v);}

TEST(NetflixFixture, predict_2) {
    std::unordered_map<int,double> movie_avg;
    std::unordered_map<int,double> customer_avg;

    movie_avg.insert({10000, 2.90});
    customer_avg.insert({200206, 4.41});

    const double v = Netflix_predict(10000, 200206, movie_avg, customer_avg);
    ASSERT_EQ(3.61, v);}

TEST(NetflixFixture, predict_3) {
    std::unordered_map<int,double> movie_avg;
    std::unordered_map<int,double> customer_avg;

    movie_avg.insert({10015, 3.82});
    customer_avg.insert({2162539, 3.33});

    const double v = Netflix_predict(10015, 2162539, movie_avg, customer_avg);
    ASSERT_TRUE(3.45 != v);}


// -----
// solve
// -----

/*TEST(NetflixFixture, solve) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    Netflix_solve(r, w);
ASSERT_EQ("1 10 1\n100 200 1\n201 210 1\n900 1000 1\n", w.str());}*/

/*TEST(NetflixFixture, solve) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    Netflix_solve(r, w);
ASSERT_EQ("1 10 1\n100 200 1\n201 210 1\n900 1000 1\n", w.str());}*/