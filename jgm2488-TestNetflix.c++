// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <unordered_map> // map

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// netflix_read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("1");
    std::string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("1", i);}
TEST(NetflixFixture, read_2) {
    istringstream r("bob");
    std::string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("bob", i);}
TEST(NetflixFixture, read_3) {
    istringstream r("10000:");
    std::string           i;
    const bool b = netflix_read(r, i);
    ASSERT_TRUE(b);
    ASSERT_EQ("10000:", i);}

// ----
// netflix_eval
// ----

TEST(NetflixFixture, eval_1) {
    double test_ray[2];
    test_ray[1] = 3.75;
    std::unordered_map<int, double> test_map;
    test_map[30878] = 3.63;
    const double v = netflix_eval(1, 30878, test_ray, test_map);
    ASSERT_DOUBLE_EQ(3.68, v);}

TEST(NetflixFixture, eval_2) {
    double test_ray[2];
    test_ray[1] = 1.5;
    std::unordered_map<int, double> test_map;
    test_map[152516] = 2.0;
    const double v = netflix_eval(1, 152516, test_ray, test_map);
    ASSERT_DOUBLE_EQ(0.0, v);}

TEST(NetflixFixture, eval_3) {
    double test_ray[2];
    test_ray[1] = 4.23;
    std::unordered_map<int, double> test_map;
    test_map[12512] = 1.95;
    const double v = netflix_eval(1, 12512, test_ray, test_map);
    ASSERT_DOUBLE_EQ(2.48, v);}

// -----
// netflix_print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream w;
    netflix_print(w, "1");
    ASSERT_EQ("1\n", w.str());}
TEST(NetflixFixture, print_2) {
    ostringstream w;
    netflix_print(w, "bob");
    ASSERT_EQ("bob\n", w.str());}
TEST(NetflixFixture, print_3) {
    ostringstream w;
    netflix_print(w, "101010:");
    ASSERT_EQ("101010:\n", w.str());}

// -----
// populate_movies
// -----

TEST(NetflixFixture, pop_1) {
    double test_ray[4] = {0.0};
    populate_movies(test_ray, true);
    ASSERT_EQ(3.75, test_ray[1]);}
TEST(NetflixFixture, pop_2) {
    double test_ray[4] = {0.0};
    populate_movies(test_ray, true);
    ASSERT_EQ(2.5, test_ray[2]);}
TEST(NetflixFixture, pop_3) {
    double test_ray[4] = {0.0};
    populate_movies(test_ray, true);
    ASSERT_EQ(1.4, test_ray[3]);}

// -----
// populate_users
// -----

TEST(NetflixFixture, popu_1) {
    std::unordered_map<int,double> test_map;
    populate_users(test_map, true);
    ASSERT_EQ(3.63, test_map[30878]);}
TEST(NetflixFixture, popu_2) {
    std::unordered_map<int,double> test_map;
    populate_users(test_map, true);
    ASSERT_EQ(3.23, test_map[2647871]);}
TEST(NetflixFixture, popu_3) {
    std::unordered_map<int,double> test_map;
    populate_users(test_map, true);
    ASSERT_EQ(3.54, test_map[1283744]);}

// -----
// calculate_rmse
// -----

TEST(NetflixFixture, cal_1) {
    ASSERT_EQ(0.53, calculate_rmse(true));}
TEST(NetflixFixture, cal_2) {
    ASSERT_EQ(0.53, calculate_rmse(true));}
TEST(NetflixFixture, cal_3) {
    ASSERT_EQ(0.53, calculate_rmse(true));}

// -----
// netflix_solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("1:\n30878\n2647871");
    ostringstream w;
    netflix_solve(r, w, true);
    ASSERT_EQ("1:\n3.6\n3.2\nRMSE: 0.53\n", w.str());}
TEST(NetflixFixture, solve_2) {
    istringstream r("1:\n30878\n2647871\n1283744");
    ostringstream w;
    netflix_solve(r, w, true);
    ASSERT_EQ("1:\n3.6\n3.2\n3.5\nRMSE: 0.53\n", w.str());}
TEST(NetflixFixture, solve_3) {
    istringstream r("1:\n30878\n2647871\n1283744\n2488120");
    ostringstream w;
    netflix_solve(r, w, true);
    ASSERT_EQ("1:\n3.6\n3.2\n3.5\n4.7\nRMSE: 0.53\n", w.str());}