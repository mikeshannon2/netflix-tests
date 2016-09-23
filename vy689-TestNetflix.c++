// --------------------------------
// projects/Netflix/TestNetflix.c++
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
#include <utility>  // pair
//#include <boost/archive/binary_iarchive.hpp>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("1:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(1, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_2) {
    istringstream r("1000:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(1000, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_3) {
    istringstream r("10007:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(10007, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_4) {
    istringstream r("8934:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(8934, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_5) {
    istringstream r("1923:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(1923, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_6) {
    istringstream r("10024:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(10024, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_7) {
    istringstream r("5112:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(5112, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_8) {
    istringstream r("9999:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(9999, m);
    ASSERT_EQ(0, u);}

TEST(NetflixFixture, read_9) {
    istringstream r("9876:\n");
    int           m;
    int           u;
    const bool b = netflix_read(r, m, u);
    ASSERT_TRUE(b);
    ASSERT_EQ(9876, m);
    ASSERT_EQ(0, u);}

// ----
// eval
// ----
/*
TEST(NetflixFixture, eval_1) {
    const float v = netflix_eval(1, 30878);
    ASSERT_FLOAT_EQ(3.6, v);}

TEST(NetflixFixture, eval_2) {
    const float v = netflix_eval(10, 1952305);
    ASSERT_FLOAT_EQ(2.8, v);}

TEST(NetflixFixture, eval_3) {
    const float v = netflix_eval(1000, 977808);
    ASSERT_FLOAT_EQ(2.8, v);}

TEST(NetflixFixture, eval_4) {
    const float v = netflix_eval(10006, 1093333);
    ASSERT_FLOAT_EQ(3.7, v);}
*/
// -----
// print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream w;
    netflix_print(w, 1, 10, 20);
    ASSERT_EQ("20\n", w.str());}

TEST(NetflixFixture, print_2) {
    ostringstream w;
    netflix_print(w, 200, 300, 500);
    ASSERT_EQ("500\n", w.str());}

TEST(NetflixFixture, print_3) {
    ostringstream w;
    netflix_print(w, 2345, 5678, 432);
    ASSERT_EQ("432\n", w.str());}

TEST(NetflixFixture, print_4) {
    ostringstream w;
    netflix_print(w, 5432, 6432, 5);
    ASSERT_EQ("5\n", w.str());}

TEST(NetflixFixture, print_5) {
    ostringstream w;
    netflix_print(w, 31, 532, 4);
    ASSERT_EQ("4\n", w.str());}

TEST(NetflixFixture, print_6) {
    ostringstream w;
    netflix_print(w, 654, 677, 53);
    ASSERT_EQ("53\n", w.str());}

TEST(NetflixFixture, print_7) {
    ostringstream w;
    netflix_print(w, 13, 34, 37);
    ASSERT_EQ("37\n", w.str());}

TEST(NetflixFixture, print_8) {
    ostringstream w;
    netflix_print(w, 476, 456, 34);
    ASSERT_EQ("34\n", w.str());}

TEST(NetflixFixture, print_9) {
    ostringstream w;
    netflix_print(w, 876, 980, 555);
    ASSERT_EQ("555\n", w.str());}
// -----
// solve
// -----
/*
TEST(NetflixFixture, solve_1) {
    istringstream r("10007:\n1204847\n2160216\n248206\n835054\n1064667\n2419805\n2084848\n671106\n2087887\n1340891\n1917538\n2018945\n2520477\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
	#ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10007:\n2\n2.6\n2.2\n2.2\n2\n2.4\n2.1\n2.8\n2.4\n2.7\n2.2\n2.5\n2.3\nRMSE: 1.18\n", w.str());}

TEST(NetflixFixture, solve_2) {
    istringstream r("10005:\n254775\n1892654\n469365\n793736\n926698\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
    #ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10005:\n3.5\n3.9\n3.2\n2.8\n2.9\nRMSE: 1.27\n", w.str());}

TEST(NetflixFixture, solve_3) {
    istringstream r("10008:\n1813636\n2048630\n930946\n1492860\n1687570\n1122917\n1885441\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
    #ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10008:\n4.6\n3.1\n3.4\n2.6\n4.1\n3.9\n3.9\nRMSE: 1.17\n", w.str());}

TEST(NetflixFixture, solve_4) {
    istringstream r("10009:\n1927533\n1789102\n2263612\n964421\n701514\n2120902\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
    #ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10009:\n2.9\n3.3\n4.5\n2.6\n2.5\n3.2\nRMSE: 1.14\n", w.str());}

TEST(NetflixFixture, solve_5) {
    istringstream r("10011:\n1624701\n2646826\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
    #ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10011:\n4.4\n4\nRMSE: 1.10\n", w.str());}

TEST(NetflixFixture, solve_6) {
    istringstream r("10012:\n2445069\n1483604\n418164\n2491070\n1485175\n1043648\n1913770\n2560523\n2416960\n161063\n56741\n2301550\n1275794\n");
    ostringstream w;
<<<<<<< HEAD
    netflix_solve(r, w);
=======
    #ifdef TRAVIS
    netflix_solve(r, w, 1);
	#else
	netflix_solve(r,w,0);
	#endif
>>>>>>> 26f19f8f4611839385f0248ecee22c117ff512bb
    ASSERT_EQ("10012:\n3\n3.9\n2.8\n3\n3.6\n3.7\n2.3\n3.2\n2.9\n3.2\n3.6\n3\n2.8\nRMSE: 1.03\n", w.str());}
*/
