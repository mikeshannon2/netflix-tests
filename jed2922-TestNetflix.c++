#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // string
#include <vector>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// split
// ----

TEST(Netflixfixture, split_1){
	string in = "1 2";
	vector<string> out = {"1", "2"};
	ASSERT_EQ(split(in), out);
}

TEST(Netflixfixture, split_2){
	string in = "100 200 300 400 500 600";
	vector<string> out = {"100", "200", "300", "400", "500", "600"};
	ASSERT_EQ(split(in), out);
}

TEST(Netflixfixture, split_3){
	string in = "";
	vector<string> out = {""};
	ASSERT_EQ(split(in), out);
}

// ----
// load_probe_ans
// ----

TEST(Netflixfixture, load_probe_data_standardinput){
	istringstream r("1 1283744 3\n1 1406595 4\n1 1989766 4\n");
	map<int, map<int, int>> test = load_probe_ans(r);
	ASSERT_EQ(3, test[1][1283744]);
	ASSERT_EQ(4, test[1][1406595]);
	ASSERT_EQ(4, test[1][1989766]);
}

TEST(Netflixfixture, load_probe_data_emptyfile){
	istringstream r("");
	map<int, map<int, int>> test = load_probe_ans(r);
}

// ----
// load_cache
// ----

TEST(Netflixfixture, load_cache_standardinput){
	istringstream r("0 4.0 0.84399571511\n1 3.50684931507 0.893251528049\n2 3.45248868778 0.94354470581\n");
	map<int,vector<double>> cache =  load_cache(r);
	ASSERT_EQ(cache[0][0], 4.0);
	ASSERT_EQ(cache[0][1], 0.84399571511);
	ASSERT_EQ(cache[1][0], 3.50684931507);
	ASSERT_EQ(cache[1][1], 0.893251528049);
	ASSERT_EQ(cache[2][0], 3.45248868778);
	ASSERT_EQ(cache[2][1], 0.94354470581);
	
}

TEST(Netflixfixture, load_cache_emptyfile){
	istringstream r("");
	map<int,vector<double>> cache =  load_cache(r);
}

TEST(Netflixfixture, load_cache_abnormalsize){
	istringstream r("5 4 1 2 3\n1 3.506 0.893 2.3453\n2 3.45248868778\n");
	map<int,vector<double>> cache =  load_cache(r);
	ASSERT_EQ(cache[5][0], 4);
	ASSERT_EQ(cache[5][1], 1);
	ASSERT_EQ(cache[5][2], 2);
	ASSERT_EQ(cache[5][3], 3);
	ASSERT_EQ(cache[1][0], 3.506);
	ASSERT_EQ(cache[1][1], 0.893);
	ASSERT_EQ(cache[1][2], 2.3453);
	ASSERT_EQ(cache[2][0], 3.45248868778);
}

// ----
// netflix_prediction
// ----

TEST(Netflixfixture, netflix_predict_average){
	istringstream r("1:\n1283744\n1406595\n1989766\n1904905");
	ostringstream w;
	netflix_predict(r, w);
	ASSERT_EQ("1:\n3.57\n3.56\n3.35\n3.89\nRMSE: 0.49", w.str());
}

TEST(Netflixfixture, netflix_predict_belowaverage){
	istringstream r("3:\n311641\n2561674\n2251677");
	ostringstream w;
	netflix_predict(r, w);
	ASSERT_EQ("3:\n1.78\n1.96\n3.05\nRMSE: 0.94", w.str());
}

TEST(Netflixfixture, netflix_predict_aboveaverage){
	istringstream r("5:\n1808686\n1207257\n2469155");
	ostringstream w;
	netflix_predict(r, w);
	ASSERT_EQ("5:\n4.39\n4.4\n3.71\nRMSE: 0.9", w.str());
}

// ----
// guess_rating
// ----

TEST(Netflixfixture, netflix_guess_rating_average){
	int movie = 5, customer = 1128196;
	stringstream s;
	s << guess_rating(movie, customer);
	ASSERT_EQ("3.95869", s.str());
}

TEST(Netflixfixture, netflix_guess_rating_upperlimit){
	int movie = 5, customer = 1794541;
	stringstream s;
	s << guess_rating(movie, customer);
	ASSERT_EQ("3.11558",s.str());
	
}

TEST(Netflixfixture, netflix_guess_rating_lowerlimit){
	int movie = 5, customer = 1874618;
	stringstream s;
	s << guess_rating(movie, customer);
	ASSERT_EQ("3.26887",s.str());
	
}

TEST(Netflixfixture, netflix_guess_rating_belowaverage){
	int movie = 8, customer = 1040462;
	stringstream s;
	s << guess_rating(movie, customer);
	ASSERT_EQ("3.28508",s.str());
	
}

TEST(Netflixfixture, netflix_guess_rating_aboveaverage){
	int movie = 8, customer = 862298;
	stringstream s;
	s << guess_rating(movie, customer);
	ASSERT_EQ("3.59841",s.str());
	
}