// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Christiano Contreras
// Alex Niznik
// ----------------------------
 
// --------
// includes
// --------

#include "gtest/gtest.h"
#include "Netflix.h"
#include <sstream>

extern map<int, float> user_cache;
extern map<int, float> movie_cache;
extern map<int, int> answer_cache;
extern map<int, float> prediction_cache;

TEST(NetflixFixture, populate_cache_1)
{
	populate_cache(USER_CACHE_PATH, 
				   "cyt276-as63439-avg-customer-ratings.txt", 
				   user_cache);

	float rating = user_cache[2505140];
	stringstream s;
	s << fixed << setprecision(2) << rating;
	cout << rating << endl;
	string rating_string = s.str();
	ASSERT_EQ("3.81", rating_string);

}

TEST(NetflixFixture, populate_cache_2)
{
	populate_cache(USER_CACHE_PATH, 
				   "cyt276-as63439-avg-customer-ratings.txt", 
				   user_cache);

	float rating = user_cache[2185545];

	stringstream s;
	s << fixed << setprecision(2) << rating;
	string rating_string = s.str();

	ASSERT_EQ("3.65", rating_string);
	
}

TEST(NetflixFixture, populate_cache_3)
{
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);

	float rating = movie_cache[4521];
	stringstream s;
	s << fixed << setprecision(2) << rating;
	string rating_string = s.str();

	ASSERT_EQ("3.97", rating_string);
}

TEST(NetflixFixture, populate_answers_cache_1)
{
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");
	int rating = answer_cache[4];

	ASSERT_EQ(5, rating);
}

TEST(NetflixFixture, populate_answers_cache_2)
{
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");
	int rating = answer_cache[0];

	ASSERT_EQ(4, rating);
}

TEST(NetflixFixture, populate_answers_cache_3)
{
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");
	int rating = answer_cache[6];

	ASSERT_EQ(4, rating);
}

TEST(NetflixFixture, make_prediction_1)
{
	int movie_ID = 1000;
	int user_ID = 973432;
	float rating1 = 0;
	float rating2 = 0;
	float overall_mean;
	float movie_offset;
	float user_offset;
	string rating_string1;
	string rating_string2;
	stringstream ss1;
	stringstream ss2;

	populate_cache(USER_CACHE_PATH, 
				   "cyt276-as63439-avg-customer-ratings.txt", 
				   user_cache);

	populate_cache(MOVIE_CACHE_PATH,
				   "cyt276-as63439-avg-movie-ratings.txt", 
				   movie_cache);


    overall_mean = 3.6;
    movie_offset = movie_cache[movie_ID] - overall_mean;
    user_offset = user_cache[user_ID] - overall_mean;
	rating1 = overall_mean + movie_offset + user_offset;

	rating2 = make_prediction(1000,973432);

	ss1 << fixed << setprecision(2) << rating1;
	ss2 << fixed << setprecision(2) << rating2;

	rating_string1 = ss1.str();
	rating_string2 = ss2.str();


	ASSERT_EQ(rating_string1, rating_string2);

}

TEST(NetflixFixture, make_prediction_2)
{
	int movie_ID = 1001;
	int user_ID = 1257929;
	float rating1 = 0;
	float rating2 = 0;
	float overall_mean;
	float movie_offset;
	float user_offset;
	string rating_string1;
	string rating_string2;
	stringstream ss1;
	stringstream ss2;

	populate_cache(USER_CACHE_PATH, 
				   "cyt276-as63439-avg-customer-ratings.txt", 
				   user_cache);

	populate_cache(MOVIE_CACHE_PATH,
				   "cyt276-as63439-avg-movie-ratings.txt", 
				   movie_cache);


    overall_mean = 3.6;
    movie_offset = movie_cache[movie_ID] - overall_mean;
    user_offset = user_cache[user_ID] - overall_mean;
	rating1 = overall_mean + movie_offset + user_offset;

	rating2 = make_prediction(movie_ID,user_ID);

	ss1 << fixed << setprecision(2) << rating1;
	ss2 << fixed << setprecision(2) << rating2;

	rating_string1 = ss1.str();
	rating_string2 = ss2.str();


	ASSERT_EQ(rating_string1, rating_string2);

}

TEST(NetflixFixture, make_prediction_3)
{
	int movie_ID = 266;
	int user_ID = 1055551;
	float rating1 = 0;
	float rating2 = 0;
	float overall_mean;
	float movie_offset;
	float user_offset;
	string rating_string1;
	string rating_string2;
	stringstream ss1;
	stringstream ss2;

	populate_cache(USER_CACHE_PATH, 
				   "cyt276-as63439-avg-customer-ratings.txt", 
				   user_cache);

	populate_cache(MOVIE_CACHE_PATH,
				   "cyt276-as63439-avg-movie-ratings.txt", 
				   movie_cache);


    overall_mean = 3.6;
    movie_offset = movie_cache[movie_ID] - overall_mean;
    user_offset = user_cache[user_ID] - overall_mean;
	rating1 = overall_mean + movie_offset + user_offset;

	rating2 = make_prediction(movie_ID,user_ID);

	ss1 << fixed << setprecision(2) << rating1;
	ss2 << fixed << setprecision(2) << rating2;

	rating_string1 = ss1.str();
	rating_string2 = ss2.str();


	ASSERT_EQ(rating_string1, rating_string2);

}

TEST(NetflixFixture, rmse_1)
{
	string line1 = "2043:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string input = line1 + line2 + line3;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");
	
	parse_input(iss);
	
	ASSERT_TRUE(rmse() < 1.0);
}

TEST(NetflixFixture, rmse_2)
{
	string line1 = "10851:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string line4 = "462685\n";
	string input = line1 + line2 + line3 + line4;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");

	parse_input(iss);
	
	ASSERT_TRUE(rmse() < 1.0);
}

TEST(NetflixFixture, rmse_3)
{
	string line1 = "2043:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string line4 = "10851:\n";
	string line5 = "1417435\n";
	string line6 = "2312054\n";
	string line7 = "462685\n";
	string input = line1 + line2 + line3 + line4;
	input += line5 + line6 + line7;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");

	parse_input(iss);
	
	ASSERT_TRUE(rmse() < 1.0);

}

TEST(NetflixFixture, parse_input_1)
{
	string line1 = "2043:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string line4 = "10851:\n";
	string line5 = "1417435\n";
	string line6 = "2312054\n";
	string line7 = "462685\n";
	string input = line1 + line2 + line3 + line4;
	input += line5 + line6 + line7;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");

	parse_input(iss);

	ASSERT_TRUE(prediction_cache[0]);
}

TEST(NetflixFixture, parse_input_2)
{
	string line1 = "2043:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string line4 = "10851:\n";
	string line5 = "1417435\n";
	string line6 = "2312054\n";
	string line7 = "462685\n";
	string input = line1 + line2 + line3 + line4;
	input += line5 + line6 + line7;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");

	parse_input(iss);

	ASSERT_TRUE(prediction_cache[1]);
}

TEST(NetflixFixture, parse_input_3)
{
	string line1 = "2043:\n";
	string line2 = "1417435\n";
	string line3 = "2312054\n";
	string line4 = "10851:\n";
	string line5 = "1417435\n";
	string line6 = "2312054\n";
	string line7 = "462685\n";
	string input = line1 + line2 + line3 + line4;
	input += line5 + line6 + line7;
	istringstream iss(input);

	populate_cache(USER_CACHE_PATH, "cyt276-as63439-avg-customer-ratings.txt", user_cache);
	populate_cache(MOVIE_CACHE_PATH,"cyt276-as63439-avg-movie-ratings.txt", movie_cache);
	populate_answers_cache(ANSWER_CACHE_PATH, "cyt276-as63439-actual-ratings.txt");

	parse_input(iss);

	ASSERT_TRUE(prediction_cache[4]);
}