


#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------
// begin test
//

TEST(NetflixFixture, test_1) {
    const bool b = true;
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, test_2) {
    const bool b = false;
    ASSERT_FALSE(b);
}

// -----------
// netflix_run
// -----------

TEST(NetflixFixture, run_1){
  istringstream r("1:\n2\n3\n1\n2:\n1\n4:\n");
  ostringstream w;
  int ratings[4][4] = {{3,5,4,3}, {4,4,5,3}, {2,1,3,2}, {4,1,3,3}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  netflix_run(r, w, customer_cache, movie_cache, actual_rating);
  ASSERT_EQ("1:\n7.8\n5.8\n5.8\n2:\n3.8\n4:\nRSME: 2.5865\n", w.str());
}

TEST(NetflixFixture, run_2){
  istringstream r("");
  ostringstream w;
  int ratings[4][4] = {{1,3,2,2}, {2,4,3,5}, {1,1,2,1}, {1,3,4,2}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  netflix_run(r, w, customer_cache, movie_cache, actual_rating);
  ASSERT_EQ("RSME: -nan\n", w.str());
}

TEST(NetflixFixture, run_3){
  istringstream r("3:\n1\n");
  ostringstream w;
  int ratings[4][4] = {{1,1,2,2}, {1,1,0,1}, {5,5,4,5}, {3,3,2,3}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  netflix_run(r, w, customer_cache, movie_cache, actual_rating);
  ASSERT_EQ("3:\n4\nRSME: 1\n", w.str());
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream w;
    netflix_print(w, 1.1);
    ASSERT_EQ("1.1\n", w.str());}

TEST(NetflixFixture, print_2) {
    ostringstream w;
    netflix_print(w, 3.7);
    ASSERT_EQ("3.7\n", w.str());}

TEST(NetflixFixture, print_3) {
    ostringstream w;
    netflix_print(w, 2.9);
    ASSERT_EQ("2.9\n", w.str());}

// ------------
// netflix_eval
// ------------

TEST(NetflixFixture, eval_1) {
  int ratings[4][4] = {{3,5,4,3}, {4,4,5,3}, {2,1,3,2}, {4,1,3,3}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  double estimated = netflix_eval(2,1,customer_cache, movie_cache, actual_rating);
  ASSERT_TRUE(double_equals(estimated, 3.8));
}

TEST(NetflixFixture, eval_2) {
  int ratings[4][4] = {{1,3,2,2}, {2,4,3,5}, {1,1,2,1}, {1,3,4,2}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  double estimated = netflix_eval(2,1,customer_cache, movie_cache, actual_rating);
  ASSERT_TRUE(double_equals(estimated, 3));
}

TEST(NetflixFixture, eval_3) {
  int ratings[4][4] = {{1,1,2,2}, {1,1,0,1}, {5,5,4,5}, {3,3,2,3}};
  map<double, double> movie_cache;
  map<double, double> customer_cache;
  map<int, map<int, int>> actual_rating;
  int customer_sums[4] = {};
  int movie_sums[4] = {};
  for(int a = 0; a<4; a++)
    for(int b = 0; b<4; b++){
      customer_sums[b]+=ratings[a][b];
      movie_sums[a]+=ratings[a][b];
      customer_sums[b]+=ratings[a][b];
      actual_rating[a][b] = ratings[a][b];
  }
  for(int a = 0; a<4; a++){
    movie_cache[a] = movie_sums[a]/4.0;
    customer_cache[a] = customer_sums[a]/4.0;
  }
  double estimated = netflix_eval(2,1,customer_cache, movie_cache, actual_rating);
  ASSERT_TRUE(double_equals(estimated, 6));
}

// -------------
// double_equals
// -------------

TEST(NetflixFixture, double_equals_1) {
    ASSERT_TRUE(double_equals(3.878957487, 3.878957487));}

TEST(NetflixFixture, double_equals_2) {
    ASSERT_FALSE(double_equals(4.878957487, 3.878957487));}

TEST(NetflixFixture, double_equals_3) {
    ASSERT_TRUE(double_equals(3.878957487, 3.878957488));}

// -----------------
// double_arr_equals
// -----------------

TEST(NetflixFixture, double__arr_equals_1) {
    double a[] = {3.3, 4.6, 3.8, 4.1, 4.7};
    double b[] = {3.1, 4.3, 4.1, 4.1, 4.5};
    ASSERT_FALSE(double_arr_equals(a,b,5));}

TEST(NetflixFixture, double_arr_equals_2) {
    double a[] = {3.1, 4.3, 4.1, 4.1, 4.5, 6.2};
    double b[] = {3.1, 4.3, 4.1, 4.1, 4.5};
    ASSERT_TRUE(double_arr_equals(a,b,5));}

TEST(NetflixFixture, double_arr_equals_3) {
    double a[] = {3.11, 4.3, 4.1, 4.1, 4.5, 6.2};
    double b[] = {3.1, 4.3, 4.1, 4.1, 4.5};
    ASSERT_FALSE(double_arr_equals(a,b,5));}

// --------------
// calculate_rsme
// --------------

TEST(NetflixFixture, rsme_1) {
  double result = calculate_rsme(15000, 341);
  ASSERT_TRUE(double_equals(6.632365324, result));
}

TEST(NetflixFixture, rsme_2) {
  double result = calculate_rsme(541, 274);
  ASSERT_TRUE(double_equals(1.405152146, result));
}

TEST(NetflixFixture, rsme_3) {
  double result = calculate_rsme(58274892789, 275274852);
  ASSERT_TRUE(double_equals(14.54981505, result));
}

// ------------
// netflix_read
// ------------

TEST(NetflixFixture, read_1) {
    istringstream r("0\n");
    int           i = -1;
    int           j;
    const bool b = netflix_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(-1, i);
    ASSERT_EQ(0, j);}

TEST(NetflixFixture, read_2) {
    istringstream r("0:\n");
    int           i;
    int           j;
    const bool b = netflix_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(0, i);
    ASSERT_EQ(-1, j);}

TEST(NetflixFixture, read_3) {
    istringstream r("");
    int           i;
    int           j;
    const bool b = netflix_read(r, i, j);
    ASSERT_FALSE(b);}

// --------
// end test
// --------
