// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include "gtest/gtest.h"
#include <math.h>
#include "Netflix.h"

// id_type
#define MOVIE 1
#define CUSTOMER 2

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("2043:\n");
    int           i;
    int           j;
    const bool b = read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(2043, i);
    ASSERT_EQ(MOVIE, j);
}

TEST(NetflixFixture, read_2) {
    istringstream r("123456\n");
    int           i;
    int           j;
    const bool b = read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(123456, i);
    ASSERT_EQ(CUSTOMER, j);
}

TEST(NetflixFixture, read_3) {
    istringstream r("");
    int           i;
    int           j;
    const bool b = read(r, i, j);
    ASSERT_FALSE(b);
}

// ----
// get_avg
// ----

// TEST(NetflixFixture, get_avg_1) {
//     int           i = 2043;
//     int           j = MOVIE;
//     istringstream cache("10009:\n1927533\n1789102\n2263612\n1001:\n1050889\n67976\n1025642");
//     const double b = get_avg(i, j, &cache);
//     ASSERT_EQ(3.78, b);
// }
//
// TEST(NetflixFixture, get_avg_2) {
//     int           i = 1738367;
//     int           j = CUSTOMER;
//     istringstream cache("1885598 3.60\286258 2.86\1738367 3.64\2553729 3.80\1530019 2.90\612535 3.60");
//     const double b = get_avg(i, j, &cache);
//     ASSERT_EQ(3.64, b);
// }
//
// TEST(NetflixFixture, get_avg_3) {
//     int           i = 2043;
//     int           j = CUSTOMER;
//     istringstream cache("10009:\n1927533\n1789102\n2263612\n1001:\n1050889\n67976\n1025642");
//     const double b = get_avg(i, j, &cache);
//     ASSERT_EQ(0, b);
// }

// ----
// get_rating
// ----

// TEST(NetflixFixture, get_rating_1) {
//     int           i = 2043;
//     int           j = 2180261;
//     const double b = get_rating(i, j);
//     ASSERT_EQ(3, b);
// }

// TEST(NetflixFixture, get_rating_2) {
//     int           i = 2043;
//     int           j = 0;
//     const double b = get_rating(i, j);
//     ASSERT_EQ(0, b);
// }

// TEST(NetflixFixture, get_rating_3) {
//     int           i = 0;
//     int           j = 2180261;
//     const double b = get_rating(i, j);
//     ASSERT_EQ(0, b);
// }

// ----
// predict
// ----

TEST(NetflixFixture, predict_1) {
    int           i = 0;
    int           j = 0;
    const double b = predict(i, j);
    ASSERT_EQ(0, b);
}

TEST(NetflixFixture, predict_2) {
    int           i = 2;
    int           j = 2;
    const double b = predict(i, j);
    ASSERT_EQ(2, b);
}

TEST(NetflixFixture, predict_3) {
    int           i = 1;
    int           j = 3;
    const double b = predict(i, j);
    ASSERT_EQ(2, b);
}

// ----
// rmse
// ----

TEST(NetflixFixture, rmse_1) {
    vector<double>           i (10, 0);
    vector<double>           j (10, 0);
    const double b = rmse(i, j);
    ASSERT_EQ(0, b);
}

TEST(NetflixFixture, rmse_2) {
    double doubles1[] = {10, 11, 41, 19, 18, 4, 22, 38, 7, 45};
    double doubles2[] = {13, 42, 16, 1, 8, 27, 23, 4, 50, 46};
    vector<double>   i (doubles1, doubles1 + sizeof(doubles1) / sizeof(double));
    vector<double>   j (doubles2, doubles2 + sizeof(doubles2) / sizeof(double));
    const double b = rmse(i, j);
    ASSERT_EQ(round(23.569), round(b));
}

TEST(NetflixFixture, rmse_3) {
    vector<double>           i (10, 1);
    vector<double>           j (10, 2);
    const double b = rmse(i, j);
    ASSERT_EQ(1, b);
}

// ----
// netflix_predictions
// ----

// TEST(NetflixFixture, netflix_predictions_1) {
//     // istringstream i("1:\n30878\n2647871\n10:\n1952305\n1531863\n");
//     // ostringstream w;
//     // netflix_predictions(i, w);
//     // ASSERT_EQ("1:\n3.7\n3.5\n10:\n3.3\n3.2\nRMSE: 0.34\n", w.str());
// }
//
// TEST(NetflixFixture, netflix_predictions_2) {
//     // istringstream i("10009:\n1927533\n1789102\n2263612\n1001:\n1050889\n67976\n1025642");
//     // ostringstream w;
//     // netflix_predictions(i, w);
//     // ASSERT_EQ("10009:\n3.3\n3.5\n4.1\n1001:\n4\n3.5\n3.3\nRMSE: 0.76\n", w.str());
// }
//
// TEST(NetflixFixture, netflix_predictions_3) {
//     // istringstream i("10010:\n1462925\n52050\n650466\n10014:\n1626179\n1359761\n");
//     // ostringstream w;
//     // netflix_predictions(i, w);
//     // ASSERT_EQ("10010:\n3\n2.8\n2.9\n10014:\n3.4\n3.8\nRMSE: 1.3\n", w.str());
// }
