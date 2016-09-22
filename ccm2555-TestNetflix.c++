// --------------------------------
// projects/collatz/TestCollatz.c++
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

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, predictRating_1) {
	float customerAvg = 3.7;
	float movieAvg = 3.7;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.7f, p);}

TEST(NetflixFixture, predictRating_2) {
	float customerAvg = 3.8;
	float movieAvg = 3.7;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.8f, p);}

TEST(NetflixFixture, predictRating_3) {
	float customerAvg = 3.7;
	float movieAvg = 3.8;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.8f, p);}

TEST(NetflixFixture, predictRating_4) {
	float customerAvg = 0.0f;
	float movieAvg = 3.7f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(0.0f, p);}

TEST(NetflixFixture, predictRating_5) {
	float customerAvg = 3.7f;
	float movieAvg = 0.0f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(0.0f, p);}

TEST(NetflixFixture, predictRating_6) {
	float customerAvg = 3.7f;
	float movieAvg = 3.9f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.9f, p);}

TEST(NetflixFixture, predictRating_7) {
	float customerAvg = 4.0f;
	float movieAvg = 3.7f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(4.0f, p);}

TEST(NetflixFixture, predictRating_8) {
	float customerAvg = 4.0f;
	float movieAvg = 4.0f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(4.3f, p);}

TEST(NetflixFixture, predictRating_9) {
	float customerAvg = 4.0f;
	float movieAvg = 3.4f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.7f, p);}

TEST(NetflixFixture, predictRating_10) {
	float customerAvg = 0.0f;
	float movieAvg = 7.4f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.7f, p);}

TEST(NetflixFixture, predictRating_11) {
	float customerAvg = 3.7f;
	float movieAvg = 3.7f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(3.7f, p);}

TEST(NetflixFixture, predictRating_12) {
	float customerAvg = 0.0f;
	float movieAvg = 0.0f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ( -3.7f, p);}

TEST(NetflixFixture, predictRating_13) {
	float customerAvg = 5.0f;
	float movieAvg = 3.7f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(5.0f, p);}

TEST(NetflixFixture, predictRating_14) {
	float customerAvg = 5.0f;
	float movieAvg = 3.9f;
	float p = predictRating(customerAvg, movieAvg);
	ASSERT_EQ(5.2f, p);}


TEST(NetflixFixture, calculateRmse_1) {
	double d = 1.0;
	int n = 1;
	float r = calculateRmse(d , n);
	ASSERT_EQ(1.0f, r);}

TEST(NetflixFixture, calculateRmse_2) {
	double d = 8.0;
	int n = 2;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.0f, r);}

TEST(NetflixFixture, calculateRmse_3) {
	double d = 32.0;
	int n = 2;
	float r = calculateRmse(d , n);
	ASSERT_EQ(4.0f, r);}

TEST(NetflixFixture, calculateRmse_4) {
	double d = 32.0;
	int n = 8;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.0f, r);}

TEST(NetflixFixture, calculateRmse_5) {
	double d = 32.0;
	int n = 32;
	float r = calculateRmse(d , n);
	ASSERT_EQ(1.0f, r);}

TEST(NetflixFixture, calculateRmse_6) {
	double d = 64.0;
	int n = 4;
	float r = calculateRmse(d , n);
	ASSERT_EQ(4.0f, r);}

TEST(NetflixFixture, calculateRmse_7) {
	double d = 64.0;
	int n = 1;
	float r = calculateRmse(d , n);
	ASSERT_EQ(8.0f, r);}

TEST(NetflixFixture, calculateRmse_8) {
	double d = 64.0;
	int n = 16;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.0f, r);}

TEST(NetflixFixture, calculateRmse_9) {
	double d = 2.0;
	int n = 1;
	float r = calculateRmse(d , n);
	ASSERT_EQ(1.41f, r);}

TEST(NetflixFixture, calculateRmse_10) {
	double d = 4.0;
	int n = 2;
	float r = calculateRmse(d , n);
	ASSERT_EQ(1.41f, r);}

TEST(NetflixFixture, calculateRmse_11) {
	double d = 64.0;
	int n = 32;
	float r = calculateRmse(d , n);
	ASSERT_EQ(1.41f, r);}

TEST(NetflixFixture, calculateRmse_12) {
	double d = 8.0;
	int n = 1;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.82f, r);}

TEST(NetflixFixture, calculateRmse_13) {
	double d = 16.0;
	int n = 2;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.82f, r);}

TEST(NetflixFixture, calculateRmse_14) {
	double d = 64.0;
	int n = 8;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.82f, r);}

TEST(NetflixFixture, calculateRmse_15) {
	double d = 128.0;
	int n = 16;
	float r = calculateRmse(d , n);
	ASSERT_EQ(2.82f, r);}

TEST(NetflixFixture, assert_true) {
    ASSERT_EQ(true, true);}


















