// -------------------------------------
// netflix-hamza-and-brandon/Netflix.c++
// Copyright (C) 2016
// Hamza Muhammad & Brandon Pearson
// -------------------------------------

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

// ------------------
// read_std_dev_cache
// ------------------

TEST(NetflixFixture, std_dev_file_read_1) {
  ifstream sdur_file ("/u/downing/public_html/netflix-cs371p/seb3334-tsn293-avg-user-deviation.txt");
  const bool v = read_std_dev_cache(sdur_file);
  ASSERT_TRUE(v);
}

// -------------
// read_avg_movie_cache
// -------------

TEST(NetflixFixture, avg_movie_read_1) {
  ifstream amr_file ("/u/downing/public_html/netflix-cs371p/cyt276-as63439-avg-movie-ratings.txt");
  const bool v = read_avg_movie_cache(amr_file);
  ASSERT_TRUE(v);
}

// ------------
// netflix_read
// ------------

TEST(NetflixFixture, netflix_read_1) {
  istringstream r("\n");
  const bool b = netflix_read(r);
  ASSERT_FALSE(b);
}

// ----------------------
// find_difference_square
// ----------------------

TEST(NetflixFixture, netflix_difference_1) {
  float prediction = 0.0;
  float actual_value = 0.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 0.0);
}

TEST(NetflixFixture, netflix_difference_2) {
  float prediction = 1.0;
  float actual_value = 2.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 1.0);
}

TEST(NetflixFixture, netflix_difference_3) {
  float prediction = 1.0;
  float actual_value = 3.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 4.0);
}

TEST(NetflixFixture, netflix_difference_4) {
  float prediction = 3.0;
  float actual_value = 1.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 4.0);
}

TEST(NetflixFixture, netflix_difference_5) {
  float prediction = 1.0;
  float actual_value = 1.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 0.0);
}

TEST(NetflixFixture, netflix_difference_6) {
  float prediction = 6.0;
  float actual_value = 12.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 36.0);
}

TEST(NetflixFixture, netflix_difference_7) {
  float prediction = 0.0;
  float actual_value = 0.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 0.0);
}

TEST(NetflixFixture, netflix_difference_8) {
  float prediction = 2.0;
  float actual_value = 5.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 9.0);
}

TEST(NetflixFixture, netflix_difference_9) {
  float prediction = 5.0;
  float actual_value = 7.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 4.0);
}

TEST(NetflixFixture, netflix_difference_10) {
  float prediction = 1.0;
  float actual_value = 11.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 100.0);
}

TEST(NetflixFixture, netflix_difference_11) {
  float prediction = 5.0;
  float actual_value = 0.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 25.0);
}

TEST(NetflixFixture, netflix_difference_12) {
  float prediction = 1.0;
  float actual_value = 11.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 100.0);
}

TEST(NetflixFixture, netflix_difference_13) {
  float prediction = 6.0;
  float actual_value = 10.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 16.0);
}

TEST(NetflixFixture, netflix_difference_14) {
  float prediction = 7.0;
  float actual_value = 6.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 1.0);
}

TEST(NetflixFixture, netflix_difference_15) {
  float prediction = 5.0;
  float actual_value = 8.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 9.0);
}

TEST(NetflixFixture, netflix_difference_16) {
  float prediction = 9.0;
  float actual_value = 12.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 9.0);
}

TEST(NetflixFixture, netflix_difference_17) {
  float prediction = 7.0;
  float actual_value = 3.0;
  const float f = find_difference_square(prediction, actual_value);
  ASSERT_EQ(f, 16.0);
}


// -------------
// netflix_solve
// -------------

TEST(NetflixFixture, netflix_solve_1) {

  istringstream answer_file_string ("1:\n4\n4\n3\n5\n5\n4\n4\n4\n3\n4\n5\n4\n5\n4\n3\n5\n4\n5\n4\n5\n3\n5\n5");
  istringstream amr_file_string ("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18");
  istringstream sdur_file_string ("378466 0.7558109406\n378467 -0.262865673015\n378465 0.185231337326\n287141 0.118034903713\n1583077 0.510354737251\n287143 0.301855922428\n1583078 -1.25969216007\n1774516 -0.0941478285328\n378468 -0.52959366269\n370257 -0.247270331392");

  istringstream r("1:\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766\n14756\n1027056\n1149588\n1394012\n1406595\n2529547\n1682104\n2625019\n2603381\n1774623\n470861\n712610\n1772839\n1059319\n2380848\n548064");
  ostringstream w;
  netflix_solve(r, w, answer_file_string, amr_file_string, sdur_file_string);
  ASSERT_EQ("1:\n3.8\n3.4\n3.9\n4.8\n3.7\n4.1\n3.4\n3.8\n4.2\n3.5\n3.2\n3.6\n4.1\n3.8\n2.6\n3.8\n3.7\n4.7\n4.2\n4.1\n3.1\n4.7\n3.7\nRMSE: 0.77\n", w.str());
}

TEST(NetflixFixture, netflix_solve_2) {

  istringstream answer_file_string ("1:\n");
  istringstream amr_file_string ("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18");
  istringstream sdur_file_string ("378466 0.7558109406\n378467 -0.262865673015\n378465 0.185231337326\n287141 0.118034903713\n1583077 0.510354737251\n287143 0.301855922428\n1583078 -1.25969216007\n1774516 -0.0941478285328\n378468 -0.52959366269\n370257 -0.247270331392");


  istringstream r("10:\n1952305\n1531863");
  ostringstream w;
  netflix_solve(r, w, answer_file_string, amr_file_string, sdur_file_string);
  ASSERT_EQ("10:\n2.9\n2.8\nRMSE: -nan\n", w.str());
}

TEST(NetflixFixture, netflix_solve_3) {

   istringstream answer_file_string ("1:\n4\n4\n3\n5\n5\n4\n4\n4\n3\n4\n5\n4\n5\n4\n3\n5\n4\n5\n4\n5\n3\n5\n5");
  istringstream amr_file_string ("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18");
  istringstream sdur_file_string ("378466 0.7558109406\n378467 -0.262865673015\n378465 0.185231337326\n287141 0.118034903713\n1583077 0.510354737251\n287143 0.301855922428\n1583078 -1.25969216007\n1774516 -0.0941478285328\n378468 -0.52959366269\n370257 -0.247270331392");

  istringstream r("10000:\n200206\n523108");
  ostringstream w;
  netflix_solve(r, w, answer_file_string, amr_file_string, sdur_file_string);
  ASSERT_EQ("10000:\n3.6\n3.8\nRMSE: 1.75\n", w.str());
}

TEST(NetflixFixture, netflix_solve_4) {

  istringstream answer_file_string ("1:\n4\n4\n3\n5\n5\n4\n4\n4\n3\n4\n5\n4\n5\n4\n3\n5\n4\n5\n4\n5\n3\n5\n5");
  istringstream amr_file_string ("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18");
  istringstream sdur_file_string ("378466 0.7558109406\n378467 -0.262865673015\n378465 0.185231337326\n287141 0.118034903713\n1583077 0.510354737251\n287143 0.301855922428\n1583078 -1.25969216007\n1774516 -0.0941478285328\n378468 -0.52959366269\n370257 -0.247270331392");

  istringstream r("10038:\n885147\n1144499\n1411630\n1069925\n836219\n1417121\n461985\n1148007");
  ostringstream w;
  netflix_solve(r, w, answer_file_string, amr_file_string, sdur_file_string);
  ASSERT_EQ("10038:\n3.8\n3.2\n3.0\n3.4\n3.0\n3.6\n3.4\n3.1\nRMSE: 1.40\n", w.str());
}



