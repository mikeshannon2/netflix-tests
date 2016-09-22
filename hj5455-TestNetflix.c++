// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------
#include <iostream> // cout, endl
#include <list>
#include <sstream> // istringtstream, ostringstream
#include <string>  // string
#include <utility> // pair


#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, eval1) {
	createCache("/u/downing/cs/netflix-cs371p/cyt276-as63439-avg-movie-ratings.txt", 1);
	createCache("/u/downing/cs/netflix-cs371p/cyt276-as63439-avg-customer-ratings.txt", 0);
	double ans = netflix_eval(10042, 2155386);
	ASSERT_EQ(ans, 4.28);
}


TEST(NetflixFixture, eval2) {
	double ans = netflix_eval(10042, 1292687);
	ASSERT_EQ(ans, 4.55);
}

TEST(NetflixFixture, eval3) {
	double ans = netflix_eval(10036, 2008955);
	ASSERT_EQ(ans, 3.58);
}

TEST(NeflixFixture, createCache1) {
	ASSERT_EQ(avg_customer[30878], 3.63);
}

TEST(NeflixFixture, createCache2) {
	ASSERT_EQ(avg_customer[2647871], 3.23);
}

TEST(NeflixFixture, createCache3) {
	ASSERT_EQ(avg_customer[1774623], 3.53);
}

TEST(NeflixFixture, createCache4) {
	ASSERT_EQ(avg_customer[548064], 3.47);
}

TEST(NeflixFixture, createCache5) {
	ASSERT_EQ(avg_customer[97460], 4.29);
}

TEST(NeflixFixture, createCache6) {
	ASSERT_EQ(avg_customer[79755], 4.13);
}

TEST(NeflixFixture, createCache7) {
	ASSERT_EQ(avg_customer[708895], 3.36);
}

TEST(NetflixFixture, solve1) {
	istringstream r("1:\n30878\n2647871\n1283744");
	ostringstream w;

	netflix_solve(r, w);
	ASSERT_EQ(w.str(), "1:\n3.6\n3.2\n3.5\nRMSE: 0.56");
}


TEST(NetflixFixture, solve2) {
	istringstream r("10001:\n262828\n2609496\n1474804\n831991\n267142\n2305771\n220050\n1959883\n27822\n2570808\n90355\n2417258\n264764\n143866\n766895\n714089\n2350428");
	ostringstream w;

	netflix_solve(r, w);
	ASSERT_EQ(w.str(), "10001:\n3.3\n4.2\n3.7\n2.6\n4.3\n3.4\n3.4\n3.9\n3.9\n3.5\n4.1\n4.1\n2.8\n4.1\n3.6\n3.4\n4.3\nRMSE: 0.93");
}
