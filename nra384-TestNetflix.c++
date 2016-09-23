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

// # ----
// # RMSE
// # ----

TEST(NetflixFixture, rmse_1) {
  float nums[] = {2, 3, 4};
  vector<float> pred(nums, nums + sizeof(nums) / sizeof(float));
  vector<float> ans(nums, nums + sizeof(nums) / sizeof(float));
  ASSERT_EQ(rmse(pred, ans), 0);
}

TEST(NetflixFixture, rmse_2) {
  float nums[] = {2, 3, 4};
  float nums2[] = {4, 3, 2};
  vector<float> pred(nums, nums + sizeof(nums) / sizeof(float));
  vector<float> ans(nums2, nums2 + sizeof(nums2) / sizeof(float));
  ASSERT_FLOAT_EQ(rmse(pred, ans), 1.632993161855452);
}

TEST(NetflixFixture, rmse_3) {
  vector<float> pred(1000, 1);
  vector<float> ans(1000, 5);
  ASSERT_EQ(rmse(pred, ans), 4);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream r("1:\n30878\n2647871\n1283744\n2488120\n317050");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("1:\n3.68\n3.28\n3.59\n4.71\n3.70\nRMSE: 0.74\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("10009:\n1927533\n1789102\n2263612\n964421\n701514\n2120902");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("10009:\n2.95\n3.36\n4.52\n2.62\n2.52\n3.27\nRMSE: 0.98\n",
            w.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r(
      "10028:\n1986255\n1312610\n1527666\n1606775\n1649392\n1522640\n440956");
  ostringstream w;
  netflix_solve(r, w);
  ASSERT_EQ("10028:\n2.78\n3.03\n2.70\n3.78\n3.92\n2.64\n4.09\nRMSE: 0.99\n",
            w.str());
}

// ----
// answer
// ----

TEST(NetflixFixture, answer_1) {
  const int v = netflix_answer(2219254, 20);
  ASSERT_EQ(3, v);
}
TEST(NetflixFixture, answer_2) {
  const int v = netflix_answer(54864, 17770);
  ASSERT_EQ(1, v);
}
TEST(NetflixFixture, answer_3) {
  const int v = netflix_answer(1068024, 2000);
  ASSERT_EQ(4, v);
}
TEST(NetflixFixture, answer_4) {
  const int v = netflix_answer(1564241, 2000);
  ASSERT_EQ(3, v);
}
TEST(NetflixFixture, answer_5) {
  const int v = netflix_answer(1377774, 2000);
  ASSERT_EQ(4, v);
}

// ------
// predict
//

TEST(NetflixFixture, predict_1) {
  const float v = netflix_predict(30878, 1);
  ASSERT_FLOAT_EQ(3.6800001, v);
}
TEST(NetflixFixture, predict_2) {
  const float v = netflix_predict(1952305, 10);
  ASSERT_FLOAT_EQ(2.8900001, v);
}
TEST(NetflixFixture, predict_3) {
  const float v = netflix_predict(67976, 1001);
  ASSERT_FLOAT_EQ(3.3399999, v);
}
TEST(NetflixFixture, predict_4) {
  const float v = netflix_predict(1467790, 7241);
  ASSERT_FLOAT_EQ(2.8599999, v);
}
