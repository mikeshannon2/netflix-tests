#include <iostream> 
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;



// Average

TEST(NetflixFixture, average_1){
    double cache[] = {2.1, 4.2, 7.7};
    string index = "2";
    double value = average(index, cache);
    ASSERT_EQ(7.7, value);
}

TEST(NetflixFixture, average_2){
    double cache[] = {2.1, 4.2, 7.7};
    string index = "0";
    double value = average(index, cache);
    ASSERT_EQ(2.1, value);
}

TEST(NetflixFixture, average_3){
    double cache[] = {2.1, 4.2, 7.7};
    string index = "1";
    double value = average(index, cache);
    ASSERT_EQ(4.2, value);
}

TEST(NetflixFixture, average_4){
    double cache[] = {2.1, 4.2, 7.7, 0};
    string index = "3";
    double value = average(index, cache);
    ASSERT_EQ(0, value);
}

//prediction

TEST(NetflixFixture, prediction_1){
    double average1 = 2.1;
    double average2 = 4.2;
    double predict = prediction(average1, average2);
    ASSERT_EQ(2.6, predict);
}

TEST(NetflixFixture, prediction_2){
    double average1 = 3.7;
    double average2 = 3.7;
    double predict = prediction(average1, average2);
    ASSERT_EQ(3.7, predict);
}

TEST(NetflixFixture, prediction_3){
    double average1 = 4.7;
    double average2 = 2.7;
    double predict = prediction(average1, average2);
    ASSERT_EQ(3.7, predict);
}

//RMSE

TEST(NetflixFixture, RMSE_1){
    int count = 1986;
    double difference = 1785.61;
    double rmse = RMSE(count, difference);
    double trunc =(int)(rmse*100);
    trunc /= 100;
    ASSERT_EQ(0.94, trunc);
}

TEST(NetflixFixture, RMSE_2){
    int count = 2000;
    double difference = 1785.61;
    double rmse = RMSE(count, difference);
    double trunc =(int)(rmse*100);
    trunc /= 100;
    ASSERT_EQ(0.94, trunc);
}

TEST(NetflixFixture, RMSE_3){
    int count = 2000;
    double difference = 1500;
    double rmse = RMSE(count, difference);
    double trunc =(int)(rmse*100);
    trunc /= 100;
    ASSERT_EQ(0.86, trunc);
}
