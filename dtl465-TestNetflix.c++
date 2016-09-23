
// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>  // vector

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ------------
// split
// ------------
TEST(NetflixFixture, split_1) {
    string line = "I am in Downing's class";
    char delim = ' ';
    vector<string> p = split(line,delim);
    int i = 0;
    ASSERT_EQ(p[i++], "I");
    ASSERT_EQ(p[i++], "am");
    ASSERT_EQ(p[i++], "in");
    ASSERT_EQ(p[i++], "Downing's");
    ASSERT_EQ(p[i++], "class");
}

TEST(NetflixFixture, split_2) {
    string line = "Melody is so stressed";
    char delim = ' ';
    vector<string> p = split(line,delim);
    int i = 0;
    ASSERT_EQ(p[i++], "Melody");
    ASSERT_EQ(p[i++], "is");
    ASSERT_EQ(p[i++], "so");
    ASSERT_EQ(p[i++], "stressed");
}

TEST(NetflixFixture, split_3) {
    string line = "Dennis wants a good grade";
    char delim = ' ';
    vector<string> p = split(line,delim);
    int i = 0;
    ASSERT_EQ(p[i++], "Dennis");
    ASSERT_EQ(p[i++], "wants");
    ASSERT_EQ(p[i++], "a");
    ASSERT_EQ(p[i++], "good");
    ASSERT_EQ(p[i++], "grade");
}

TEST(NetflixFixture, solve_1) {
    istringstream r("1:\n30878\n2647871\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("1:\n3.7\n3.6\nRMSE: 0.32\n", w.str());
}

TEST(NetflixFixture, solve_2) {
    istringstream r("10:\n1952305\n1952305\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("10:\n3.2\n3.2\nRMSE: 0.23\n", w.str());
}

TEST(NetflixFixture, solve_3) {
    istringstream r("10020:\n922636\n1967058\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("10020:\n3.8\n3.9\nRMSE: 0.16\n", w.str());
}

TEST(NetflixFixture, solve_4) {
    istringstream r("10047:\n205729\n711436\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("10047:\n3.8\n3.9\nRMSE: 0.81\n", w.str());
}

TEST(NetflixFixture, solve_5) {
    istringstream r("10070:\n1611581\n2116105\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("10070:\n3.6\n2.2\nRMSE: 0.31\n", w.str());
}

TEST(NetflixFixture, solve_6) {
    istringstream r("5656:\n1784146\n1937456\n2026392\n");
    ostringstream w;
    netflix_solve (r,w);
    ASSERT_EQ("5656:\n3.7\n4.3\n3.6\nRMSE: 0.69\n", w.str());
}

TEST(NetflixFixture, cache_1) {
    string r = "/u/downing/cs/netflix-cs371p/kmd2557-fem392-avg-user-rating(ordered).txt";
    map<int, float>test_cache;
    make_cache(test_cache, r);
    auto it = test_cache.begin();
    float i = 3.42;
    ASSERT_EQ(it->second, i);
}

TEST(NetflixFixture, cache_2) {
    string r = "/u/downing/cs/netflix-cs371p/kmd2557-fem392-avg-user-rating(ordered).txt";
    map<int, float>test_cache;
    make_cache(test_cache, r);
    auto it = test_cache.begin();
    float i = 4.42, j = 5.42;
    ASSERT_EQ(++it->second, i);
    ASSERT_EQ(++it->second, j);
}

TEST(NetflixFixture, cache_3) {
    string r = "/u/downing/cs/netflix-cs371p/kmd2557-fem392-avg-movie-ratings.txt";
    map<int, float>test_cache;
    make_cache(test_cache, r);
    auto it = test_cache.begin();
    float i = 3.75, j = 3.56;
    ASSERT_EQ(it++->second,i);
    ASSERT_EQ(it->second, j);
}
