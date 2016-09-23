#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <fstream>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;


TEST(NetflixFixture, round_1) {
    const double v = roundToOneDec(1.4532);
    ASSERT_EQ(1.5, v);}

TEST(NetflixFixture, round_2) {
    const double v = roundToOneDec(3.3);
    ASSERT_EQ(3.3, v);}

TEST(NetflixFixture, round_3) {
    const double v = roundToOneDec(2.72462);
    ASSERT_EQ(2.7, v);}

TEST(NetflixFixture, round_4) {
    const double v = roundToOneDec(4.98);
    ASSERT_EQ(5.0, v);}

TEST(NetflixFixture, actual_1) {
    vector<int> actual = setUpActuals();
    ASSERT_EQ(4, actual[0]);}

TEST(NetflixFixture, actual_2) {
    vector<int> actual = setUpActuals();
    ASSERT_EQ(3, actual[2]);}

TEST(NetflixFixture, actual_3) {
    vector<int> actual = setUpActuals();
    ASSERT_EQ(5, actual[3]);}

TEST(NetflixFixture, token_1) {
    vector<string> actualRatings;
    string testString = "10 20 30 40";
    Tokenize(testString, actualRatings, " ");
    int val = stoi(actualRatings[0]);
    ASSERT_EQ(10, val);}

TEST(NetflixFixture, token_2) {
    vector<string> actualRatings;
    string testString = "10 20 30 40";
    Tokenize(testString, actualRatings, " ");
    int val = stoi(actualRatings[1]);
    ASSERT_EQ(20, val);}

TEST(NetflixFixture, token_3) {
    vector<string> actualRatings;
    string testString = "10 20 30 40";
    Tokenize(testString, actualRatings, " ");
    int val = stoi(actualRatings[2]);
    ASSERT_EQ(30, val);}

TEST(NetflixFixture, token_4) {
    vector<string> actualRatings;
    string testString = "10 20 30 40";
    Tokenize(testString, actualRatings, " ");
    int val = stoi(actualRatings[3]);
    ASSERT_EQ(40, val);}

TEST(NetflixFixture, avg_1) {
    ifstream custAvg("/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt");
    unordered_map<string, double> cache = setUpAverageCache(custAvg);
    string key = "1174466";
    ASSERT_EQ(3.16, cache[key]);}

TEST(NetflixFixture, avg_2) {
    ifstream custAvg("/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt");
    unordered_map<string, double> cache = setUpAverageCache(custAvg);
    string key = "1543642";
    ASSERT_EQ(3.85, cache[key]);}

TEST(NetflixFixture, solve) {
    istringstream r("1:\n30878\n2647871\n1283744");
    ostringstream w;
    netflix_eval(r, w);
    ASSERT_EQ("1:\n3.7\n3.3\n3.6\n0.559762\n", w.str());}