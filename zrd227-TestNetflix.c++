


#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------
// begin test
//

TEST(NetflixFixture, test_1) {
    const bool b = true;
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, test_2) {
    const bool b = false;
    ASSERT_FALSE(b);
}


TEST(NetflixFixture, error_1) {
  double a[] = {1, 3, 5};
  double b[] = {2, 2, 2};
  double res[] = {0, 0, 0};
  double correct[] = {-1, 1, 3};
  array_error(a, b, res, 3);
  ASSERT_TRUE(equal(begin(res), end(res), begin(correct)));
}

TEST(NetflixFixture, error_2) {
  double a[] = {5, 2 , 7, 9, 13};
  double b[] = {4, 1, 3, 2, 1};
  double res[] = {0, 0, 0, 0, 0};
  double correct[] = {1, 1, 4, 7, 12};
  array_error(a, b, res, 5);
  ASSERT_TRUE(equal(begin(res), end(res), begin(correct)));
}

TEST(NetflixFixture, error_3) {
  double a[] = {-1, -5 , -8, -3, 13};
  double b[] = {4, 1, 3, 2, 1};
  double res[] = {0, 0, 0, 0, 0};
  double correct[] = {-5, -6, -11, -5, 12};
  array_error(a, b, res, 5);
  ASSERT_TRUE(equal(begin(res), end(res), begin(correct)));
}

TEST(NetflixFixture, square_1) {
  double a[] = {1, 3, -1, 4, 5};
  double correct[] = {1, 9, 1, 16, 25};
  array_square(a, 5);
  ASSERT_TRUE(double_arr_equals(a, correct, 5));
}

TEST(NetflixFixture, square_2) {
  double a[] = {3.5, 5.2, 2.4, 3.14, 1.2};
  double correct[] = {12.25, 27.04, 5.76, 9.8596, 1.44};
  array_square(a, 5);
  ASSERT_TRUE(double_arr_equals(a, correct, 5));
}

TEST(NetflixFixture, mean_1) {
  double a[] = {5, 5, 5, 5};
  double correct = 5.0;
  ASSERT_EQ(correct, array_mean(a, 4));
}

TEST(NetflixFixture, mean_2) {
  double a[] = {2.1, 1.3, 4.8, 3.9, 4.4};
  double correct = 3.3;
  ASSERT_EQ(correct, array_mean(a, 5));
}

TEST(NetflixFixture, mean_3) {
  double a[] = {4.8, 4.4, 4.3, 3.2, 3.9};
  double correct = 4.175;
  ASSERT_EQ(correct, array_mean(a, array_mean(a, 5)));
}


TEST(NetflixFixture, rsme_1) {
  double prediction[] = {4.3};
  double actual[] = {1.0};
  double r[] = {0.0};
  double result = calculate_rsme(prediction, actual, r, 1);
  ASSERT_TRUE(double_equals(3.3, result));
}

TEST(NetflixFixture, rsme_2) {
  double prediction[] = {3.3, 4.6, 3.8, 4.1, 4.7};
  double actual[] = {3.1, 4.3, 4.1, 4.1, 4.5};
  double r[] = {0.0, 0.0, 0.0, 0.0, 0.0};
  double result = calculate_rsme(prediction, actual, r, 5);
  ASSERT_TRUE(double_equals(0.228035, result));
}

TEST(NetflixFixture, rsme_3) {
  double prediction[] = {1.2, 3.2, 2.4, 4.9, 3.1};
  double actual[] = {2.2, 2.2, 3.4, 3.9, 4.1};
  double r[] = {0.0, 0.0, 0.0, 0.0, 0.0};
  double result = calculate_rsme(prediction, actual, r, 5);
  ASSERT_TRUE(double_equals(1.0, result));
}
// --------
// end test
// --------
