#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Netflix.h"

// ----------
// read_input
// ----------
TEST (NetflixFixture, read_input) {
	std::istringstream r ("1:\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (1, movie);
}

TEST (NetflixFixture, read_input1) {
	std::istringstream r ("1000:\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (1000, movie);
}

TEST (NetflixFixture, read_input2) {
	std::istringstream r ("2488120\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (2488120, customer);
}

TEST (NetflixFixture, read_input3) {
	std::istringstream r ("1334:\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (1334, movie);
}

TEST (NetflixFixture, read_input4) {
	std::istringstream r ("470861\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (470861, customer);
}

TEST (NetflixFixture, read_input5) {
	std::istringstream r ("555555\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (555555, customer);
}

TEST (NetflixFixture, read_input6) {
	std::istringstream r ("11324\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (11324, customer);
}

TEST (NetflixFixture, read_input7) {
	std::istringstream r ("11111:\n");
	int customer;
	int movie;
	bool b = read_input (r, customer, movie);
	ASSERT_TRUE (b);
	ASSERT_EQ (11111, movie);
}


// -------------
// round_double
// -------------
TEST (NetflixFixture, round_double) {
	double num = 0.9552;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("0.95", result);
}

TEST (NetflixFixture, round_double1) {
	double num = 0.555;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("0.55", result);
}

TEST (NetflixFixture, round_double2) {
	double num = 0.1234;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("0.12", result);
}

TEST (NetflixFixture, round_double3) {
	double num = 3.523;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("3.52", result);
}

TEST (NetflixFixture, round_double4) {
	double num = 4.2222;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("4.22", result);
}

TEST (NetflixFixture, round_double5) {
	double num = 1.0432;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("1.04", result);
}

TEST (NetflixFixture, round_double6) {
	double num = 3.234;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("3.23", result);
}

TEST (NetflixFixture, round_double7) {
	double num = 0.1111;
	int places = 2;
	std::string result = round_double (num, places);
	ASSERT_EQ ("0.11", result);
}

// ----------------
// netflix_predict
// ----------------

TEST (NetflixFixture, netflix_predict) {
	double customerAverage = 1;
	double movieAverage = 1;
	double result = netflix_predict (customerAverage, movieAverage);
	ASSERT_EQ (result, 1);
}

TEST (NetflixFixture, netflix_predict1) {
	double customerAverage = 2;
	double movieAverage = 2;
	double result = netflix_predict (customerAverage, movieAverage);
	ASSERT_EQ (result, 1);
}

TEST (NetflixFixture, netflix_predict2) {
	double customerAverage = 3;
	double movieAverage = 3;
	double result = netflix_predict (customerAverage, movieAverage);
	ASSERT_EQ (result, 2.3);
}

TEST (NetflixFixture, netflix_predict3) {
	double customerAverage = 4;
	double movieAverage = 4;
	double result = netflix_predict (customerAverage, movieAverage);
	ASSERT_EQ (result, 4.3);
}

TEST (NetflixFixture, netflix_predict4) {
	double customerAverage = 5;
	double movieAverage = 5;
	double result = netflix_predict (customerAverage, movieAverage);
	ASSERT_EQ (result, 5);
}


// ----------------
// netflix
// ----------------
TEST (NetflixFixture, netflix1) {
	std::istringstream r("139:\n1390264\n");
	std::ostringstream w;
	netflix (r, w);
	ASSERT_EQ (w.str(), "139:\n2.2\nRMSE: 0.22\n");
}

TEST (NetflixFixture, netflix2) {
	std::istringstream r("1390:\n167534\n");
	std::ostringstream w;
	netflix (r, w);
	ASSERT_EQ (w.str(), "1390:\n4.3\nRMSE: 0.63\n");
}


TEST (NetflixFixture, netflix3) {
	std::istringstream r("13900:\n296823\n1471460\n");
	std::ostringstream w;
	netflix (r, w);
	ASSERT_EQ (w.str(), "13900:\n4.2\n3.6\nRMSE: 0.31\n");
}