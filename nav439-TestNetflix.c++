// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------
#include <fstream> // cout, endl

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <cmath>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;


// -----
// netflix_actual_ratings_map
// -----

TEST(NetflixFixture, actual_map_1) {
	istringstream r("1 1059319 3");
    const map<int,std::map<int,int>> v = netflix_create_actual_rating_map(r);

    ASSERT_EQ(3, v.find(1)->second.find(1059319)->second);
   ;}

TEST(NetflixFixture, actual_map_2) {
	istringstream r("1 1059319 3\n1 30878 4");
    const map<int,std::map<int,int>> v = netflix_create_actual_rating_map(r);

    ASSERT_EQ(4, v.find(1)->second.find(30878)->second);    
    ;}

TEST(NetflixFixture, actual_map_3) {
	istringstream r("1 1059319 3\n1 30878 4\n3 1514528 4\n3 1543897 4\n3 1641505 4\n3 1822229 5\n3 1993442 5\n3 2081473 4\n3 2229289 4\n3 2251677 2\n3 2297310 5\n3 2344483 4\n3 2390623 3\n3 2428502 4\n3 2477231 4\n3 2561674 1\n4 410199 5\n4 2434289 2\n4 2498512 4\n4 2573419 3\n5 70199 4\n5 81979 5\n5 100750 5\n5 209999 5\n5 221630 1\n5 258801 5\n5 358664 5\n5 368977 5\n5 382445 4\n5 401117 3");
    const std::map<int,std::map<int,int>> v = netflix_create_actual_rating_map(r);

    ASSERT_EQ(4, v.find(3)->second.find(2229289)->second);    
    ;}

TEST(NetflixFixture, actual_map_4) {
	istringstream r("1 1059319 3\n1 30878 4\n3 1514528 4\n3 1543897 4\n3 1641505 4\n3 1822229 5\n3 1993442 5\n3 2081473 4\n3 2229289 4\n3 2251677 2\n3 2297310 5\n3 2344483 4\n3 2390623 3\n3 2428502 4\n3 2477231 4\n3 2561674 1\n4 410199 5\n4 2434289 2\n4 2498512 4\n4 2573419 3\n5 70199 4\n5 81979 5\n5 100750 5\n5 209999 5\n5 221630 1\n5 258801 5\n5 358664 5\n5 368977 5\n5 382445 4\n5 401117 3");
    const std::map<int,std::map<int,int>> v = netflix_create_actual_rating_map(r);

    ASSERT_EQ(2, v.find(4)->second.find(2434289)->second);
   ;}


// -----
// netflix_avg_movie_ratings_map
// -----

TEST(NetflixFixture, avg_movie_map_1) {
    istringstream r("1 2.6");
    const map<int,double> v = netflix_create_avg_movie_rating_map(r);

    ASSERT_EQ(2.6, v.find(1)->second);
    ;}


TEST(NetflixFixture, avg_movie_map_2) {
    istringstream r("1 8\n2 3.56\n3 3.64\n4 2.74\n5 3.92");
    const map<int,double> v = netflix_create_avg_movie_rating_map(r);

    ASSERT_EQ(8, v.find(1)->second);
   ;}

TEST(NetflixFixture, avg_movie_map_3) {
    istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92");
    const map<int,double> v = netflix_create_avg_movie_rating_map(r);

    ASSERT_EQ(3.56, v.find(2)->second);
    ;}


TEST(NetflixFixture, avg_movie_map_4) {
    istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92");
    const map<int,double> v = netflix_create_avg_movie_rating_map(r);

    ASSERT_EQ(3.92, v.find(5)->second);
    ;}


// -----
// netflix_avg_SD_map
// -----

TEST(NetflixFixture, SD_map_1) {
    istringstream r("1900 0.938956");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(1900)->second);
    ASSERT_EQ(0, x);
   ;}

TEST(NetflixFixture, SD_map_2) {
    istringstream r("1900 3.938956");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(1900)->second);
    ASSERT_EQ(3, x);
   ;}

TEST(NetflixFixture, SD_map_3) {
    istringstream r("2000 1.03436\n2900 0.850256\n3200 1.00705\n3300 0.927475\n3800 1.35401\n3900 1.26257\n4300 0.982135\n4700 1.26642\n5600 1.11699\n5900 1.11838");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(3200)->second);
    ASSERT_EQ(1, x);
   ;}


TEST(NetflixFixture, SD_map_4) {
    istringstream r("2000 1.03436\n2900 0.850256\n3200 1.00705\n3300 0.927475\n3800 1.35401\n3900 1.26257\n4300 0.982135\n4700 1.26642\n5600 1.11699\n5900 1.11838");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(2900)->second);
    ASSERT_EQ(0, x);
   ;}

TEST(NetflixFixture, SD_map_5) {
    istringstream r("2000 -1.03436\n2900 0.850256\n3200 1.00705\n3300 0.927475\n3800 1.35401\n3900 1.26257\n4300 0.982135\n4700 1.26642\n5600 1.11699\n5900 1.11838");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(2000)->second);
    ASSERT_EQ(-1, x);
   ;}


TEST(NetflixFixture, SD_map_6) {
    istringstream r("2000 -1.03436\n2900 0.850256\n3200 1.00705\n3300 0.927475\n3800 1.35401\n3900 1.26257\n4300 0.982135\n4700 1.26642\n5600 1.11699\n5900 1.11838");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(3200)->second);
    ASSERT_EQ(1, x);
   ;}

TEST(NetflixFixture, SD_map_7) {
    istringstream r("2136524 0.873743455656\n1219822 -0.223202008572\n1219824 -0.111816519315\n16708 -0.0644621125292\n842288 -0.671981084917");
    const map<int,double> v = netflix_create_SD_map(r);
    int x = (int)(v.find(1219824)->second);
    ASSERT_EQ(0, x);
   ;}

TEST(NetflixFixture, SD_map_8) {
    istringstream r("2136524 0.873743455656\n1219822 -0.223202008572\n1219824 -0.111816519315\n16708 -0.0644621125292\n842288 -0.671981084917");
    const map<int,double> v = netflix_create_SD_map(r);
    double x = v.find(16708)->second;
    ASSERT_EQ(-0.0644621125292, x);
   ;}

// -----
// netflix_predict
// -----

TEST(NetflixFixture, predict_1) {
    istringstream r("2136524 0.87\n1219822 -0.223202008572\n1219824 -0.111816519315\n16708 -0.0644621125292\n842288 -0.671981084917");
    netflix_create_SD_map(r);
    istringstream s("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92");
    netflix_create_avg_movie_rating_map(s);

    double v = netflix_predict(1, 2136524);
    ASSERT_EQ(4.62, v);}

TEST(NetflixFixture, predict_2) {
    istringstream r("2136524 0.87\n1219822 -0.223202008572\n1219824 -0.111816519315\n16708 -0.064\n842288 -0.671981084917");
    netflix_create_SD_map(r);
    istringstream s("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92");
    netflix_create_avg_movie_rating_map(s);

    double v = netflix_predict(5, 16708);
    ASSERT_EQ(3.856, v);}

// -----
// netflix_estimate
// -----

TEST(NetflixFixture, estimate_1) {
    istringstream actual_map("1 23 3.2");
    istringstream avg_movie("1 2");
    istringstream user_SD("23 0.5");
    istringstream r("1:\n23");
    ostringstream s;

    bool v = netflix_estimate_ratings (r, s, actual_map, avg_movie, user_SD);
    ASSERT_EQ(true, v);}