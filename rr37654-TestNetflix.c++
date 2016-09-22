// --------------------------------
// TestNetflix.c++
// Rahul Rajavel
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> 
#include <sstream>  
#include <fstream> 
#include <string>   

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// -------------------
// netflix_dot_product
// -------------------

TEST(NetflixTests, netflix_dot_product_1) {
	ASSERT_TRUE(netflix_dot_product(NULL, NULL, 0) == 0.0);
}

TEST(NetflixTests, netflix_dot_product_2) {
	double a[1] = {1};
	double b[1] = {2};
	ASSERT_TRUE(netflix_dot_product(a, b, 0) == 0.0);
}

TEST(NetflixTests, netflix_dot_product_3) {
	double a[1] = {1};
	double b[1] = {2};
	ASSERT_TRUE(netflix_dot_product(a, b, 1) == 2.0);
}

TEST(NetflixTests, netflix_dot_product_4) {
	double a[2] = {1.0, 4.1};
	double b[2] = {2, 3};
	ASSERT_TRUE(netflix_dot_product(a, b, 1) == 2.0);
}

TEST(NetflixTests, netflix_dot_product_5) {
	double a[2] = {1.0, 4.1};
	double b[2] = {2, 3};
	ASSERT_TRUE(netflix_dot_product(a, b, 2) == 14.3);
}

TEST(NetflixTests, netflix_dot_product_6) {
	double a[4] = {9.8, 14.4, 7.1, 3.3};
	double b[4] = {1.1, 2.3, 2.1, 1.4};
	ASSERT_TRUE(netflix_dot_product(a, b, 4) == 63.4);
}

TEST(NetflixTests, netflix_dot_product_7) {
	double a[5] = {2.7, -4.3, 1.8, 2.6, 20.2};
	double b[5] = {1.2, -2.0, -5.8, -1.8, 8.4};
	ASSERT_TRUE(netflix_dot_product(a, b, 5) == 166.4);
}


TEST(NetflixTests, netflix_dot_product_8) {
	double a[5] = {-2.7, 4.3, -1.8, -2.6, -20.2};
	double b[5] = {1.2, -2.0, -5.8, -1.8, 8.4};
	ASSERT_TRUE(netflix_dot_product(a, b, 5) == -166.4);
}

// ------------
// netflix_calc
// ------------

TEST(NetflixTests, netflix_calc_1) {
	ASSERT_TRUE(netflix_calc(2.58, 3.41, 1.13599, 0.123793) == 2.7);
}

TEST(NetflixTests, netflix_calc_2) {
	ASSERT_TRUE(netflix_calc(3.73, 3.33, 0.861645, -0.0281809) == 3.6);
}

TEST(NetflixTests, netflix_calc_3) {
	ASSERT_TRUE(netflix_calc(3.24, 3.09, 1.0278, -0.484726) == 2.7);
}

TEST(NetflixTests, netflix_calc_4) {
	ASSERT_TRUE(netflix_calc(3.07, 3.21, 0.904313, -0.261855) == 2.8);
}

TEST(NetflixTests, netflix_calc_5) {
	ASSERT_TRUE(netflix_calc(3.49, 3, 1.35061, -0.482843) == 3.0);
}

/*

// ----------------
// netflix_averages
// ----------------

TEST(NetflixTests, netflix_averages_1) {
	unordered_map<int, double> movie_averages;
	unordered_map<int, double> customer_averages;
	unordered_map<int, double> movie_deviations;
	unordered_map<int, double> customer_deviations;

	netflix_averages(movie_averages, customer_averages, movie_deviations, customer_deviations);

	ASSERT_TRUE(movie_averages.size() == 17770);
}

*/

// ---------------------
// netflix_obtain_inputs
// ---------------------

TEST(NetflixTests, netflix_obtain_inputs_1) {
	unordered_map<int, vector<int>> i;
	vector<int> io;
	istringstream s("1:\n2\n3\n4:\n1\n");
	ostringstream o;

	netflix_obtain_inputs(i, io, s, o);

	ASSERT_TRUE(i[1].size() == 2);
	ASSERT_TRUE(io.size() == 2);
}

// ---------------------
// netflix_obtain_inputs
// ---------------------

TEST(NetflixTests, netflix_obtain_inputs_2) {
	unordered_map<int, vector<int>> i;
	vector<int> io;
	istringstream s("1:\n2\n3\n4:\n1\n");
	ostringstream o;
 
	netflix_obtain_inputs(i, io, s, o);

	ASSERT_TRUE(i[4].size() == 1);
	ASSERT_TRUE(io.size() == 2);
}

/*

// -------------
// netflix_solve
// -------------

TEST(NetflixTests, netflix_solve_1) {
	istringstream s("1018:\n1236938\n2500683\n1242704");
	ostringstream o;

	netflix_solve(s, o);

	ASSERT_EQ(o.str().substr(0, 10), "1018:\n3.9\n");
}

*/
