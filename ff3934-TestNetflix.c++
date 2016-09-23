// -----------------------
// Netflix - project2
// Author: Farnoud Faghihi
// EID: ff3934
// -----------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// indluces
// --------

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --
// se
// --

TEST(NetflixFixture, se_1) {
   const float v = netflix_se(2.5, 2.4);
   ASSERT_NEAR(0.01, v, 0.0001);
}

TEST(NetflixFixture, se_2) {
   const float v = netflix_se(2.5, 2.5);
   ASSERT_NEAR(0.00, v, 0.0001);
}

TEST(NetflixFixture, se_3) {
   const float v = netflix_se(3.5, 2.5);
   ASSERT_NEAR(1.0, v, 0.0001);
}

// -------
// predict
// -------

TEST(NetflixFixture, predict_1) {
   const float v = netflix_predict(1.0, 2.0);
   ASSERT_NEAR(-0.7, v, 0.0001);
}

TEST(NetflixFixture, predict_2) {
   const float v = netflix_predict(2.5, 3.0);
   ASSERT_NEAR(1.8, v, 0.0001);
}

TEST(NetflixFixture, predict_3) {
   const float v = netflix_predict(2.0, 3.7);
   ASSERT_NEAR(2.0, v, 0.0001);
}

// -----
// ismid
// -----

TEST(NetflixFixture, ismid_1) {
   const bool b = netflix_ismid("30:");
   ASSERT_TRUE(b);
}

TEST(NetflixFixture, ismid_2) {
   const bool b = netflix_ismid("30");
   ASSERT_FALSE(b);
}

TEST(NetflixFixture, ismid_3) {
   const bool b = netflix_ismid("350:");
   ASSERT_TRUE(b);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
   ostringstream w;
   const float v = netflix_eval(w, 5.0, 5.0);
   ASSERT_NEAR(0.0, v, 0.0001); 
}

TEST(NetflixFixture, eval_2) {
   ostringstream w;
   const float v = netflix_eval(w, 4.0, 5.0);
   ASSERT_NEAR(1.0, v, 0.0001); 
}

TEST(NetflixFixture, eval_3) {
   ostringstream w;
   const float v = netflix_eval(w, 3.0, 5.0);
   ASSERT_NEAR(4.0, v, 0.0001); 
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
   ostringstream w;
   netflix_print(w, 2.5);
   ASSERT_EQ("2.5\n", w.str());
}

TEST(NetflixFixture, print_2) {
   ostringstream w;
   netflix_print(w, 22.5);
   ASSERT_EQ("22.5\n", w.str());
}

TEST(NetflixFixture, print_3) {
   ostringstream w;
   netflix_print(w, 2.435);
   ASSERT_EQ("2.4\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
   istringstream r("1:\n30878\n2647871\n1283744\n2488120\n");
   ostringstream w;
   netflix_solve(r, w);
   ASSERT_EQ("3.6\n3.2\n3.5\n4.7\n", w.str());
}

TEST(NetflixFixture, solve_2) {
   istringstream r("1000:\n2326571\n977808\n");
   ostringstream w;
   netflix_solve(r, w);
   ASSERT_EQ("3.1\n2.8\n", w.str());
}

TEST(NetflixFixture, solve_3) {
   istringstream r("1000:\n1010534\n1861759\n");
   ostringstream w;
   netflix_solve(r, w);
   ASSERT_EQ("2.5\n4.5\n", w.str());
}

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
   istringstream r("20\n");
   string str;
   const bool b = netflix_read(r, str);
   ASSERT_TRUE(b);
   ASSERT_EQ("20", str);
}

TEST(NetflixFixture, read_2) {
   istringstream r("320:\n");
   string str;
   const bool b = netflix_read(r, str);
   ASSERT_TRUE(b);
   ASSERT_EQ("320:", str);
}

TEST(NetflixFixture, read_3) {
   istringstream r("5420\n");
   string str;
   const bool b = netflix_read(r, str);
   ASSERT_TRUE(b);
   ASSERT_EQ("5420", str);
}
