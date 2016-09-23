#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, read1) {
	istringstream r("1\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ( "1", i);
}

TEST(NetflixFixture, read2) {
	istringstream r("1150\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ( "1150", i);
}

TEST(NetflixFixture, read3) {
	istringstream r("99\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ( "99", i);
}



TEST(NetflixFixture, print1) {
	ostringstream w;
	netflix_print(w, 1.5);
	ASSERT_EQ("1.5\n", w.str());
}

TEST(NetflixFixture, print2) {
	ostringstream w;
	netflix_print(w, 5.16);
	ASSERT_EQ("5.16\n", w.str());
}

TEST(NetflixFixture, print3) {
	ostringstream w;
	netflix_print(w, 1542.5);
	ASSERT_EQ("1542.5\n", w.str());
}


TEST(NetflixFixture, solve1) {
	istringstream r("1:\n30878\n2647871\n1283744\n2488120\n");
	istringstream avgCustomerRatingsCache("30878 3.63\n2647871 3.23\n1283744 3.54\n2488120 4.66\n");
	istringstream avgMovieRatingsCache("1 3.75\n");
	istringstream actualRatingsCache("1:\n4\n4\n3\n5\n");
	ostringstream w;
	netflix_solve(r, w, avgCustomerRatingsCache, avgMovieRatingsCache, actualRatingsCache);
	ASSERT_EQ("1:\n3.6\n3.2\n3.5\n4.6\nRMSE: 0.54\n", w.str());
}

TEST(NetflixFixture, solve2) {
	istringstream r("10004:\n1737087\n1270334\n1262711\n1903515\n");
	istringstream avgCustomerRatingsCache("1737087 4.55\n1270334 3.57\n1262711 3.79\n1903515 3.38\n");
	istringstream avgMovieRatingsCache("10004 4.21\n");
	istringstream actualRatingsCache("10004:\n5\n5\n3\n5\n");
	ostringstream w;
	netflix_solve(r, w, avgCustomerRatingsCache, avgMovieRatingsCache, actualRatingsCache);
	ASSERT_EQ("10004:\n5\n4\n4.2\n3.8\nRMSE: 0.98\n", w.str());
}

TEST(NetflixFixture, solve3) {
	istringstream r("1001:\n1050889\n67976\n1025642\n624334\n");
	istringstream avgCustomerRatingsCache("1050889 4.71\n67976 3.72\n1025642 3.32\n624334 3.47\n");
	istringstream avgMovieRatingsCache("1001 3.32\n");
	istringstream actualRatingsCache("1001:\n4\n4\n5\n3\n");
	ostringstream w;
	netflix_solve(r, w, avgCustomerRatingsCache, avgMovieRatingsCache, actualRatingsCache);
	ASSERT_EQ("1001:\n4.3\n3.3\n2.9\n3\nRMSE: 1.11\n", w.str());
}


TEST(NetflixFixture, eval1) {
	const double ret = netflix_eval(1, 30878);
	ASSERT_EQ(ret, 3.6);
}

TEST(NetflixFixture, eval2) {
	const double ret = netflix_eval(1, 2647871);
	ASSERT_EQ(ret, 3.2);
}

TEST(NetflixFixture, eval3) {
	const double ret = netflix_eval(1, 1283744);
	ASSERT_EQ(ret, 3.5);
}
