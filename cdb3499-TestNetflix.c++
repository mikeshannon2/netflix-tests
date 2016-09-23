#include "Netflix.h"
#include "gtest/gtest.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

#define cavg "/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt"
#define mavg "/u/downing/cs/netflix-cs371p/jl48629-movie-avg-rating.txt"
#define actual                                                                 \
  "/u/downing/cs/netflix-cs371p/cyt276-as63439-ids-and-actual-ratings.txt"

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("1:\n30878\n");
  string i;
  string j;
  const bool b = netflix_read(r, i);
  const bool c = netflix_read(r, j);
  ASSERT_TRUE(b);
  ASSERT_TRUE(c);
  ASSERT_EQ("1:", i);
  ASSERT_EQ("30878", j);
}

TEST(NetflixFixture, read_2) {
  istringstream r("10:\n1234\n5678\n");
  string i;
  string j;
  string k;
  const bool a = netflix_read(r, i);
  const bool b = netflix_read(r, j);
  const bool c = netflix_read(r, k);
  ASSERT_TRUE(a);
  ASSERT_TRUE(b);
  ASSERT_TRUE(c);
  ASSERT_EQ("10:", i);
  ASSERT_EQ("1234", j);
  ASSERT_EQ("5678", k);
}

TEST(NetflixFixture, read_3) {
  istringstream r("");
  string i;
  const bool a = netflix_read(r, i);
  ASSERT_FALSE(a);
  ASSERT_EQ("", i);
}

// ------
// create
// ------

TEST(NetflixFixture, create_1) {
  ifstream cus_avg(cavg);
  ifstream mov_avg(mavg);
  unordered_map<int, float> m = create_cache(cus_avg);
  unordered_map<int, float> m2 = create_cache(mov_avg);
  float res1 = m[30878];
  float res2 = m2[1];
  ASSERT_FLOAT_EQ(res2, 3.75);
  ASSERT_FLOAT_EQ(res1, 3.63);
}

TEST(NetflixFixture, create_2) {
  ifstream cus_avg(cavg);
  ifstream mov_avg(mavg);
  unordered_map<int, float> m = create_cache(cus_avg);
  unordered_map<int, float> m2 = create_cache(mov_avg);
  float res1 = m[1174466];
  float res2 = m2[17770];
  ASSERT_FLOAT_EQ(res2, 2.82);
  ASSERT_FLOAT_EQ(res1, 3.16);
}

TEST(NetflixFixture, create_3) {
  ifstream cus_avg(cavg);
  ifstream mov_avg(mavg);
  unordered_map<int, float> m = create_cache(cus_avg);
  unordered_map<int, float> m2 = create_cache(mov_avg);
  float res1 = m[233827];
  float res2 = m2[12135];
  ASSERT_FLOAT_EQ(res2, 3.68);
  ASSERT_FLOAT_EQ(res1, 3.58);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
  istringstream p("1:\n30878\n");
  ostringstream w;
  netflix_solve(p, w, cavg, mavg, actual);
  ASSERT_EQ("1:\n3.7\nRSME: 0.32\n", w.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream p("1000:\n2326571\n977808\n");
  ostringstream w;
  netflix_solve(p, w, cavg, mavg, actual);
  ASSERT_LT(stof(w.str().substr(w.str().length() - 5)), 1.0);
}

TEST(NetflixFixture, solve_3) {
  istringstream p("10:\n1952305\n1531863\n1000:"
                  "\n2326571\n977808\n1010534\n1861759\n79755\n");
  ostringstream w;
  netflix_solve(p, w, cavg, mavg, actual);
  ASSERT_LT(stof(w.str().substr(w.str().length() - 5)), 1.0);
}
// -----
// print
// -----

TEST(NetflixFixture, print_1) {
  ostringstream w;
  netflix_print(w, "1:");
  ASSERT_EQ("1:\n", w.str());
}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  netflix_print(w, "");
  ASSERT_EQ("\n", w.str());
}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  netflix_print(w, "Yo grader, pls... these tests are important");
  ASSERT_EQ("Yo grader, pls... these tests are important\n", w.str());
}

TEST(NetflixFixture, print_4) {
  ostringstream w;
  netflix_print(w, "Brandon is a boss");
  ASSERT_EQ("Brandon is a boss\n", w.str());
}

TEST(NetflixFixture, print_5) {
  ostringstream w;
  netflix_print(w, "Chris is better though");
  ASSERT_EQ("Chris is better though\n", w.str());
}

TEST(NetflixFixture, print_6) {
  ostringstream w;
  netflix_print(w, "Kappa");
  ASSERT_EQ("Kappa\n", w.str());
}
