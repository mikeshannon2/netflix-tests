// --------------------------------
// projects/netflix/TestNetflix.c++
// Angie Murphy 
// anm2727
// Brandon Torio
// bct562
// --------------------------------

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
// calculatePrediction
// ----

TEST(NetflixFixture, calc_Prediction1) {
  map<int, double> m1;
  map<int, double> m2;
  m1[0] = 0;
  m2[0] = 0;
  int i = 0;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, m1, m2);
  ASSERT_EQ(1, d);
}

TEST(NetflixFixture, calc_Prediction2) {
  map<int, double> m1;
  map<int, double> m2;
  m1[0] = 3.7;
  m2[1] = 3.7;
  int i = 1;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, m1, m2);
  ASSERT_EQ(3.7, d);
}

TEST(NetflixFixture, calc_Prediction3) {
  map<int, double> cust;
  map<int, double> movie;
  cust[0] = 4;
  movie[1] = 3;
  int i = 1;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, cust, movie);
  ASSERT_EQ(3.3, d);
}

TEST(NetflixFixture, calc_Prediction4) {
  map<int, double> cust;
  map<int, double> movie;
  cust[6] = 0;
  movie[0] = 0;
  int i = 0;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, cust, movie);
  ASSERT_EQ(1, d);
}

TEST(NetflixFixture, calc_Prediction5) {
  map<int, double> cust;
  map<int, double> movie;
  cust[0] = 4;
  movie[1] = 3;
  int i = 1;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, cust, movie);
  ASSERT_EQ(3.3, d);
}

TEST(NetflixFixture, calc_Prediction6) {
  map<int, double> cust;
  map<int, double> movie;
  movie[1] = 10;
  cust[0] = 10;
  int i = 1;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, cust, movie);
  ASSERT_EQ(5, d);
}

TEST(NetflixFixture, calc_Prediction7) {
  map<int, double> cust;
  map<int, double> movie;
  movie[1] = -5;
  cust[0] = -3.1;
  int i = 1;
  int j = 0;
  const double d = netflix_calculatePrediction(i, j, cust, movie);
  ASSERT_EQ(1, d);
}

// ----
// identify_movie
// ----

TEST(NetflixFixture, identify_movie1) {
  std::string str = "whom";
  bool check = netflix_identify_movie(str);
  ASSERT_EQ(false, check);
}

TEST(NetflixFixture, identify_movie2) {
  std::string str = "may the force be with you, always.";
  bool check = netflix_identify_movie(str);
  ASSERT_EQ(false, check);
}

TEST(NetflixFixture, identify_movie3) {
  std::string str = "Star Wars The Force Awakens:";
  bool check = netflix_identify_movie(str);
  ASSERT_EQ(true, check);
}

TEST(NetflixFixture, identify_movie4) {
  std::string str = "9001";
  bool check = netflix_identify_movie(str);
  ASSERT_EQ(false, check);
}

TEST(NetflixFixture, identify_movie5) {
  std::string str = "admiral ackbar says ::::: it's a trap!:!!!!";
  bool check = netflix_identify_movie(str);
  ASSERT_EQ(false, check);
}

//
//  netflix_add_to_sum
//

TEST(NetflixFixture, check_sum1) {
  std::string whom = "1.0";
  std::string ok = "2.0";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(1, check);
}

TEST(NetflixFixture, check_sum2) {
  std::string whom = "0";
  std::string ok = "0";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(0, check);
}

TEST(NetflixFixture, check_sum3) {
  std::string whom = "0";
  std::string ok = "0";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(0, check);
}

TEST(NetflixFixture, check_sum4) {
  std::string whom = "3";
  std::string ok = "5";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(4, check);
}

TEST(NetflixFixture, check_sum5) {
  std::string whom = "1.5";
  std::string ok = "0";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(2.25, check);
}

TEST(NetflixFixture, check_sum6) {
  std::string whom = "0";
  std::string ok = "0";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(0, check);
}

TEST(NetflixFixture, check_sum7) {
  std::string whom = "5";
  std::string ok = "4.5";
  double check = netflix_add_to_sum(whom, ok);
  ASSERT_EQ(.25, check);
}

//
//  netflix_calculateRMSE
//

TEST(NetflixFixture, check_RMSE1) {
  double check = netflix_calculateRMSE();
  bool b = check < 1;
  ASSERT_TRUE(b);
}

//
//  netflix_check_map
//

TEST(NetflixFixture, check_map1) {
  map<int, double> check = netflix_cacheData("wookie");
  bool b = check.empty();
  ASSERT_TRUE(b);
}
