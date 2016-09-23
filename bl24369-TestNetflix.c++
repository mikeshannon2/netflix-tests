// --------------------------------
// projects/Netflix/TestNetflix.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"
#include "Netflix.h"
#include <cassert>  // assert
#include <iostream> // endl, istringstream, ostream
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <math.h>
#include "Netflix.h"
#include <iomanip>

using namespace std;

/* 6 functions total ==> 18 tests required
   Functions to test

   std::string Netflix_eval(std::string i, int j, int k) {			5
   bool Netflix_read(istringstream &r, std::string &i, int &j, int &k) {	5
   void Netflix_print(ostream &w, std::string v) {				6
   void Netflix_solve(istringstream &r, ostream &w) {				2

   
*/

// ----
// read
// ----
// default given by downing
TEST(NetflixFixture, read) {
  istringstream r("110:");
  std::string i;
  int j;
  int k;
  const bool b = Netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ("110:", i);
  ASSERT_EQ(110, j);
  ASSERT_EQ(1, k);
}

TEST(NetflixFixture, read1) {
  istringstream r("40:");
  std::string i;
  int j;
  int k;
  const bool b = Netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ("40:", i);
  ASSERT_EQ(40, j);
  ASSERT_EQ(1, k);
}

TEST(NetflixFixture, read2) {
  istringstream r("99");
  std::string i;
  int j;
  int k;
  const bool b = Netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ("99", i);
  ASSERT_EQ(99, j);
  ASSERT_EQ(0, k);
}

TEST(NetflixFixture, read3) {
  istringstream r("777");
  std::string i;
  int j;
  int k;
  const bool b = Netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ("777", i);
  ASSERT_EQ(777, j);
  ASSERT_EQ(0, k);
}

TEST(NetflixFixture, read4) {
  istringstream r("1234:");
  std::string i;
  int j;
  int k;
  const bool b = Netflix_read(r, i, j, k);
  ASSERT_TRUE(b);
  ASSERT_EQ("1234:", i);
  ASSERT_EQ(1234, j);
  ASSERT_EQ(1, k);
}


// ----
// eval
// ----
// Default tests given by downing
TEST(NetflixFixture, eval_1) {
  const std::string i("20:");
  int j = 20;
  int k = 1;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("20:", v);
} 

TEST(NetflixFixture, eval_2) {
  const std::string i("97");	//Avg rating of user 97 = 3.23
  int j = 97; 
  int k = 0;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("-3.7", v); 
}

TEST(NetflixFixture, eval_3) {
  const std::string i("0:");
  int j = 0; 
  int k = 1;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("0:", v); 
} 

TEST(NetflixFixture, eval_4) {
  const std::string i("1234");    //Avg rating of user 97 = 3.23
  int j = 1234; 
  int k = 0;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("-3.7", v); 
} 

TEST(NetflixFixture, eval_5) {
  const std::string i("664:");
  int j = 664;
  int k = 1;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("664:", v);
}
/*
TEST(NetflixFixture, eval_6) {
  const std::string i("555");    //Avg rating of user 97 = 3.23
  int j = 555;
  int k = 0;
  const std::string v = Netflix_eval(i,j,k);
  ASSERT_EQ("-3.7", v);
}
*/
// -----
// print
// -----

TEST(NetflixFixture, print) {
  ostringstream w;
  std::string s1("20");
  Netflix_print(w, s1);
  ASSERT_EQ("20\n", w.str());
}

TEST(NetflixFixture, print1) {
  ostringstream w;
  std::string s1("190");
  Netflix_print(w, s1);
  ASSERT_EQ("190\n", w.str());
}

TEST(NetflixFixture, print2) {
  ostringstream w;
  std::string s1("27");
  Netflix_print(w, s1);
  ASSERT_EQ("27\n", w.str());
}

TEST(NetflixFixture, print3) {
  ostringstream w;
  std::string s1("999");
  Netflix_print(w, s1);
  ASSERT_EQ("999\n", w.str());
}

TEST(NetflixFixture, print4) {
  ostringstream w;
  std::string s1("0");
  Netflix_print(w, s1);
  ASSERT_EQ("0\n", w.str());
}

TEST(NetflixFixture, print5) {
  ostringstream w;
  std::string s1("1234");
  Netflix_print(w, s1);
  ASSERT_EQ("1234\n", w.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve) {
  istringstream r("1:\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766\n14756\n1027056\n1149588\n1394012\n1406595\n2529547\n1682104\n2625019\n2603381\n1774623\n470861\n712610\n1772839\n1059319\n2380848\n548064\n");
  ostringstream w;
  Netflix_solve(r, w);
  ASSERT_EQ("1:\n3.68\n3.28\n3.59\n4.71\n3.7\n3.9\n3.38\n3.69\n4.03\n3.51\n2.96\n3.58\n3.97\n3.99\n2.78\n3.94\n3.58\n4.5\n4.13\n4.18\n3.07\n5.05\n3.52\n", w.str());
}

TEST(NetflixFixture, solve1) {
  istringstream r("10:\n1952305\n1531863\n");
  ostringstream w;
  Netflix_solve(r, w); 
  ASSERT_EQ("10:\n2.89\n2.63\n", w.str());
}

/*
TEST(NetflixFixture, solve2) {
  istringstream r("1000:\n2326571\n977808\n1010534\n1861759\n79755\n98259\n1960212\n97460\n2623506\n2409123\n1959111\n809597\n2251189\n537705\n929584\n506737\n708895\n1900790\n2553920\n1196779\n2411446\n1002296\n1580442\n100291\n433455\n2368043\n906984\n");
  ostringstream w;
  Netflix_solve(r, w); 
  ASSERT_EQ("1000:\n3.18\n2.87\n2.58\n4.58\n3.71\n3.34\n3.21\n3.87\n2.93\n2.44\n3.22\n3.47\n3.18\n4.26\n3.86\n2.98\n2.94\n2.97\n3.13\n3.58\n3.31\n3.85\n2.32\n2.99\n3.99\n3.03\n3.55\n", w.str());
}

TEST(NetflixFixture, solve3) {
  istringstream r("10001:\n262828\n2609496\n1474804\n831991\n267142\n2305771\n220050\n1959883\n27822\n2570808\n90355\n2417258\n264764\n143866\n766895\n714089\n2350428\n");
  ostringstream w;
  Netflix_solve(r, w); 
  ASSERT_EQ("10001:\n3.39\n4.29\n3.71\n2.69\n4.31\n3.42\n3.44\n3.98\n3.93\n3.53\n4.12\n4.13\n2.9\n4.17\n3.61\n3.46\n4.37\n", w.str());
}
*/
