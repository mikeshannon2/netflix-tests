// --------------------------------
// projects/netflix/Testnetflix.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <fstream>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// netflix_read (5)
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("1:\n30878\n");
  int movie_id;
  vector<int> customer_id;
  const bool b = netflix_read(r, movie_id, customer_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, movie_id);
}

TEST(NetflixFixture, read_2) {
  istringstream r("");
  int movie_id;
  vector<int> customer_id;
  const bool b = netflix_read(r, movie_id, customer_id);
  ASSERT_FALSE(b);
}

TEST(NetflixFixture, read_3) {
  istringstream r("10:\n1952305\n1531863\n");
  int movie_id;
  vector<int> customer_id;
  const bool b = netflix_read(r, movie_id, customer_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(10, movie_id);
}

TEST(NetflixFixture, read_4) {
  istringstream r("\n");
  int movie_id;
  vector<int> customer_id;
  const bool b = netflix_read(r, movie_id, customer_id);
  ASSERT_FALSE(b);
}

TEST(NetflixFixture, read_5) {
  istringstream r("2222:\n30878\n");
  int movie_id;
  vector<int> customer_id;
  customer_id.push_back(10);
  customer_id.push_back(3000);
  customer_id.push_back(20);
  const bool b = netflix_read(r, movie_id, customer_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(2222, movie_id);
}

// ----
// netflix_eval (3)
// ----

TEST(NetflixFixture, eval_1) {
  vector<int> customer_ids;
  customer_ids.push_back(1.0);
  customer_ids.push_back(2.0);
  customer_ids.push_back(3.0);
  vector<double> v = netflix_eval(customer_ids, 101);
  vector<double> ratings;
  ratings.push_back(3.7);
  ASSERT_TRUE(v == ratings);
}

TEST(NetflixFixture, eval_2) {
  vector<int> customer_ids;
  vector<double> v = netflix_eval(customer_ids, 101);
  vector<double> ratings;
  ratings.push_back(3.7);
  ASSERT_TRUE(v == ratings);
}

TEST(NetflixFixture, eval_3) {
  vector<int> customer_ids;
  customer_ids.push_back(1.0);
  customer_ids.push_back(2.0);
  customer_ids.push_back(3.0);
  vector<double> v = netflix_eval(customer_ids, 101);
  vector<double> ratings;
  ratings.push_back(3.7);
  ASSERT_FALSE(v.empty());
}

// -----
// netflix_rmse (3)
// -----

TEST(NetflixFixture, rmse_1) {
  vector<double> predicted;
  predicted.push_back(2.8);
  predicted.push_back(2.6);
  vector<int> customer_ids;
  ifstream actual_ratings ("/u/downing/cs/netflix-cs371p/cyt276-as63439-actual-ratings.txt");
  double rmse = netflix_rmse(predicted, customer_ids, actual_ratings);
  ASSERT_TRUE(rmse == 1.3);
}

TEST(NetflixFixture, rmse_2) {

  static const double arr[] = {3.6, 3.2, 3.5, 4.7, 3.7, 3.9, 3.3, 3.6, 4, 3.5, 2.9, 3.5, 3.9, 3.9, 2.7, 3.9, 3.5, 4.5, 4.1, 4.1, 3, 5, 3.5, 2.8, 2.6};
  vector<double> predicted (arr, arr + sizeof(arr) / sizeof(arr[0]) );

  static const int cus_arr[] = {30878, 2647871, 1283744, 2488120, 317050, 1904905, 1989766, 14756, 1027056, 1149588, 1394012, 1406595, 2529547, 1682104, 625019, 2603381, 1774623, 470861, 12610, 1772839, 1059319, 2380848, 548064, 1952305, 1531863};
  vector<int> customer_ids (cus_arr, cus_arr + sizeof(cus_arr) / sizeof(cus_arr[0]));
  ifstream actual_ratings ("/u/downing/cs/netflix-cs371p/cyt276-as63439-actual-ratings.txt");
  double rmse = netflix_rmse(predicted, customer_ids, actual_ratings);

  ASSERT_TRUE(rmse == .79);
}

TEST(NetflixFixture, rmse_3) {
  static const double arr[] = {3.6, 3.2, 3.5, 4.7, 3.7, 3.9, 3.3, 3.6, 4, 3.5, 2.9, 3.5, 3.9, 3.9, 2.7, 3.9, 3.5, 4.5, 4.1, 4.1, 3, 5, 3.5};
  vector<double> predicted (arr, arr + sizeof(arr) / sizeof(arr[0]) );
  
  static const int cus_arr[] = {30878, 2647871, 1283744, 2488120, 317050, 1904905, 1989766, 14756, 1027056, 1149588, 1394012, 1406595, 2529547, 1682104, 625019, 2603381, 1774623, 470861, 12610, 1772839, 1059319, 2380848, 548064};
  vector<int> customer_ids (cus_arr, cus_arr + sizeof(cus_arr) / sizeof(cus_arr[0]));
  ifstream actual_ratings ("/u/downing/cs/netflix-cs371p/cyt276-as63439-actual-ratings.txt");
  double rmse = netflix_rmse(predicted, customer_ids, actual_ratings);
  ASSERT_TRUE(rmse == .82);
}

// -----
// print (3)
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  vector<double> predictions; 
  predictions.push_back(10);
  netflix_print(w, 123423, predictions);
  ASSERT_EQ("123423:\n10\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  vector<double> predictions; 
  netflix_print(w, 123423, predictions);
  ASSERT_EQ("123423:\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  vector<double> predictions; 
  predictions.push_back(10);
  predictions.push_back(20);
  predictions.push_back(30);
  predictions.push_back(40);
  predictions.push_back(50);
  predictions.push_back(60);
  netflix_print(w, 123423, predictions);
  ASSERT_EQ("123423:\n10\n20\n30\n40\n50\n60\n", w.str());
}

// -----
// solve (1)
// -----

TEST(NetflixFixture, solve) {
  istringstream r("10:\n1952305\n1531863");
  ostringstream w;
  ifstream probe("probe.txt");
  ifstream actualRatings ("/u/downing/cs/netflix-cs371p/cyt276-as63439-actual-ratings.txt");
  netflix_solve(r, w, probe, actualRatings);
  ASSERT_EQ("10:\n3.7\nRMSE: 0.29\n", w.str());
}