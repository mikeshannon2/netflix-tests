// ------------------------
// TestNetflix.c++
// Caelan Evans
// University of Texas 2016
// ------------------------

// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ---------------------
// clear_data_structures
// ---------------------

// Test inserting (and clearing) data structures (movie_ratings)
TEST(NetflixFixture, clear_data_structures_1) {
    istringstream r("1 1");
    ostringstream w;
    load_movie_ratings(r, w);
    clear_data_structures();
    istringstream r2("2 2");
    ostringstream w2;
    load_movie_ratings(r2, w2);
    ASSERT_EQ("2\n", w2.str());
    clear_data_structures();
}

// Test inserting (and clearing) data structures (customer_ratings)
TEST(NetflixFixture, clear_data_structures_2) {
    istringstream r("1 1");
    ostringstream w;
    load_customer_ratings(r, w);
    clear_data_structures();
    istringstream r2("2 2");
    ostringstream w2;
    load_customer_ratings(r2, w2);
    ASSERT_EQ("2\n", w2.str());
    clear_data_structures();
}

// Test inserting (and clearing) data structures (actual_ratings)
TEST(NetflixFixture, clear_data_structures_3) {
    istringstream r("100");
    ostringstream w;
    load_actual_ratings(r, w);
    clear_data_structures();
    istringstream r2("200");
    ostringstream w2;
    load_actual_ratings(r2, w2);
    ASSERT_EQ("200\n", w2.str());
    clear_data_structures();
}

// ------------------
// load_movie_ratings
// ------------------

// Test float values
TEST(NetflixFixture, load_movie_ratings_1) {
    istringstream r("1 3.5\n");
    ostringstream w;
    load_movie_ratings(r, w);
    ASSERT_EQ("3.5\n", w.str());
    clear_data_structures();
}

// Test integer numbers
TEST(NetflixFixture, load_movie_ratings_2) {
    istringstream r("2 5\n");
    ostringstream w;
    load_movie_ratings(r, w);
    ASSERT_EQ("5\n", w.str());
    clear_data_structures();
}

// Test multiple entries at once
TEST(NetflixFixture, load_movie_ratings_3) {
    istringstream r("1 3.5\n2 5");
    ostringstream w;
    load_movie_ratings(r, w);
    ASSERT_EQ("3.5\n5\n", w.str());
    clear_data_structures();
}

// ---------------------
// load_customer_ratings
// ---------------------

// Test float values
TEST(NetflixFixture, load_customer_ratings_1) {
    istringstream r("1 3.5");
    ostringstream w;
    load_customer_ratings(r, w);
    ASSERT_EQ("3.5\n", w.str());
    clear_data_structures();
}

// Test integer values
TEST(NetflixFixture, load_customer_ratings_2) {
    istringstream r("1 5");
    ostringstream w;
    load_customer_ratings(r, w);
    ASSERT_EQ("5\n", w.str());
    clear_data_structures();
}

// Test multiple entries
TEST(NetflixFixture, load_customer_ratings_3) {
    istringstream r("1 3.5\n2 5");
    ostringstream w;
    load_customer_ratings(r, w);
    ASSERT_EQ("3.5\n5\n", w.str());
    clear_data_structures();
}

// -------------------
// load_actual_ratings
// -------------------

// Test single value
TEST(NetflixFixture, load_actual_ratings_1) {
    istringstream r("100:\n123\n");
    ostringstream w;
    load_actual_ratings(r, w);
    ASSERT_EQ("100:\n123\n", w.str());
    clear_data_structures();
}

// Test single movie, multiple customers
TEST(NetflixFixture, load_actual_ratings_2) {
    istringstream r("100:\n123\n456\n789\n");
    ostringstream w;
    load_actual_ratings(r, w);
    ASSERT_EQ("100:\n123\n456\n789\n", w.str());
    clear_data_structures();
}

// Test multiple movies
TEST(NetflixFixture, load_actual_ratings_3) {
    istringstream r("100:\n123\n200:\n456\n");
    ostringstream w;
    load_actual_ratings(r, w);
    ASSERT_EQ("100:\n123\n200:\n456\n", w.str());
    clear_data_structures();
}

// ---------
// read_line
// ---------

TEST(NetflixFixture, read_line_1) {
    istringstream r("123\n");
    std::string w;
    const bool v = read_line(r, w);
    ASSERT_TRUE(v);
}

TEST(NetflixFixture, read_line_2) {
    istringstream r("4\n");
    std::string w;
    const bool v = read_line(r, w);
    ASSERT_TRUE(v);
}

TEST(NetflixFixture, read_line_3) {
    istringstream r("");
    std::string w;
    const bool v = read_line(r, w);
    ASSERT_FALSE(v);
}

// ----------
// print_line
// ----------

TEST(NetflixFixture, print_line_1) {
    ostringstream w;
    std::string s("123");
    print_line(w, s);
    ASSERT_EQ("123\n", w.str());
}

TEST(NetflixFixture, print_line_2) {
    ostringstream w;
    std::string s("4");
    print_line(w, s);
    ASSERT_EQ("4\n", w.str());
}

TEST(NetflixFixture, print_line_3) {
    ostringstream w;
    std::string s("");
    print_line(w, s);
    ASSERT_EQ("\n", w.str());
}

// --------------
// calculate_RMSE
// --------------

TEST(NetflixFixture, calculate_RMSE_1) {
    // General purpose ostringstream to provide to functions
    ostringstream os;

    istringstream mr("100 3.0\n");
    load_movie_ratings(mr, os);

    istringstream cr("1 3.0\n");
    load_customer_ratings(cr, os);

    istringstream ar("100:\n3.0\n");
    load_actual_ratings(ar, os);

    istringstream probe("100:\n1\n");
    ostringstream output;
    calculate_RMSE(probe, output);
    ASSERT_EQ("100:\n2.7\nRMSE: 0.26\n", output.str());
    clear_data_structures();
}

TEST(NetflixFixture, calculate_RMSE_2) {
    // General purpose ostringstream to provide to functions
    ostringstream os;

    istringstream mr("100 3.0\n");
    load_movie_ratings(mr, os);

    istringstream cr("1 4.0\n");
    load_customer_ratings(cr, os);

    istringstream ar("100:\n4.2\n");
    load_actual_ratings(ar, os);

    istringstream probe("100:\n1\n");
    ostringstream output;
    calculate_RMSE(probe, output);
    ASSERT_EQ("100:\n3.7\nRMSE: 0.53\n", output.str());
    clear_data_structures();
}

TEST(NetflixFixture, calculate_RMSE_3) {
    // General purpose ostringstream to provide to functions
    ostringstream os;

    istringstream mr("100 3.0\n");
    load_movie_ratings(mr, os);

    istringstream cr("1 3.0\n");
    load_customer_ratings(cr, os);

    istringstream ar("100:\n3.0\n");
    load_actual_ratings(ar, os);

    istringstream probe("100:\n1\n");
    ostringstream output;
    calculate_RMSE(probe, output);
    ASSERT_EQ("100:\n3.2\nRMSE: 0.17\n", output.str());
    clear_data_structures();
}
