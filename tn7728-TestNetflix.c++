#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"
#include "Netflix.h"

using namespace std;

// ----
// READ MOVIE CACHE
// ----

	 TEST(NetflixFixtures, moviecache_1)
	{
		const bool fin = movie_avg_cache_parser();
		ASSERT_TRUE(fin);
	}

	TEST(NetflixFixtures, moviecache_2)
	{
		const bool ish = movie_avg_cache_parser();
		ASSERT_TRUE(ish);
	}

	TEST(NetflixFixtures, moviecache_3)
	{
		const bool ed = movie_avg_cache_parser();
		ASSERT_TRUE(ed);
	}

// ----
// PREDICT THE RATING
// ----

	TEST(NetflixFixtures, predict_ratings_1)
	{
		double movie_rating = 3.75;
		double user_rating = 3.63;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.68, ans);
	}

	TEST(NetflixFixtures, predict_ratings_2)
	{
		double movie_rating = 3.75;
		double user_rating = 3.23;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.28, ans);
	}

	TEST(NetflixFixtures, predict_ratings_3)
	{
		double movie_rating = 3.75;
		double user_rating = 3.54;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.59, ans);
	}
	TEST(NetflixFixtures, predict_ratings_4)
	{
		double movie_rating = 3.75;
		double user_rating = 4.66;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(4.71, ans);
	}
	TEST(NetflixFixtures, predict_ratings_5)
	{
		double movie_rating = 3.75;
		double user_rating = 3.65;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.70, ans);
	}
	TEST(NetflixFixtures, predict_ratings_6)
	{
		double movie_rating = 3.75;
		double user_rating = 3.85;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.90, ans);
	}

	TEST(NetflixFixtures, predict_ratings_7)
	{
		double movie_rating = 3.18;
		double user_rating = 3.41;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(2.89, ans);
	}
	TEST(NetflixFixtures, predict_ratings_8)
	{
		double movie_rating = 3.18;
		double user_rating = 3.15;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(2.63, ans);
	}
	TEST(NetflixFixtures, predict_ratings_9)
	{
		double movie_rating = 3.28;
		double user_rating = 3.60;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(3.18, ans);
	}
	TEST(NetflixFixtures, predict_ratings_10)
	{
		double movie_rating = 3.28;
		double user_rating = 3.29;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(2.87, ans);
	}
	TEST(NetflixFixtures, predict_ratings_11)
	{
		double movie_rating = 3.28;
		double user_rating = 3.00;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(2.58, ans);
	}
	TEST(NetflixFixtures, predict_ratings_12)
	{
		double movie_rating = 3.28;
		double user_rating = 5.00;

		double ans = predict_rating(movie_rating, user_rating);

		ASSERT_DOUBLE_EQ(4.58, ans);
	}
// -----
// EVAL
// -----

	TEST(NetflixFixtures, netflix_eval_1)
	{
		unordered_map<int, double> customer_cache = {{30878, 3.63}, {2647871, 3.23}};
		istringstream r("1:\n 30878 \n 2657871\n");
		ostringstream w;
	    double ans = netflix_eval(customer_cache, r);;
		ASSERT_DOUBLE_EQ(0.28284271247461895, ans);

	}

// -----
// SOLVE
// -----