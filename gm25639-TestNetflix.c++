// /** @file TestNetflix.c++
//  *  @brief Test script
//  *
//  *  Unit Tests.
//  */

// // --------
// // includes
// // --------

#include "gtest/gtest.h"
#include <iostream> // cout, endl
#include <list>     // list
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "Netflix.h"
#include "RunNetflix.c++"

using namespace std;

// // ------------
// // netflix eval
// // ------------

TEST(NetflixFixture, netflix_eval_1) {
  unordered_map<int, double> movie_avg_rating;
  movie_avg_rating[1] = 3.75;
  movie_avg_rating[10] = 3.18;
  unordered_map<int, double> customer_avg_rating;
  customer_avg_rating[1531863] = 3.94;
  customer_avg_rating[1027056] = 3.98;
  customer_avg_rating[1059319] = 3.02;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  actual_ratings_cache[10][1531863] = 3;
  actual_ratings_cache[1][1027056] = 3;
  actual_ratings_cache[1][1059319] = 3;
  istringstream r("1:\n1027056\n1059319\n10:\n1531863");
  ostringstream w;
  netflix_eval(r, w, movie_avg_rating, customer_avg_rating,
               actual_ratings_cache);
  ASSERT_EQ("1:\n4\n3\n10:\n2.6\nRMSE: 0.64\n", w.str());
}

TEST(NetflixFixture, netflix_eval_2) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  movie_avg_rating[1000] = 3.28;
  customer_avg_rating[1002296] = 4.27;
  customer_avg_rating[100291] = 3.41;
  actual_ratings_cache[1000][1002296] = 5;
  actual_ratings_cache[1000][100291] = 2;

  istringstream r("1000:\n1002296\n100291");
  ostringstream w;
  netflix_eval(r, w, movie_avg_rating, customer_avg_rating,
               actual_ratings_cache);
  ASSERT_EQ("100:\n3.8\n3\nRMSE: 1.07\n", w.str());
}

TEST(NetflixFixture, netflix_eval_3) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  movie_avg_rating[10000] = 2.9;
  customer_avg_rating[200206] = 4.41;
  customer_avg_rating[523108] = 4.26;
  actual_ratings_cache[10000][200206] = 5;
  actual_ratings_cache[10000][523108] = 4;
  istringstream r("10000:\n200206\n523108");
  ostringstream w;
  netflix_eval(r, w, movie_avg_rating, customer_avg_rating,
               actual_ratings_cache);
  ASSERT_EQ("10000:\n3.6\n3.4\nRMSE: 1.02\n", w.str());
}

// ------------------------
// netflix_construct_caches
// ------------------------

TEST(NetflixFixture, netflix_construct_caches_1) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  run_netflix_construct_caches(movie_avg_rating, customer_avg_rating,
                               actual_ratings_cache);

  ASSERT_EQ(4, actual_ratings_cache[10000][523108]);
}

TEST(NetflixFixture, netflix_construct_caches_2) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  run_netflix_construct_caches(movie_avg_rating, customer_avg_rating,
                               actual_ratings_cache);

  ASSERT_EQ(5, actual_ratings_cache[10000][200206]);
}

TEST(NetflixFixture, netflix_construct_caches_3) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  run_netflix_construct_caches(movie_avg_rating, customer_avg_rating,
                               actual_ratings_cache);

  ASSERT_EQ(2, actual_ratings_cache[1000][100291]);
}

TEST(NetflixFixture, netflix_construct_caches_4) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  run_netflix_construct_caches(movie_avg_rating, customer_avg_rating,
                               actual_ratings_cache);

  ASSERT_EQ(3, actual_ratings_cache[1][1059319]);
}

TEST(NetflixFixture, netflix_construct_caches_5) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  run_netflix_construct_caches(movie_avg_rating, customer_avg_rating,
                               actual_ratings_cache);

  ASSERT_EQ(3, actual_ratings_cache[1][1027056]);
}

// ------------
// netflix_solve
// ------------

TEST(NetflixFixture, netflix_solve_1) {
  unordered_map<int, double> movie_avg_rating;
  unordered_map<int, double> customer_avg_rating;
  unordered_map<int, unordered_map<int, int>> actual_ratings_cache;
  movie_avg_rating[10000] = 2.9;
  customer_avg_rating[200206] = 4.41;
  customer_avg_rating[523108] = 4.26;
  actual_ratings_cache[10000][200206] = 5;
  actual_ratings_cache[10000][523108] = 4;
  istringstream r("10000:\n200206\n523108");
  ostringstream w;
  netflix_solve(r, w, movie_avg_rating, customer_avg_rating,
                actual_ratings_cache);
  ASSERT_EQ("10000:\n3.6\n3.4\nRMSE: 1.02\n", w.str());
}