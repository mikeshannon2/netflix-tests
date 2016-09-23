// --------------------------------
// Copyright (C) 2016
// Jorge Zapien and Linh Nguyen
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("1:\n");
    int i;
    const int b = netflix_read(r, i);
    ASSERT_EQ(1, b);
    ASSERT_EQ(1, i);
}

TEST(NetflixFixture, read_2) {
    istringstream r("6531531\n");
    int i;
    const int b = netflix_read(r, i);
    ASSERT_EQ(      2, b);
    ASSERT_EQ(6531531, i);
}

TEST(NetflixFixture, read_3) {
    istringstream r("0:\n");
    int i;
    const int b = netflix_read(r, i);
    ASSERT_EQ(1, b);
    ASSERT_EQ(0, i);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
    const double v = netflix_eval(4.0, 4.5);
    ASSERT_FLOAT_EQ(4.8, v);
}

TEST(NetflixFixture, eval_2) {
    const double v = netflix_eval(3.2, 5.0);
    ASSERT_FLOAT_EQ(4.5, v);
}

TEST(NetflixFixture, eval_3) {
    const double v = netflix_eval(2.2, 3.5);
    ASSERT_FLOAT_EQ(2.0, v);
}

TEST(NetflixFixture, eval_4) {
    const double v = netflix_eval(1.2, 5.0);
    ASSERT_FLOAT_EQ(2.5, v);
}

TEST(NetflixFixture, eval_5) {
    const double v = netflix_eval(4.2, 3.5);
    ASSERT_FLOAT_EQ(4.0, v);
}

TEST(NetflixFixture, eval_6) {
    const double v = netflix_eval(5.0, 2.4);
    ASSERT_FLOAT_EQ(3.7, v);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("1:\n10\n9\n2:\n5\n");
    ostringstream w;

    unordered_map<int, double> avg_movie_ratings;
    avg_movie_ratings[1] = 2.5;
    avg_movie_ratings[2] = 3.5;
    unordered_map<int, double> avg_customer_ratings;
    avg_customer_ratings[10] = 5.0;
    avg_customer_ratings[9] = 4.0;
    avg_customer_ratings[2] = 3.5;
    avg_customer_ratings[5] = 2.5;
    unordered_map<int, unordered_map<int, int>> actual_ratings;
    actual_ratings[1][10] = 4;
    actual_ratings[1][9] = 3;
    actual_ratings[1][2] = 2;
    actual_ratings[2][5] = 1;

    netflix_solve(r, w, avg_movie_ratings, avg_customer_ratings, actual_ratings);
    ASSERT_EQ("1:\n3.8\n2.8\n2:\n2.3\nRMSE: 0.77\n", w.str());
}

TEST(NetflixFixture, solve_2) {
    istringstream r("5:\n2\n3\n");
    ostringstream w;

    unordered_map<int, double> avg_movie_ratings;
    avg_movie_ratings[5] = 3.0;
    unordered_map<int, double> avg_customer_ratings;
    avg_customer_ratings[2] = 5.0;
    avg_customer_ratings[3] = 1.1;
    unordered_map<int, unordered_map<int, int>> actual_ratings;
    actual_ratings[5][2] = 5;
    actual_ratings[5][3] = 1;

    netflix_solve(r, w, avg_movie_ratings, avg_customer_ratings, actual_ratings);
    ASSERT_EQ("5:\n4.3\n0.4\nRMSE: 0.65\n", w.str());
}

TEST(NetflixFixture, solve_3) {
    istringstream r("");
    ostringstream w;

    unordered_map<int, double> avg_movie_ratings;
    unordered_map<int, double> avg_customer_ratings;
    unordered_map<int, unordered_map<int, int>> actual_ratings;
    
    netflix_solve(r, w, avg_movie_ratings, avg_customer_ratings, actual_ratings);
    ASSERT_EQ("RMSE: 0.00\n", w.str());
}
