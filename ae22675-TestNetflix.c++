
// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "Netflix.h"
#include "gtest/gtest.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, netflix_read_1) {
  istringstream r("Kieran");
  string line;
  const bool result = netflix_read(r, line);
  ASSERT_TRUE(result);
  ASSERT_EQ(line, "Kieran");
}

TEST(NetflixFixture, netflix_read_2) {
  istringstream r("1575381");
  string line;
  const bool result = netflix_read(r, line);
  ASSERT_TRUE(result);
  ASSERT_EQ(line, "1575381");
}

TEST(NetflixFixture, netflix_read_3) {
  istringstream r("Kieran\n Adam");
  string line;
  const bool result = netflix_read(r, line);
  ASSERT_TRUE(result);
  ASSERT_EQ(line, "Kieran");

  const bool result2 = netflix_read(r, line);
  ASSERT_TRUE(result2);
  ASSERT_EQ(line, "Adam");
}

TEST(NetflixFixture, netflix_read_4) {
  istringstream r("3.58\n 1575381");
  string line;
  const bool result = netflix_read(r, line);
  ASSERT_TRUE(result);
  ASSERT_EQ(line, "3.58");

  const bool result2 = netflix_read(r, line);
  ASSERT_TRUE(result2);
  ASSERT_EQ(line, "1575381");
}

// ----
// parse_and_store_value
// ----

// storing in the map
TEST(NetflixFixture, parse_and_store_value_1) {
  std::map<const int, float> storage_map;

  ofstream write_file;
  write_file.open("test_input.txt");
  write_file << "1575381 3.58";
  write_file.close();

  ifstream read_file;
  read_file.open("test_input.txt");
  if (read_file.is_open()) {
    while (!read_file.eof()) {
      parse_and_store_value(read_file, storage_map);
    }
    read_file.close();
  }

  ASSERT_FLOAT_EQ(storage_map[1575381], 3.58);
  remove("test_input.txt");
}

// storing multiple in the map
TEST(NetflixFixture, parse_and_store_value_2) {
  std::map<const int, float> storage_map;

  ofstream write_file;
  write_file.open("test_input.txt");
  write_file << "1 3.58\n";
  write_file << "2 3.58\n";
  write_file << "3 3.58\n";
  write_file << "4 3.58";
  write_file.close();

  ifstream read_file;
  read_file.open("test_input.txt");
  if (read_file.is_open()) {
    while (!read_file.eof()) {
      parse_and_store_value(read_file, storage_map);
    }
    read_file.close();
  }

  ASSERT_FLOAT_EQ(storage_map[1], 3.58);
  ASSERT_FLOAT_EQ(storage_map[2], 3.58);
  ASSERT_FLOAT_EQ(storage_map[3], 3.58);
  ASSERT_FLOAT_EQ(storage_map[4], 3.58);
  remove("test_input.txt");
}

// overriteing a value at a key
TEST(NetflixFixture, parse_and_store_value_3) {
  std::map<const int, float> storage_map;

  ofstream write_file;
  write_file.open("test_input.txt");
  write_file << "1575381 3.58\n";
  write_file << "1575381 4.00\n";
  write_file << "1575381 -1.00";
  write_file.close();

  ifstream read_file;
  read_file.open("test_input.txt");
  if (read_file.is_open()) {
    while (!read_file.eof()) {
      parse_and_store_value(read_file, storage_map);
    }
    read_file.close();
  }

  ASSERT_FLOAT_EQ(storage_map[1575381], -1.00);
  remove("test_input.txt");
}

// overriteing a value at a key
TEST(NetflixFixture, parse_and_store_value_4) {
  std::map<const int, float> storage_map;

  ofstream write_file;
  write_file.open("test_input.txt");
  write_file << "1575381 3.58\n";
  write_file << "1575381 4.00\n";
  write_file << "1575381 -1.00";
  write_file.close();

  ifstream read_file;
  read_file.open("test_input.txt");
  if (read_file.is_open()) {
    while (!read_file.eof()) {
      parse_and_store_value(read_file, storage_map);
    }
    read_file.close();
  }

  ASSERT_FLOAT_EQ(storage_map[1575381], -1.00);
  remove("test_input.txt");
}

// empty map
TEST(NetflixFixture, parse_and_store_value_5) {
  std::map<const int, float> storage_map;

  ofstream write_file;
  write_file.open("test_input.txt");
  write_file << "1575381 1.00";
  write_file.close();

  ifstream read_file;
  read_file.open("test_input.txt");
  if (read_file.is_open()) {
    while (!read_file.eof()) {
      parse_and_store_value(read_file, storage_map);
    }
    read_file.close();
  }

  ASSERT_EQ(storage_map.size(), 1);
  remove("test_input.txt");
}

// ----
// compute_rmse
// ----
TEST(NetflixFixture, compute_rmse_1) {
  float set_one[] = {3.0, 6.0, 7.0};
  float set_two[] = {1.0, 2.0, 3.0};

  const float result = compute_rmse(set_one, set_two, 3.0);
  ASSERT_FLOAT_EQ(3.47, result);
}

TEST(NetflixFixture, compute_rmse_2) {
  float set_one[] = {3.0, 7.0, 1.0};
  float set_two[] = {10.0, 12.0, 5.0};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(5.48, result);
}

TEST(NetflixFixture, compute_rmse_3) {
  float set_one[] = {3.0, 6.0, 7.0, 10.0, 12.0, 53.0};
  float set_two[] = {3.0, 6.0, 7.0, 10.0, 12.0, 53.0};

  const float result = compute_rmse(set_one, set_two, 6);
  ASSERT_FLOAT_EQ(0.00, result);
}

TEST(NetflixFixture, compute_rmse_5) {
  float set_one[] = {1.5, 2.7, 3.5};
  float set_two[] = {1.4, 2.8, 3.3};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(0.15, result);
}

TEST(NetflixFixture, compute_rmse_6) {
  float set_one[] = {0.4, 1.0, 0.5};
  float set_two[] = {0.70, 1.0, 1.3};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(0.5, result);
}

TEST(NetflixFixture, compute_rmse_7) {
  float set_one[] = {1, 2, 3, 4, 5, 6};
  float set_two[] = {0, 0, 0, 0, 0, 0};

  const float result = compute_rmse(set_one, set_two, 6);
  ASSERT_FLOAT_EQ(3.9, result);
}

TEST(NetflixFixture, compute_rmse_8) {
  float set_one[] = {101, 102, 103, 104, 105, 1111, 90, 56, 23};
  float set_two[] = {101.5, 107.3, 101, 117, 118.3, 22.8, 59.9, 27.2, 25.6};

  const float result = compute_rmse(set_one, set_two, 9);
  ASSERT_FLOAT_EQ(363.06, result);
}

TEST(NetflixFixture, compute_rmse_9) {
  float set_one[] = {1.5, 2.7, 3.5, 78, .9, -0.2};
  float set_two[] = {1.4, 2.8, 90, 78, 1.0, 0.5};

  const float result = compute_rmse(set_one, set_two, 6);
  ASSERT_FLOAT_EQ(35.32, result);
}

TEST(NetflixFixture, compute_rmse_10) {
  float set_one[] = {0.15, 0.27, 0.35};
  float set_two[] = {14, 28, 33};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(26, result);
}

TEST(NetflixFixture, compute_rmse_11) {
  float set_one[] = {15, 27, 35};
  float set_two[] = {14, 28, 33};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(1.42, result);
}

TEST(NetflixFixture, compute_rmse_12) {
  float set_one[] = {100.5, 50, 25};
  float set_two[] = {98, 17, 45};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(22.33, result);
}

TEST(NetflixFixture, compute_rmse_13) {
  float set_one[] = {2.7, 6.7, 4.5};
  float set_two[] = {4.0, 10.0, 3.3};

  const float result = compute_rmse(set_one, set_two, 3);
  ASSERT_FLOAT_EQ(2.17, result);
}
