#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

map<int, float> fake_viewer_avg = {{1, 3.5}, {2, 4.0}, {3, 3.0}, {4, 4.5}, {5, 3.5}, {6, 4.5}};
map<int, float> fake_movie_avg = {{1, 3.5}};

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("87:\n");
  int i;
  bool flag;
  const bool b = read(r, i, flag);
  ASSERT_TRUE(b);
  ASSERT_EQ(87, i);
  ASSERT_TRUE(flag);}

TEST(NetflixFixture, read_2) {
  istringstream r("468853\n");       
  int i;
  bool flag;
  const bool b = read(r, i, flag);
  ASSERT_TRUE(b);
  ASSERT_EQ(468853, i);}

TEST(NetflixFixture, read_3) {
  istringstream r("34687:\n");       
  int i;
  bool flag;
  const bool b = read(r, i, flag);
  ASSERT_TRUE(b);
  ASSERT_EQ(34687, i);
  ASSERT_TRUE(flag);}

TEST(NetflixFixture, read_4) {
  istringstream r("001323\n");
  int i;
  bool flag;
  const bool b = read(r, i, flag);
  ASSERT_TRUE(b);
  ASSERT_EQ(1323, i);}


// ----
// eval
// ----
TEST(NetflixFixture, eval_1) {
  istringstream fake_actual("1:\n3\n");
  int i = 1;
  float sqerror = 0;
  int count = 0;
  float movie_avg_rating = 3.5;
  float result = eval(i, sqerror, count, movie_avg_rating, fake_actual, fake_viewer_avg);
  ASSERT_EQ(3.3f, result);}

TEST(NetflixFixture, eval_2) {
  istringstream fake_actual("1:\n4\n");
  int i = 2;
  float sqerror = 0;
  int count = 0;
  float movie_avg_rating = 3.5;
  float result = eval(i, sqerror, count, movie_avg_rating, fake_actual, fake_viewer_avg);
  ASSERT_EQ(3.8f, result);}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  float v = 3.4;
  print(w, v);
  ASSERT_EQ("3.4\n", w.str());}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  float v = 0.1;
  print(w, v);
  ASSERT_EQ("0.1\n", w.str());}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  float v = 0.9;
  print(w, v);
  ASSERT_EQ("0.9\n", w.str());}

TEST(NetflixFixture, print_4) {
  ostringstream w;
  float v = 0.1;
  print(w, v);
  ASSERT_EQ("0.1\n", w.str());}


// ----
// rmse
// ----

TEST(NetflixFixture, rmse_1) {
  float sqerror = 3.9605;
  int count = 5;
  float rmse_result = rmse(sqerror, count);
  ASSERT_EQ(0.89f, rmse_result);}

TEST(NetflixFixture, rmse_2) {
  float sqerror = 4.5864;
  int count = 6;
  float rmse_result = rmse(sqerror, count);
  ASSERT_EQ(0.87429972f, rmse_result);}

TEST(NetflixFixture, rmse_3) {
  float sqerror = 2.2445;
  int count = 5;
  float rmse_result = rmse(sqerror, count);
  ASSERT_EQ(0.67f, rmse_result);}

TEST(NetflixFixture, rmse_4) {
  float sqerror = 2.3232;
  int count = 3;
  float rmse_result = rmse(sqerror, count);
  ASSERT_EQ(0.88f, rmse_result);}


// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream fake_actual("1:\n3\n4\n3\n4\n3\n4\n");
  istringstream r("1:\n1\n2\n3\n4\n5\n6\n");
  ostringstream w;
  solve(r, w, fake_actual, fake_movie_avg, fake_viewer_avg);
  ASSERT_EQ("1:\n3.3\n3.8\n2.8\n4.3\n3.3\n4.3\nRMSE: 0.27\n", w.str());}
/*
TEST(NetflixFixture, solve_2) {
  istringstream r("1:\n2647871\n1283744\n2488120\n317050\n1904905\n");
  ostringstream w;
  solve(r, w);
  ASSERT_EQ("23946:\n3.7\n3.7\n3.7\n3.7\n3.7\nRMSE: 0.90\n", w.str());}

TEST(NetflixFixture, solve_3) {
  istringstream r("1:\n1\n1\n1\n1\n");
  ostringstream w;
  solve(r, w);
  ASSERT_EQ("1:\n3.7\n3.7\n3.7\n3.7\nRMSE: 0.43\n", w.str());}
*/

// ----
// eval
// ----
/*
TEST(NetflixFixture, eval_1) {
  int i = 1989766;
  float sqerror = 0.0;
  int count = 0;
  float movie_rating_avg = 3.75;
  float rating = eval(i, sqerror, count, movie_rating_avg);
  ASSERT_EQ(3.38f, rating);}
*/


