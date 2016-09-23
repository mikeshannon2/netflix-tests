// --------
// includes
// --------

#include <iostream> // cout, endl
#include <fstream>
#include <sstream>  // istringtstream, ostringstream
#include <math.h>
#include <map>
#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read_int
// ----

TEST(NetflixFixture, read_int){
	ofstream temp;
	temp.open("temp.txt");
	temp << "100\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	int i;
	const bool a = netflix_read_int(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(100, i);
	const bool b = netflix_read_int(test,i);
	ASSERT_FALSE(b);
	test.close();
}

TEST(NetflixFixture, read_int_2){
	ofstream temp;
	temp.open("temp.txt");
	temp << "-1\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	int i;
	const bool a = netflix_read_int(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(-1, i);
	const bool b = netflix_read_int(test,i);
	ASSERT_FALSE(b);
	test.close();
}

TEST(NetflixFixture, read_int_3){
	ofstream temp;
	temp.open("temp.txt");
	temp << "0\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	int i;
	const bool a = netflix_read_int(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(0, i);
	const bool b = netflix_read_int(test,i);
	ASSERT_FALSE(b);
	test.close();
}

// ----
// read_double
// ----

TEST(NetflixFixture, read_double){
	ofstream temp;
	temp.open("temp.txt");
	temp << "10.43\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	double i;
	const bool a = netflix_read_double(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(10.43, i);
	const bool b = netflix_read_double(test,i);
	ASSERT_FALSE(b);
	test.close();
}

TEST(NetflixFixture, read_double_2){
	ofstream temp;
	temp.open("temp.txt");
	temp << "0.00\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	double i;
	const bool a = netflix_read_double(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(0.00, i);
	const bool b = netflix_read_double(test,i);
	ASSERT_FALSE(b);
	test.close();
}

TEST(NetflixFixture, read_double_3){
	ofstream temp;
	temp.open("temp.txt");
	temp << "-2.43\n";
	temp.close();
	ifstream test;
	test.open("temp.txt");
	double i;
	const bool a = netflix_read_double(test, i);
	ASSERT_TRUE(a);
	ASSERT_EQ(-2.43, i);
	const bool b = netflix_read_double(test,i);
	ASSERT_FALSE(b);
	test.close();
}

// ----
// print
// ----

TEST(NetflixFixture, print){
	ostringstream w;
	std::string temp ("Hello:");
	netflix_print(w, temp);
	ASSERT_EQ("Hello:\n", w.str());
}

TEST(NetflixFixture, print_2){
	ostringstream w;
	std::string temp ("cs371p");
	netflix_print(w, temp);
	ASSERT_EQ("cs371p\n", w.str());
}

TEST(NetflixFixture, print_3){
	ostringstream w;
	std::string temp ("Goodbye!!!");
	netflix_print(w, temp);
	ASSERT_EQ("Goodbye!!!\n", w.str());
}

// ----
// predict
// ----

TEST(NetflixFixture, predict){
	double movie = 4.0;
	double customer = 3.0;
	double result = netflix_predict(movie, customer);
	double expected = 3.3;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < 0.001);
}

TEST(NetflixFixture, predict_2){
	double movie = 5.0;
	double customer = 1.0;
	double result = netflix_predict(movie, customer);
	double expected = 2.3;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < 0.001);
}

TEST(NetflixFixture, predict_3){
	double movie = 2.0;
	double customer = 2.0;
	double result = netflix_predict(movie, customer);
	double expected = 0.3;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < 0.001);
}

// ----
// update sum
// ----

TEST(NetflixFixture, update_sum){
	double prediction = 3.5;
	int actual = 3;
	double sum = 0.0;
	update_sum(prediction, actual, sum);
	double expected = 0.25;
	double result = fabs(expected - sum);
	ASSERT_TRUE(result < 0.001);
}

TEST(NetflixFixture, update_sum_2){
	double prediction = 2.7;
	int actual = 3;
	double sum = 0.0;
	update_sum(prediction, actual, sum);
	double expected = 0.09;
	double result = fabs(expected - sum);
	ASSERT_TRUE(result < 0.001);
}

TEST(NetflixFixture, update_sum_3){
	double prediction = 3.85;
	int actual = 3;
	double sum = 0.0;
	update_sum(prediction, actual, sum);
	double expected = 0.7225;
	double result = fabs(expected - sum);
	ASSERT_TRUE(result < 0.00001);
}

// ----
// calculate_RMSE
// ----

TEST(NetflixFixture, calculate_RMSE){
	double sum = 75.34;
	int count = 15;
	double result = calculate_RMSE(sum, count);
	double expected = 2.241130;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < .000001);
}

TEST(NetflixFixture, calculate_RMSE_2){
	double sum = 98.72;
	int count = 17;
	double result = calculate_RMSE(sum, count);
	double expected = 2.409783;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < .000001);
}

TEST(NetflixFixture, calculate_RMSE_3){
	double sum = 40.32;
	int count = 12;
	double result = calculate_RMSE(sum, count);
	double expected = 1.83303;
	double diff = fabs(result - expected);
	ASSERT_TRUE(diff < .000001);
}

// ----
// create_map
// ----

TEST(NetflixFixture, create_map){
	std::map<int, double> test_map;
	ofstream test;
	test.open("test.txt");
	test << "1 2.33\n" ;
	test.close();
	ifstream r;
	r.open("test.txt");
	create_map(test_map, r);	
	ASSERT_FALSE(test_map.empty());
	r.close();
}

TEST(NetflixFixture, create_map_2){
	std::map<int, double> test_map;
	ofstream test;
	test.open("test.txt");
	test << "4 3.78\n" ;
	test.close();
	ifstream r;
	r.open("test.txt");
	create_map(test_map, r);
	double result = test_map[4];
	ASSERT_EQ(result, 3.78);
	r.close();
}

TEST(NetflixFixture, create_map_3){
	std::map<int, double> test_map;
	ofstream test;
	test.open("test.txt");
	test << "10354 4.5\n" ;
	test.close();
	ifstream r;
	r.open("test.txt");
	create_map(test_map, r);	
	double result = test_map[10354];
	ASSERT_EQ(result, 4.5);
	r.close();
}

TEST(NetflixFixture, create_map_4){
	std::map<int, double> test_map;
	ofstream test;
	test.open("test.txt");
	test << "70986 2.54\n" ;
	test.close();
	ifstream r;
	r.open("test.txt");
	create_map(test_map, r);	
	double result = test_map[70986];
	ASSERT_EQ(result, 2.54);
	r.close();
}

// ----
// Netflix solve
// ----

TEST(NetflixFixture, netflix_solve){
	istringstream r("1:\n30878\n2647871\n1283744\n2488120\n");
	ostringstream w;
	//mock answer cache
	ofstream answer;
	answer.open("answer.txt");
	answer << "1:\n3\n3\n3\n3\n";
	answer.close();
	ifstream answer_cache;
	answer_cache.open("answer.txt");
	//mock movie average rating cache
	ofstream movie;
	movie.open("movie.txt");
	movie << "1 3.2\n";
	movie.close();
	ifstream movie_cache;
	movie_cache.open("movie.txt");
	//mock customer average rating cache
	ofstream customer;
	customer.open("customer.txt");
	customer << "30878 3.2\n2647871 3.2\n1283744 3.2\n2488120 3.2\n";
	customer.close();
	ifstream customer_cache;
	customer_cache.open("customer.txt");

	double RMSE = netflix_solve (r, w, answer_cache, movie_cache, customer_cache);
	ASSERT_TRUE(RMSE < 1);

	answer_cache.close();
	movie_cache.close();
	customer_cache.close();

}

TEST(NetflixFixture, netflix_solve_2){
	istringstream r("1000:\n2326571\n977808\n1010534\n1861759\n");
	ostringstream w;
	//mock answer cache
	ofstream answer;
	answer.open("answer.txt");
	answer << "1000:\n3\n3\n3\n3";
	answer.close();
	ifstream answer_cache;
	answer_cache.open("answer.txt");
	//mock movie average rating cache
	ofstream movie;
	movie.open("movie.txt");
	movie << "1000 3.5\n";
	movie.close();
	ifstream movie_cache;
	movie_cache.open("movie.txt");
	//mock customer average rating cache
	ofstream customer;
	customer.open("customer.txt");
	customer << "2326571 3.5\n977808 3.5\n1010534 3.5\n1861759 3.5\n";
	customer.close();
	ifstream customer_cache;
	customer_cache.open("customer.txt");

	double RMSE = netflix_solve (r, w, answer_cache, movie_cache, customer_cache);
	ASSERT_TRUE(RMSE < 1);

	answer_cache.close();
	movie_cache.close();
	customer_cache.close();

}
