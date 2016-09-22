// -------------------
// netflix/Netflix.c++
//
// Robert Hinojosa
// Coty Kurtz
// -------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, read) {
  istringstream r("1 10\n");
  string i;
  const bool b = netflix_read(r, i);
  ASSERT_TRUE(b);
  ASSERT_EQ("1", i);
}

TEST(NetflixFixture, eval) {
  float movie_avg = 4.2;
  float customer_avg = 3.1;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 3.6);
}

TEST(NetflixFixture, eval2) {
  float movie_avg = 2.0;
  float customer_avg = 3.0;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 1.3);
}

TEST(NetflixFixture, eval3) {
  float movie_avg = 5.0;
  float customer_avg = 5.0;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 5.0);
}

TEST(NetflixFixture, eval4) {
  float movie_avg = 0.0;
  float customer_avg = 0.0;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 0.0);
}

TEST(NetflixFixture, eval5) {
  float movie_avg = 3.7;
  float customer_avg = 3.7;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 3.7);
}

TEST(NetflixFixture, eval6) {
  float movie_avg = -1.0;
  float customer_avg = -1.0;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 0.0);
}

TEST(NetflixFixture, eval7) {
  float movie_avg = 6.0;
  float customer_avg = 7.0;
  float prediction = netflix_eval(movie_avg, customer_avg);

  EXPECT_FLOAT_EQ(prediction, 5.0);
}

TEST(NetflixFixture, solve1) {
  istringstream r("2043:\n18273\n");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("2043:\n0.1\n", w.str());
}
