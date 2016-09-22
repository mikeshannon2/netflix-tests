/**
 * @file TestNetflix.c++
 * @brief Unit tests for Netflix using Google Test.
 * @copyright Copyright (C) 2016
 * @author Glenn P. Downing
 * @author Brian Cui, Tyler Hester
 */

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

/** @brief Simple test fixture to ensure each unit test is not affected
 * by the side effects on the caches by other tests. */
class NetflixFixture : public ::testing::Test {
protected:
    /** @brief Empty all the caches so no key value pairs remain. */
    virtual void SetUp() {
        movie_avg.clear();
        user_dev.clear();
        actual_ratings.clear();
    }
};

// ----
// read
// ----

/* Stub function for testing load_file */
void load_stub(const char line[]) {
    /* Make sure we don't get a null pointer */
    ASSERT_TRUE(line);
    return;
}

TEST_F(NetflixFixture, load_file_1) {
    load_file("README.md", load_stub);

    /* Ensure file read doesn't crash */
    ASSERT_TRUE(true);
}

/* Tests for processing and storing movie average cache. */
TEST_F(NetflixFixture, movie_avg_1) {
    parse_movie_avg("1 2.34");
    ASSERT_EQ(movie_avg[1], 2.34);
}

TEST_F(NetflixFixture, movie_avg_2) {
    parse_movie_avg("0 5.67");
    ASSERT_EQ(movie_avg[0], 5.67);
}

TEST_F(NetflixFixture, movie_avg_3) {
    parse_movie_avg("100 -1234.1234");
    ASSERT_EQ(movie_avg[100], -1234.1234);
}

TEST_F(NetflixFixture, movie_avg_4) {
    parse_movie_avg("-1234 0.9999");
    ASSERT_EQ(movie_avg[-1234], 0.9999);
}

/* Tests for processing and storing user deviation cache. */
TEST_F(NetflixFixture, user_dev_1) {
    parse_user_dev("12 3.14");
    ASSERT_EQ(user_dev[12], 3.14);
}

TEST_F(NetflixFixture, user_dev_2) {
    parse_user_dev("95 -5.67");
    ASSERT_EQ(user_dev[95], -5.67);
}

TEST_F(NetflixFixture, user_dev_3) {
    parse_user_dev("1995 0.99999");
    ASSERT_EQ(user_dev[1995], 0.99999);
}

TEST_F(NetflixFixture, user_dev_4) {
    parse_user_dev("0 -0.123");
    ASSERT_EQ(user_dev[0], -0.123);
}

/* Tests for processing and storing actual rating cache. */
TEST_F(NetflixFixture, actual_ratings_1) {
    parse_actual_ratings("55 1234 5");
    ASSERT_EQ(actual_ratings[55][1234], 5);
}

TEST_F(NetflixFixture, actual_ratings_2) {
    parse_actual_ratings("-99 4321 4");
    ASSERT_EQ(actual_ratings[-99][4321], 4);
}

TEST_F(NetflixFixture, actual_ratings_3) {
    parse_actual_ratings("6341 67 2");
    ASSERT_EQ(actual_ratings[6341][67], 2);
}

/* Ensure predict_rating adds movie average and user deviation. */
TEST_F(NetflixFixture, predict_rating_1) {
    parse_movie_avg("1 2.1");
    parse_user_dev("2 3.3");
    ASSERT_EQ(predict_rating(1, 2), 5.4);
}

TEST_F(NetflixFixture, predict_rating_2) {
    parse_movie_avg("2 1.5");
    parse_user_dev("3 4.6");
    ASSERT_EQ(predict_rating(2, 3), 6.1);
}

TEST_F(NetflixFixture, predict_rating_3) {
    parse_movie_avg("1234 1234.5");
    parse_user_dev("4321 8.987");
    ASSERT_EQ(predict_rating(1234, 4321), 1243.487);
}

/* Ensure the RMSE value is properly calculated based on
   mean sum and count. */
TEST_F(NetflixFixture, calc_rmse_1) {
    ASSERT_EQ(calculate_rmse(0, 0), 0.0);
}

TEST_F(NetflixFixture, calc_rmse_2) {
    ASSERT_EQ(calculate_rmse(32, 2), 4.0);
}

TEST_F(NetflixFixture, calc_rmse_3) {
    ASSERT_EQ(calculate_rmse(100, 4), 5.0);
}

/* Test the actual netflix_solve function based on sample cache
   data and sample input data. */
TEST_F(NetflixFixture, netflix_solve_1) {
    parse_actual_ratings("1 1234 3.0");
    parse_movie_avg("1 2.0");
    parse_user_dev("1234 0.5");

    istringstream r("1:\n1234\n");
    ostringstream w;

    double rmse = netflix_solve(r, w, 0);
    ASSERT_LT(rmse, 1.00);
    ASSERT_GT(rmse, 0);    
}

TEST_F(NetflixFixture, netflix_solve_2) {
    parse_actual_ratings("9999 9999 5.0");
    parse_movie_avg("9999 1.0");
    parse_user_dev("9999 3.999");

    istringstream r("9999:\n9999\n");
    ostringstream w;

    double rmse = netflix_solve(r, w, 0);
    ASSERT_LT(rmse, 1.00);
    ASSERT_GT(rmse, 0);
}

TEST_F(NetflixFixture, netflix_solve_3) {
    parse_actual_ratings("10 4444 2.0");
    parse_actual_ratings("11 4444 3.0");
    parse_actual_ratings("12 4444 4.0");
    parse_actual_ratings("10 5555 1.0");
    parse_actual_ratings("11 5555 2.0");
    parse_actual_ratings("12 5555 5.0");

    parse_movie_avg("10 2.0");
    parse_movie_avg("11 3.5");
    parse_movie_avg("12 4.9");

    parse_user_dev("4444 -.5");
    parse_user_dev("5555 -.2");

    istringstream r("10:\n4444\n5555\n11:\n4444\n5555\n12:\n4444\n5555\n");
    ostringstream w;

    double rmse = netflix_solve(r, w, 0);
    ASSERT_LT(rmse, 1.00);
    ASSERT_GT(rmse, 0);
}
