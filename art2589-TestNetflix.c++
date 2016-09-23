#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <cmath>    // sqrt
#include <fstream>  // ifs

#include "gtest/gtest.h"

#include "Netflix.h"

// predict
TEST(NetflixFixture, netflix_predict_1)
{
    float f = netflix_predict(3.9, 1.0);     
    ASSERT_FLOAT_EQ(1.2, f); 
}

TEST(NetflixFixture, netflix_predict_2)
{
    float f = netflix_predict(4.2, 1.0);     
    ASSERT_FLOAT_EQ(1.5, f);
}

TEST(NetflixFixture, netflix_predict_3)
{
    float f = netflix_predict(1.2, 4.7);     
    ASSERT_FLOAT_EQ(2.2, f);
}

TEST(NetflixFixture, netflix_predict_4)
{
    float f = netflix_predict(3.7, 3.7);     
    ASSERT_FLOAT_EQ(3.7, f);
}

// rmse
TEST(NetflixFixture, netflix_rmse_1)
{
    float f = netflix_rmse(3.0,2);
    ASSERT_FLOAT_EQ(sqrt(1.5), f);
}

TEST(NetflixFixture, netflix_rmse_2)
{
    float f = netflix_rmse(3.0,3);
    ASSERT_FLOAT_EQ(sqrt(1), f);
}

TEST(NetflixFixture, netflix_rmse_3)
{
    float f = netflix_rmse(5.0,9);
    ASSERT_FLOAT_EQ(sqrt(5.0/9), f);
}

TEST(NetflixFixture, netflix_rmse_4)
{
    float f = netflix_rmse(1.5,2);
    ASSERT_FLOAT_EQ(sqrt(0.75), f);
}





