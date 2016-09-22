// TestNetflix.c++
// Copyright (C) 2016
// Brandon I. Smith
// UTEID: bis266

#include <climits>
#include <cstdint>
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <fstream>
#include <cmath>    // abs

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------------
// predict_rating
// --------------

TEST(NetflixFixture, solve1) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 2.5f);
	vector<float> movie_avg(1, 2.5f);
	ASSERT_TRUE(
		abs(1.3f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}

TEST(NetflixFixture, solve2) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 0.0f);
	vector<float> movie_avg(1, 5.0f);
	ASSERT_TRUE(
		abs(1.3f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}

TEST(NetflixFixture, solve3) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 4.3f);
	vector<float> movie_avg(1, 2.1f);
	ASSERT_TRUE(
		abs(2.7f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}

TEST(NetflixFixture, solve4) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 3.1f);
	vector<float> movie_avg(1, 4.8f);
	ASSERT_TRUE(
		abs(4.2f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}

TEST(NetflixFixture, solve5) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 3.9f);
	vector<float> movie_avg(1, 2.4f);
	ASSERT_TRUE(
		abs(2.6f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}

TEST(NetflixFixture, solve6) {
	int uid = 0;
	int mid = 0;
	vector<float> user_avg(1, 4.2f);
	vector<float> movie_avg(1, 4.6f);
	ASSERT_TRUE(
		abs(5.1f - predict_rating(uid, mid, user_avg, movie_avg)) < 0.01f);
}
