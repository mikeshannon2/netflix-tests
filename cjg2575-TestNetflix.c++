#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1){
	istringstream r("1:\n");
	string m;
	const bool b = netflix_read(r, m);
    ASSERT_TRUE(b);
    EXPECT_EQ(m, "1:");}

TEST(NetflixFixture, read_2){
	istringstream r("1:\n2136178\n");
	string m;
	const bool b = netflix_read(r, m);
    ASSERT_TRUE(b);
    EXPECT_EQ(m, "1:");
	const bool b2 = netflix_read(r, m);
	ASSERT_TRUE(b2);
	EXPECT_EQ(m, "2136178");}

TEST(NetflixFixture, read_3){
	istringstream r("1:");
	string m;
	netflix_read(r,m);
	const bool b = netflix_read(r, m);
	ASSERT_FALSE(b);}


// ----
// print
// ----

TEST(NetflixFixture, print_1) {
	ostringstream w;
	struct movie m;
	m.movie_id = 20;
	m.customers = {100};
	m.ratings = {3};
	map<int, map<int, float>> movie_predictions = {};
	netflix_print(w, m, movie_predictions);
	// Check that the map contains the ratings map
	map<int, map<int, float>>::iterator it = movie_predictions.find(m.movie_id);
	ASSERT_TRUE(it != movie_predictions.end());
	// Check that the customer ratings are in the map
	map<int, float> customer_ratings = it->second;
	map<int, float>::iterator customer_it = customer_ratings.find(m.customers[0]);
	ASSERT_TRUE(customer_it != customer_ratings.end());
	ASSERT_TRUE(customer_it->second == m.ratings[0]);}

// ----
// netflix_read_cache
// ----
TEST(NetflixFixture, netflix_read_cache_1){
	istringstream r("200 4");
	int id;
	float rating;
	const bool b = netflix_read_cache(r, id, rating);
	ASSERT_TRUE(b);
	ASSERT_EQ(id, 200);
	ASSERT_EQ(rating, 4);
}


TEST(NetflixFixture, netflix_read_cache_2){
	istringstream r("300 4.2\n400 2.4");
	int id;
	float rating;
	const bool b = netflix_read_cache(r, id, rating);
	ASSERT_TRUE(b);
	ASSERT_EQ(id, 300);
	ASSERT_FLOAT_EQ(rating, 4.2);
	const bool b2 = netflix_read_cache(r, id, rating);
	ASSERT_TRUE(b2);
	ASSERT_EQ(id, 400);
	ASSERT_FLOAT_EQ(rating, 2.4);
}

TEST(NetflixFixture, netflix_read_cache_3){
	istringstream r("300 4.2");
	int id;
	float rating;
	const bool b = netflix_read_cache(r, id, rating);
	ASSERT_TRUE(b);
	ASSERT_EQ(id, 300);
	ASSERT_FLOAT_EQ(rating, 4.2);
	const bool b2 = netflix_read_cache(r, id, rating);
	ASSERT_FALSE(b2);
}

// --------------------
// netflix_read_answers
// --------------------
TEST(NetflixFixture, netflix_read_answers_1){
	istringstream r("1 200 4.0");
	int m_id, c_id;
	float rating;
	const bool b = netflix_read_answers(r, m_id, c_id, rating);
	ASSERT_TRUE(b);
	ASSERT_EQ(m_id, 1);
	ASSERT_EQ(c_id, 200);
	ASSERT_FLOAT_EQ(rating, 4.0);}

TEST(NetflixFixture, netflix_read_answers_2){
	istringstream r("1 200 4\n 2 201 4.5");
	int m_id, c_id;
	float rating;
	netflix_read_answers(r, m_id, c_id, rating);
	const bool b = netflix_read_answers(r, m_id, c_id, rating);
	ASSERT_TRUE(b);
	ASSERT_EQ(m_id, 2);
	ASSERT_EQ(c_id, 201);
	ASSERT_FLOAT_EQ(rating, 4.5);}

TEST(NetflixFixture, netflix_read_answers_3){
	istringstream r("1 200 4.0");
	int m_id, c_id;
	float rating;
	netflix_read_answers(r, m_id, c_id, rating);
	const bool b = netflix_read_answers(r, m_id, c_id, rating);
	ASSERT_FALSE(b);}


// -------------------------
// netflix_make_map
// -------------------------
TEST(NetflixFixture, netflix_make_map_1){
	istringstream r("10 5");
	map<int, float> customer_ratings_1;
	netflix_make_map(r, customer_ratings_1);
	ASSERT_TRUE(customer_ratings_1[10] == 5);}


TEST(NetflixFixture, netflix_make_map_2){
	istringstream r("20 3");
	map<int, float> customer_ratings_2;
	netflix_make_map(r, customer_ratings_2);
	ASSERT_TRUE(customer_ratings_2[20] == 3);}


TEST(NetflixFixture, netflix_make_map_3){
	istringstream r("40 2");
	map<int, float> customer_ratings_3;
	netflix_make_map(r, customer_ratings_3);
	ASSERT_TRUE(customer_ratings_3[40] == 2);}

TEST(NetflixFixture, netflix_make_map_4){
	istringstream r("900 4");
	map<int, float> customer_ratings_4;
	netflix_make_map(r, customer_ratings_4);
	ASSERT_TRUE(customer_ratings_4[900] == 4);}


// -------------------------
// netflix_map_actual_ratings
// -------------------------
TEST(NetflixFixture, map_actual_ratings_1){
	istringstream r("10 2000 4");
	map<int, map<int, float>> actual_ratings_1;
	netflix_map_actual_ratings(r, actual_ratings_1);
	ASSERT_TRUE(actual_ratings_1[10][2000] = 4);
}

TEST(NetflixFixture, map_actual_ratings_2){
	istringstream r("20 3000 3");
	map<int, map<int, float>> actual_ratings_2;
	netflix_map_actual_ratings(r, actual_ratings_2);
	ASSERT_TRUE(actual_ratings_2[20][3000] == 3);
}

TEST(NetflixFixture, map_actual_ratings_3){
	istringstream r("50 2350 2");
	map<int, map<int, float>> actual_ratings_3;
	netflix_map_actual_ratings(r, actual_ratings_3);
	ASSERT_TRUE(actual_ratings_3[50][2350] == 2);
}

TEST(NetflixFixture, map_actual_ratings_4){
	istringstream r("7832 2333 4");
	map<int, map<int, float>> actual_ratings_4;
	netflix_map_actual_ratings(r, actual_ratings_4);
	ASSERT_TRUE(actual_ratings_4[7832][2333] == 4);
}

// ----------------------
// netflix_calculate_rmse
// ----------------------
TEST(NetflixFixture, calculate_rmse_1) {
	map<int, map<int, float>> movie_predictions;
	map<int, float> customer_predictions;
	customer_predictions[200] = 3;
	movie_predictions[10] = customer_predictions;

	map<int, map<int, float>> actual_m_ratings;
	map<int, float> movie_ratings;
	movie_ratings[200] = 4;
	actual_m_ratings[10] = movie_ratings;
	const float rmse_1 = calculate_rmse(movie_predictions, actual_m_ratings);
	ASSERT_FLOAT_EQ(1, rmse_1);
}

TEST(NetflixFixture, calculate_rmse_2) {
	map<int, map<int, float>> movie_predictions;
	map<int, float> customer_predictions;
	customer_predictions[200] = 2;
	movie_predictions[10] = customer_predictions;

	map<int, map<int, float>> actual_m_ratings;
	map<int, float> movie_ratings;
	movie_ratings[200] = 5;
	actual_m_ratings[10] = movie_ratings;
	const float rmse_1 = calculate_rmse(movie_predictions, actual_m_ratings);
	ASSERT_FLOAT_EQ(3, rmse_1);
}

TEST(NetflixFixture, calculate_rmse_3) {
	map<int, map<int, float>> movie_predictions;
	map<int, float> customer_predictions;
	customer_predictions[200] = 3;
	movie_predictions[10] = customer_predictions;

	map<int, map<int, float>> actual_m_ratings;
	map<int, float> movie_ratings;
	movie_ratings[200] = 3;
	actual_m_ratings[10] = movie_ratings;
	const float rmse_1 = calculate_rmse(movie_predictions, actual_m_ratings);
	ASSERT_FLOAT_EQ(0, rmse_1);
}

// ------------------------
// netflix_make_predictions
// ------------------------

TEST(NetflixFixture, netflix_make_predictions_1){
	istringstream r("1:\n12");
	ostringstream w;
	map<int, map<int, float>> movie_predictions;
	map<int, float> movie_ratings;
	movie_ratings[1] = 4.7;
	map<int, float> customer_ratings;
	customer_ratings[12] = 2;
	netflix_make_predictions(r, w, movie_predictions, movie_ratings, customer_ratings);
	ASSERT_FLOAT_EQ(3.0, movie_predictions[1][12]);}

TEST(NetflixFixture, netflix_make_predictions_2){
	istringstream r("1:\n12\n10:\n12");
	ostringstream w;
	map<int, map<int, float>> movie_predictions;
	map<int, float> movie_ratings;
	movie_ratings[1] = 4.7;
	movie_ratings[10] = 3.7;
	map<int, float> customer_ratings;
	customer_ratings[12] = 2;
	netflix_make_predictions(r, w, movie_predictions, movie_ratings, customer_ratings);
	ASSERT_FLOAT_EQ(3.0, movie_predictions[1][12]);
	ASSERT_FLOAT_EQ(2.0, movie_predictions[10][12]);}

TEST(NetflixFixture, netflix_make_predictions_3){
	istringstream r("1:\n12\n14");
	ostringstream w;
	map<int, map<int, float>> movie_predictions;
	map<int, float> movie_ratings;
	movie_ratings[1] = 4.7;
	map<int, float> customer_ratings;
	customer_ratings[12] = 2;
	customer_ratings[14] = 3.5;
	netflix_make_predictions(r, w, movie_predictions, movie_ratings, customer_ratings);
	ASSERT_FLOAT_EQ(3.0, movie_predictions[1][12]);
	ASSERT_FLOAT_EQ(4.5, movie_predictions[1][14]);}


TEST(NetflixFixture, netflix_make_predictions_4){
	istringstream r("1:\n12\n14\n10:\n12\n14");
	ostringstream w;
	map<int, map<int, float>> movie_predictions;
	map<int, float> movie_ratings;
	movie_ratings[1] = 4.7;
	movie_ratings[10] = 3.7;
	map<int, float> customer_ratings;
	customer_ratings[12] = 2;
	customer_ratings[14] = 3.5;
	netflix_make_predictions(r, w, movie_predictions, movie_ratings, customer_ratings);
	ASSERT_FLOAT_EQ(3.0, movie_predictions[1][12]);
	ASSERT_FLOAT_EQ(4.5, movie_predictions[1][14]);
	ASSERT_FLOAT_EQ(2.0, movie_predictions[10][12]);
	ASSERT_FLOAT_EQ(3.5, movie_predictions[10][14]);}

// ---------------
// netflix_predict
// ---------------

TEST(NetflixFixture, netflix_predict_1){
int m_id = 1;
int c_id = 12;
map<int, float> m_ratings, c_ratings;
m_ratings[1] = 4.7;
c_ratings[12] = 2.0;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(3.0,est);}

TEST(NetflixFixture, netflix_predict_2){
int m_id = 1;
int c_id = 14;
map<int, float> m_ratings, c_ratings;
m_ratings[1] = 4.7;
c_ratings[14] = 3.5;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(4.5,est);}

TEST(NetflixFixture, netflix_predict_3){
int m_id = 10;
int c_id = 12;
map<int, float> m_ratings, c_ratings;
m_ratings[10] = 3.7;
c_ratings[12] = 2.0;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(2.0,est);}

TEST(NetflixFixture, netflix_predict_4){
int m_id = 10;
int c_id = 14;
map<int, float> m_ratings, c_ratings;
m_ratings[10] = 3.7;
c_ratings[14] = 3.5;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(3.5,est);}

TEST(NetflixFixture, netflix_predict_5){
int m_id = 1;
int c_id = 12;
map<int, float> m_ratings, c_ratings;
m_ratings[1] = 4.7;
c_ratings[12] = 5;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(5,est);}

TEST(NetflixFixture, netflix_predict_6){
int m_id = 1;
int c_id = 12;
map<int, float> m_ratings, c_ratings;
m_ratings[1] = 2;
c_ratings[12] = 1;
float est = netflix_predict(m_id, c_id, m_ratings, c_ratings);
ASSERT_FLOAT_EQ(1,est);}