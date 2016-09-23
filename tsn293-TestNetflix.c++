/** @file TestNetflix.c++
 *  @brief contains unit tests for Netflix.c++
 *  
 *  `
 */

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"
#include "Netflix.h"

using namespace std;

// ----------
// initCaches
// ----------

// no tests

// -------------
// netflix_cache
// -------------

TEST(NetflixFixture, cache_1) {
  float testArr[11];
  istringstream r("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n6 3.08\n7 2.13\n8 3.19\n9 2.62\n10 3.18\n");
  netflix_cache(&r, testArr);
  EXPECT_FLOAT_EQ(testArr[6], 3.08);
}

// --------------------------
// netflix_cache_real_ratings
// --------------------------

TEST(NetflixFixture, cache_2) {
  map<int, map<int, int> > testMap;
  istringstream r("1 1772839 5\n1 1059319 3\n1 2380848 5\n1 548064 5\n10 1952305 3\n10 1531863 3");
  netflix_cache_real_ratings(&r, &testMap);
  ASSERT_TRUE(testMap.size() == 2);
}

// ----------------------------
// netflix_cache_user_deviation
// ----------------------------

TEST(NetflixFixture, cache_3) {
  map<int, float> testMap;
  istringstream r("5988 0.473906135731\n5989 -0.413743980355\n2142978 0.418924742715\n778283 0.00617904658619\n1450535 0.289039143899\n968454 0.0839771336555\n2142975 0.580948482645");
  netflix_cache_user_deviation(&r, &testMap);
  EXPECT_FLOAT_EQ(testMap.at(5989), -0.413743980355);
}

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("7 \n");
  int i = 1254;
  int j = 0;
  netflix_read(r, i, j);
  ASSERT_EQ(1254, i);
  ASSERT_EQ(7, j);
}

TEST(NetflixFixture, read_2) {
  istringstream r("102396: \n");
  int i = 0;
  int j = 0;
  netflix_read(r, i, j);
  ASSERT_EQ(102396, i);
  ASSERT_EQ(0, j);
}

TEST(NetflixFixture, read_3) {
  istringstream r("102396: \n");
  int i = 3194;
  int j = 49092;
  netflix_read(r, i, j);
  ASSERT_EQ(102396, i);
  ASSERT_EQ(0, j);
}

TEST(NetflixFixture, read_4) {
  istringstream r("5468 \n");
  int i = 15467;
  int j = 13146;
  netflix_read(r, i, j);
  ASSERT_EQ(15467, i);
  ASSERT_EQ(5468, j);
}

TEST(NetflixFixture, read_5) {
  istringstream r("134613 \n");
  int i = 1235;
  int j = 234456;
  netflix_read(r, i, j);
  ASSERT_EQ(1235, i);
  ASSERT_EQ(134613, j);
}

TEST(NetflixFixture, read_6) {
  istringstream r("12334: \n");
  int i = 4261;
  int j = 126143;
  netflix_read(r, i, j);
  ASSERT_EQ(12334, i);
  ASSERT_EQ(0, j);
}

// ----
// write
// ----

TEST(NetflixFixture, write_1) {
  ostringstream w;
  netflix_write(w, 2036, true);
  ASSERT_EQ("2036:\n", w.str());
}

TEST(NetflixFixture, write_2) {
  ostringstream w;
  netflix_write(w, 12348, true);
  ASSERT_EQ("12348:\n", w.str());
}

TEST(NetflixFixture, write_3) {
  ostringstream w;
  netflix_write(w, 5261, true);
  ASSERT_EQ("5261:\n", w.str());
}

TEST(NetflixFixture, write_4) {
  ostringstream w;
  netflix_write(w, 3.4, false);
  ASSERT_EQ("3.4\n", w.str());
}

TEST(NetflixFixture, write_5) {
  ostringstream w;
  netflix_write(w, 4.1, false);
  ASSERT_EQ("4.1\n", w.str());
}

TEST(NetflixFixture, write_6) {
  ostringstream w;
  netflix_write(w, 2.8, false);
  ASSERT_EQ("2.8\n", w.str());
}

// ----
// run
// ----

TEST(NetflixFixture, run_1) {
  istringstream avgMovieStream("1 3.75\n10 3.18\n");
  istringstream userDeviationStream("30878 0.0793479187896\n14756 0.0906247939492\n1952305 -0.284453061937\n1531863 -0.36267039976\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  istringstream r("1:\n30878\n14756\n10:\n1952305\n1531863\n");
  ostringstream w;
  netflix_run(r, w);
  ASSERT_EQ("1:\n3.8\n3.8\n10:\n2.8\n2.8\n", w.str());
}

 TEST(NetflixFixture, run_2) {
  istringstream avgMovieStream("10010 2.40\n");
  istringstream userDeviationStream("1462925, -0.0783349495429\n52050, 0.0449896572495\n650466, -0.298437852969\n");
  istringstream trueRatingStream("10010 1462925 4\n10010 52050 3\n10010 650466 1\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  netflix_cache_real_ratings(&trueRatingStream, &actualValues);
  istringstream r("10010:\n1462925\n52050\n650466");
  ostringstream w;
  netflix_run(r, w);
  ASSERT_EQ("10010:\n2.3\n2.4\n2.1\n", w.str());
}

 TEST(NetflixFixture, run_3) {
  istringstream avgMovieStream("14962 2.33\n14963 3.63");
  istringstream userDeviationStream("2368098, -0.683909994894\n1092338, 0.381024323673\n639977, 0.0885404900442\n439019, 0.145766979422\n2605407, 0.145766979422\n700173, -0.319966612935\n2192288, 0.567611937969\n748312, 0.00985584430694\n965555, -0.0963633360041\n1180941, -0.270610686384\n808471, 0.527328092888\n150597, -0.602208507615\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  istringstream r("14962:\n2368098\n1092338\n14963:\n639977\n439019\n2605407\n700173\n2192288\n748312\n965555\n1180941\n808471\n150597");
  ostringstream w;
  netflix_run(r, w);
  ASSERT_EQ("14962:\n1.6\n2.7\n14963:\n3.7\n3.7\n3.7\n3.3\n4.1\n3.6\n3.5\n3.3\n4.1\n3.0\n", w.str());
}

TEST(NetflixFixture, run_4) {
  istringstream avgMovieStream("10043 4.10\n");
  istringstream userDeviationStream("834820 0.0278739940703\n852886 -0.132757159516\n2204494 -0.114280859246\n774717 -0.517401553536\n1406050 -0.10556764337\n2317868 0.0109409004619\n202667 -0.319277781268\n1728377 0.021891830181\n2048837 0.604588366268\n1103080 -0.0766097928417\n510319 0.132302571778\n2314914 0.540739402473\n2460018 -0.19364272153\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  istringstream r("10043:\n834820\n852886\n2204494\n774717\n1406050\n2317868\n202667\n1728377\n2048837\n1103080\n510319\n2314914\n2460018");
  ostringstream w;
  netflix_run(r, w);
  ASSERT_EQ("10043:\n4.1\n3.9\n3.9\n3.5\n3.9\n4.1\n3.7\n4.1\n4.7\n4.0\n4.2\n4.6\n3.9\n", w.str());
}

 TEST(NetflixFixture, run_5) {
  istringstream avgMovieStream("10081 3.47\n10082 2.67");
  istringstream userDeviationStream("252944 0.19163576842\n1253220 0.202038319884\n1376599 -0.0629830948706\n298750 0.252664482191\n2408948 0.331735379187\n365261 -0.275472795566\n2542796 -0.0203825288528\n67679 0.345077237375\n2105693 -0.342794114917\n1484526 0.149568909643\n2032893 1.14525250105\n1088027 0.316097847532\n2015749 0.626203478014\n1137317 -0.333547993839\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  istringstream r("10081:\n252944\n1253220\n1376599\n298750\n2408948\n365261\n2542796\n10082:\n67679\n2105693\n1484526\n2032893\n1088027\n2015749\n1137317");
  ostringstream w;
  netflix_run(r, w);
  ASSERT_EQ("10081:\n3.6\n3.6\n3.4\n3.7\n3.8\n3.1\n3.4\n10082:\n3.0\n2.3\n2.8\n3.8\n2.9\n3.2\n2.3\n", w.str());
}


// -------
// predict
// -------

TEST(NetflixFixture, predict_1) {
  istringstream avgMovieStream("1227 1.50\n");
  istringstream userDeviationStream("156565 -0.919412196627\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  int m = 1227;
  int u = 156565;
  float r = netflix_predict(m, u);
  EXPECT_FLOAT_EQ(r, .5);
}

TEST(NetflixFixture, predict_2) {
  istringstream avgMovieStream("1223 2.81\n");
  istringstream userDeviationStream("795489 0.498173998743\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  int m = 1223;
  int u = 795489;
  float r = netflix_predict(m, u);
  EXPECT_FLOAT_EQ(r, 3.3);
}

TEST(NetflixFixture, predict_3) {
  istringstream avgMovieStream("1001 3.32\n");
  istringstream userDeviationStream("1050889 1.02756870833\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  int m = 1001;
  int u = 1050889;
  float r = netflix_predict(m, u);
  EXPECT_FLOAT_EQ(r, 4.3);
}

TEST(NetflixFixture, predict_4) {
  istringstream avgMovieStream("10021 2.01\n");
  istringstream userDeviationStream("2366406 0.157163745433\n");
  netflix_cache(&avgMovieStream, movieAvgs);
  netflix_cache_user_deviation(&userDeviationStream, &userDeviations);
  int m = 10021;
  int u = 2366406;
  float r = netflix_predict(m, u);
  EXPECT_FLOAT_EQ(r, 2.1);
}
