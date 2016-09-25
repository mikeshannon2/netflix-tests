// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----
double cust[200000];
double mov[17700];
int real_ratings[1];
string start = "1:\n";

TEST(NetflixFixture, read_1) {
    istringstream r("10");
    string output;
    const bool b = netflix_read(r, output);
    ASSERT_TRUE(b);
    ASSERT_EQ("10", output);
}

TEST(NetflixFixture, read_2){
    istringstream r("100000");
    string output;
    const bool b = netflix_read(r, output);
    ASSERT_TRUE(b);
    ASSERT_EQ("100000", output);
}

TEST(NetflixFixture, read_3){
    istringstream r("6548923");
    string output;
    const bool b = netflix_read(r, output);
    ASSERT_TRUE(b);
    ASSERT_EQ("6548923", output);
}

TEST(NetflixFixture, read_r){
    istringstream r("2043:");
    string output;
    const bool b = netflix_read(r, output);
    ASSERT_TRUE(b);
    ASSERT_EQ("2043:", output);

}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
    double avg_cust[200000];
    avg_cust[141745] = 2.63;
    double avg_movie[17700];
    avg_movie[2043] = 3.78;
    double avg_all = 3.5;
    double v = netflix_eval(2043, 141745, avg_cust, avg_movie, avg_all);
    int a = (int) (v * 100);
    ASSERT_EQ(290, a);}

TEST(NetflixFixture, eval_2) {
    double avg_cust[200000];
    avg_cust[141745] = 2.63;
    double avg_movie[17700];
    avg_movie[10851] = 3.85;
    double avg_all = 3.5;
    double v = netflix_eval(10851, 141745, avg_cust, avg_movie, avg_all);
    int a = (int)(v * 100);
    ASSERT_EQ(298, a);}


// ----
// rmse
// ----

TEST(NetflixFixture, rmse_1){
	int a = 8;
	int b = 2;
	const int v = rmse(a, b);
	ASSERT_EQ(2, v);
}

TEST(NetflixFixture, rmse_2){
	int a = 64;
	int b = 4;
	const int v = rmse(a, b);
	ASSERT_EQ(4, v);
}

TEST(NetflixFixture, rmse_3){
	int a = 64;
	int b = 1;
	const int v = rmse(a, b);
	ASSERT_EQ(8, v);
}

TEST(NetflixFixture, rmse_4){
	int a = 27;
	int b = 3;
	const int v = rmse(a, b);
	ASSERT_EQ(3, v);
}

// -------------
// getRealRating
// -------------

TEST(NetflixFixture, gRR_1){
	int real_ratings[5] = {4, 5, 2, 4, 1};
	int index = 2;
	const int v = getRealRating(index, real_ratings);
	ASSERT_EQ(2, v);
}

TEST(NetflixFixture, gRR_2){
	int real_ratings[1000];
	int index = 156;
	real_ratings[index] = 3;
	const int v = getRealRating(index, real_ratings);
	ASSERT_EQ(3, v);
}

TEST(NetflixFixture, gRR_3){
	int real_ratings[10000];
	int index = 9999;
	real_ratings[index] = 1;
	const int v = getRealRating(index, real_ratings);
	ASSERT_EQ(1, v);
}
TEST(NetflixFixture, gRR_4){
	int real_ratings[5] = {1, 2, 3, 4, 5};
	int index = 4;
	const int v = getRealRating(index, real_ratings);
	ASSERT_EQ(5, v);
}
// -----
// print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream w;
    double i = 3.44323;
    netflix_print(w, i);
    ASSERT_EQ("3.4", w.str());
}

TEST(NetflixFixture, print_2){
	ostringstream w;
	double i = 4.234234;
	netflix_print(w, i);
	ASSERT_EQ("4.2", w.str());
}

TEST(NetflixFixture, print_3){
	ostringstream w;
	double i = 1.7;
	netflix_print(w, i);
	ASSERT_EQ("1.7", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
    istringstream r("30878");
    cust[30878] = 3.63;
    mov[1] = 3.75;
    real_ratings[0] = 4;
    ostringstream w;
    netflix_solve(r, w, start, 3.451031, cust, mov, real_ratings);
    ASSERT_EQ("1:\n3.9\nRMSE: 0.071\n", w.str());
}
