#include <iostream>
#include <sstream>


#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ------------
// netflix_read
// ------------

TEST(NetflixFixture, read_none) {
  istringstream r("");
  string s;
  const bool b = netflix_read(r, s);
  ASSERT_FALSE(b);
}

TEST(NetflixFixture, read_one) {
  istringstream r("3249823:");
  string s;
  const bool b = netflix_read(r, s);
  ASSERT_EQ("3249823:", s);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, read_two) {
  istringstream r("43246\n546798:");
  string s;
  bool b = netflix_read(r, s);
  ASSERT_EQ("43246", s);
  ASSERT_TRUE(b);

  b = netflix_read(r, s);
  ASSERT_EQ("546798:", s);
  ASSERT_TRUE(b);
}

TEST(NetflixFixture, read_three) {
  istringstream r("43246\n546798:\n987642:");
  string s;
  bool b = netflix_read(r, s);
  ASSERT_EQ("43246", s);
  ASSERT_TRUE(b);

  b = netflix_read(r, s);
  ASSERT_EQ("546798:", s);
  ASSERT_TRUE(b);

  b = netflix_read(r, s);
  ASSERT_EQ("987642:", s);
  ASSERT_TRUE(b);
}


// -------------
// netflix_print_mov
// -------------

TEST(NetflixFixture, print_mov_one) {
  ostringstream w;
  netflix_print_mov(w, "234234:");
  ASSERT_EQ("234234:\n", w.str());
}

TEST(NetflixFixture, print_mov_two) {
  ostringstream w;
  netflix_print_mov(w, "4564564:");
  ASSERT_EQ("4564564:\n", w.str());
}

TEST(NetflixFixture, print_mov_three) {
  ostringstream w;
  netflix_print_mov(w, "1:");
  ASSERT_EQ("1:\n", w.str());
}

TEST(NetflixFixture, print_mov_four) {
  ostringstream w;
  netflix_print_mov(w, "21309234:");
  ASSERT_EQ("21309234:\n", w.str());
}


// -------------
// netflix_print_dec
// -------------

TEST(NetflixFixture, print_rate_one) {
  ostringstream w;
  netflix_print_rate(w, 3.1446, 2);
  ASSERT_EQ("3.14\n", w.str());
}

TEST(NetflixFixture, print_rate_two) {
  ostringstream w;
  netflix_print_rate(w, 4324.234, 1);
  ASSERT_EQ("4324.2\n", w.str());
}

TEST(NetflixFixture, print_rate_three) {
  ostringstream w;
  netflix_print_rate(w, 1.232211, 4);
  ASSERT_EQ("1.2322\n", w.str());
}

TEST(NetflixFixture, print_rate_four) {
  ostringstream w;
  netflix_print_rate(w, 23.43234365, 5);
  ASSERT_EQ("23.43234\n", w.str());
}


// ---------
// calc_rmse
// ---------

TEST(NetflixFixture, calc_one) {
  double result = calc_rmse(100.0, 25);
  ASSERT_EQ(2.0, result);
}

TEST(NetflixFixture, calc_two) {
  double result = calc_rmse(2340.0015, 15);
  ASSERT_EQ(12.49, result);
}

TEST(NetflixFixture, calc_three) {
  double result = calc_rmse(19.208, 20);
  ASSERT_EQ(0.98, result);
}

TEST(NetflixFixture, calc_four) {
  double result = calc_rmse(3.1212, 12);
  ASSERT_EQ(0.51, result);
}


// ----------------
// TruthCache tests
// ----------------

class TruthCacheTest: public::testing::Test {
protected:
  TruthCacheTest() : c() {}
  virtual void SetUp() {
    map<int, int> ratings_one;
    map<int, int> ratings_two;
    map<int, int> ratings_three;

    ratings_one[1] = 2;
    ratings_one[2] = 3;

    ratings_two[1] = 4;
    ratings_two[2] = 5;

    ratings_three[1] = 0;
    ratings_three[2] = 2;

    c.set_ratings(203, ratings_one);
    c.set_ratings(399, ratings_two);
    c.set_ratings(10, ratings_three);
  }
  TruthCache c;
};


TEST_F(TruthCacheTest, get_rating_one){
  int r = c.get_rating(1, 10);
  ASSERT_EQ(0, r);
}

TEST_F(TruthCacheTest, get_rating_two){
  int r = c.get_rating(2, 399);
  ASSERT_EQ(5, r);
}

TEST_F(TruthCacheTest, get_rating_three){
  int r = c.get_rating(2, 203);
  ASSERT_EQ(3, r);
}

TEST_F(TruthCacheTest, get_rating_four){
  int r = c.get_rating(1, 399);
  ASSERT_EQ(4, r);
}



// ----------------
// DataCache tests
// ----------------

class DataCacheTest: public::testing::Test {
protected:
  DataCacheTest() : c() {}
  virtual void SetUp() {
    c.set_customer(100, 3.7f, 1.4f);
    c.set_customer(234, 2.4f, 1.0f);
    c.set_customer(50322, 4.0f, 2.0f);
    c.set_customer(1092342, 1.3f, 3.0f);
    c.set_movie(3493, 3.0f, 1.2f);
    c.set_movie(23, 4.4f, 2.3f);
    c.set_movie(1103, 2.2f, 1.8f);
    c.set_movie(9883, 1.8f, 3.4f);
  }
  DataCache c;
};


TEST_F(DataCacheTest, get_customer_one){
  auto& customer = c.get_customer(100);
  ASSERT_EQ(3.7f, customer.rating_avg);
  ASSERT_EQ(1.4f, customer.rating_stdev);
}

TEST_F(DataCacheTest, get_customer_two){
  auto& customer = c.get_customer(234);
  ASSERT_EQ(2.4f, customer.rating_avg);
  ASSERT_EQ(1.0f, customer.rating_stdev);
}

TEST_F(DataCacheTest, get_customer_three){
  auto& customer = c.get_customer(50322);
  ASSERT_EQ(4.0f, customer.rating_avg);
  ASSERT_EQ(2.0f, customer.rating_stdev);
}

TEST_F(DataCacheTest, get_customer_four){
  auto& customer = c.get_customer(1092342);
  ASSERT_EQ(1.3f, customer.rating_avg);
  ASSERT_EQ(3.0f, customer.rating_stdev);
}

TEST_F(DataCacheTest, get_movie_one){
  auto& movie = c.get_movie(9883);
  ASSERT_EQ(1.8f, movie.rating_avg);
  ASSERT_EQ(3.4f, movie.rating_stdev);
}

TEST_F(DataCacheTest, get_movie_two){
  auto& movie = c.get_movie(1103);
  ASSERT_EQ(2.2f, movie.rating_avg);
  ASSERT_EQ(1.8f, movie.rating_stdev);
}

TEST_F(DataCacheTest, get_movie_three){
  auto& movie = c.get_movie(23);
  ASSERT_EQ(4.4f, movie.rating_avg);
  ASSERT_EQ(2.3f, movie.rating_stdev);
}

TEST_F(DataCacheTest, get_movie_four){
  auto& movie = c.get_movie(3493);
  ASSERT_EQ(3.0f, movie.rating_avg);
  ASSERT_EQ(1.2f, movie.rating_stdev);
}

