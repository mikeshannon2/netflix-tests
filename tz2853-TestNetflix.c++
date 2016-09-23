//This file includes tests for all methods which don't require any cache as their inputs.
// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

#include <iostream>
#include <sstream> 
#include <string> 
#include <utility> 

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

//Reading through stdin/out
TEST(NetflixFixture, read_1){
    istringstream r("116");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("116", out);
}

TEST(NetflixFixture, read_2){
    istringstream r("9999");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("9999", out);
}

TEST(NetflixFixture, read_3){
    istringstream r("1");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("1", out);
}

TEST(NetflixFixture, read_4){
    istringstream r("String");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("String", out);
}

TEST(NetflixFixture, read_5){
    istringstream r(":");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ(":", out);
}

TEST(NetflixFixture, read_6){
    istringstream r("jaxaxnaxnmsxi");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("jaxaxnaxnmsxi", out);
}

TEST(NetflixFixture, read_7){
    istringstream r("182jszs");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("182jszs", out);
}

TEST(NetflixFixture, read_8){
    istringstream r(";',.,./,");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ(";',.,./,", out);
}

TEST(NetflixFixture, read_9){
    istringstream r("IO");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("IO", out);
}

TEST(NetflixFixture, read_10){
    istringstream r("o");
    string out;
    const bool b = readSTD(r, out);
    ASSERT_TRUE(b);
    ASSERT_EQ("o", out);
}

//Checking if a string contains ':'
TEST(NetflixFixture, mid_1){
    string r = "Hello world";
    const bool b = ifMID(r);
    ASSERT_FALSE(b);
}

TEST(NetflixFixture, mid_2){
    string r = "Name: Wong";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, mid_3){
    string r = "></;:";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, mid_4){
    string r = "This is my passw0rd";
    const bool b = ifMID(r);
    ASSERT_FALSE(b);
}

TEST(NetflixFixture, mid_5){
    string r = "7389e9e9";
    const bool b = ifMID(r);
    ASSERT_FALSE(b);
}

TEST(NetflixFixture, mid_6){
    string r = "::::::::::::::";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, mid_7){
    string r = "EID: wkyu278";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, mid_8){
    string r = "ajskjc212:/'221";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

TEST(NetflixFixture, mid_9){
    string r = "--";
    const bool b = ifMID(r);
    ASSERT_FALSE(b);
}

TEST(NetflixFixture, mid_10){
    string r = "siacjajccaas:acascasac";
    const bool b = ifMID(r);
    ASSERT_TRUE(b);
}

//Testing truncation
TEST(NetflixFixture, truncation_1){
    double d = 3.14159265358979;
    const string newd = truncate(d, 2);
    ASSERT_EQ("3.14", newd);
}

TEST(NetflixFixture, truncation_2){
    double d = 2.18945;
    const string newd = truncate(d, 1);
    ASSERT_EQ("2.1", newd);
}

TEST(NetflixFixture, truncation_3){
    double d = 3.1;
    const string newd = truncate(d, 1);
    ASSERT_EQ("3.1", newd);
}

TEST(NetflixFixture, truncation_4){
    double d = 100.8778267654;
    const string newd = truncate(d, 3);
    ASSERT_EQ("100.877", newd);
}

TEST(NetflixFixture, truncation_5){
    double d = 2.75612;
    const string newd = truncate(d, 3);
    ASSERT_EQ("2.756", newd);
}

TEST(NetflixFixture, truncation_6){
    double d = 8.888888;
    const string newd = truncate(d, 4);
    ASSERT_EQ("8.8888", newd);
}

TEST(NetflixFixture, truncation_7){
    double d = 31.333333;
    const string newd = truncate(d, 1);
    ASSERT_EQ("31.3", newd);
}

TEST(NetflixFixture, truncation_8){
    double d = 1000.0001;
    const string newd = truncate(d, 1);
    ASSERT_EQ("1000", newd);
}

TEST(NetflixFixture, truncation_9){
    double d = 0.1892;
    const string newd = truncate(d, 3);
    ASSERT_EQ("0.189", newd);
}

TEST(NetflixFixture, truncation_10){
    double d = 0.00012;
    const string newd = truncate(d, 4);
    ASSERT_EQ("0.0001", newd);
}