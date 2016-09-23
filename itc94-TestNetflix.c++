#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, read_1) {
  istringstream probe("1:\n30878\n2647871\n1283744\n2488120");
  istringstream ratings("1 4 4 3 5");
  istringstream averages("3.75 3.63 3.23 3.54 4.66\n");
  int probe_id;
  int rating;
  double average;
  bool movie_id;
  const bool b = netflix_read(probe, ratings, averages, probe_id, rating,
                              average, movie_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, probe_id);
  ASSERT_EQ(1, rating);
  ASSERT_EQ(3.75, average);
  ASSERT_TRUE(movie_id);
}

TEST(NetflixFixture, read_2) {
  istringstream probe("1:\n30878\n2647871\n1283744\n2488120");
  istringstream ratings("1 4 4 3 5");
  istringstream averages("3.75 3.63 3.23 3.54 4.66\n");
  int probe_values[] = {1, 30878, 2647871, 1283744, 2488120};
  int rating_values[] = {1, 4, 4, 3, 5};
  double average_values[] = {3.75, 3.63, 3.23, 3.54, 4.66};
  bool movie_values[] = {true, false, false, false, false};
  int probe_id;
  int rating;
  double average;
  bool movie_id;
  for (int i = 0; i < 5; i++) {
    const bool b = netflix_read(probe, ratings, averages, probe_id, rating,
                                average, movie_id);
    ASSERT_TRUE(b);
    ASSERT_EQ(probe_values[i], probe_id);
    ASSERT_EQ(rating_values[i], rating);
    ASSERT_EQ(average_values[i], average);
    ASSERT_EQ(movie_values[i], movie_id);
  }
}

TEST(NetflixFixture, read_3) {
  istringstream probe("1:\n30878\n2647871\n1283744\n2488120");
  istringstream ratings("1 4 4 3 5");
  istringstream averages("3.75 3.63 3.23 3.54 4.66\n");
  int probe_values[] = {1, 30878, 2647871, 1283744, 2488120};
  int rating_values[] = {1, 4, 4, 3, 5};
  double average_values[] = {3.75, 3.63, 3.23, 3.54, 4.66};
  bool movie_values[] = {true, false, false, false, false};
  int probe_id;
  int rating;
  double average;
  bool movie_id;
  for (int i = 0; netflix_read(probe, ratings, averages, probe_id, rating,
                               average, movie_id);
       i++) {
    ASSERT_EQ(probe_values[i], probe_id);
    ASSERT_EQ(rating_values[i], rating);
    ASSERT_EQ(average_values[i], average);
    ASSERT_EQ(movie_values[i], movie_id);
  }
}

TEST(NetflixFixture, solve_1) {
  istringstream probe("1:\n12");
  istringstream ratings("1 4");
  istringstream averages("3.75 3.63\n");
  ostringstream out;
  netflix_solve(probe, ratings, averages, out);
  ASSERT_EQ("1:\n3.7\nRMSE: 0.29\n", out.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream probe("1:\n1\n2\n3\n4");
  istringstream ratings("3 4 3 4 3");
  istringstream averages("3.65 3.65 3.65 3.65 3.65\n");
  ostringstream out;
  netflix_solve(probe, ratings, averages, out);
  ASSERT_EQ("1:\n3.6\n3.6\n3.6\n3.6\nRMSE: 0.5\n", out.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream probe("1:\n30878\n2647871\n1283744\n2488120");
  istringstream ratings("1 4 4 3 5");
  istringstream averages("3.75 3.63 3.23 3.54 4.66\n");
  ostringstream out;
  netflix_solve(probe, ratings, averages, out);
  ASSERT_EQ("1:\n3.7\n3.3\n3.6\n4.7\nRMSE: 0.5\n", out.str());
}

TEST(NetflixFixture, trunc1_1) { ASSERT_EQ(0.0, trunc1(0)); }

TEST(NetflixFixture, trunc1_2) { ASSERT_EQ(5.0, trunc1(5.093232)); }

TEST(NetflixFixture, trunc1_3) { ASSERT_EQ(9.4, trunc1(9.493232)); }

TEST(NetflixFixture, trunc2_1) { ASSERT_EQ(0.00, trunc2(0)); }

TEST(NetflixFixture, trunc2_2) { ASSERT_EQ(5.09, trunc2(5.093232)); }

TEST(NetflixFixture, trunc2_3) { ASSERT_EQ(9.49, trunc2(9.493232)); }

TEST(NetflixFixture, predict_1) { ASSERT_EQ(3.6, trunc1(predict(3.65, 3.65))); }

TEST(NetflixFixture, predict_2) { ASSERT_EQ(3.3, trunc1(predict(3.0, 4.0))); }

TEST(NetflixFixture, predict_3) { ASSERT_EQ(3.3, trunc1(predict(4.0, 3.0))); }

TEST(NetflixFixture, error_1) { ASSERT_EQ(0, error(0, 0)); }

TEST(NetflixFixture, error_2) { ASSERT_EQ(1, error(10, 9)); }

TEST(NetflixFixture, error_3) { ASSERT_EQ(0.25, error(4.5, 5)); }

TEST(NetflixFixture, rmse_1) { ASSERT_EQ(0, trunc2(rmse(0, 10))); }

TEST(NetflixFixture, rmse_2) { ASSERT_EQ(1, trunc2(rmse(10, 10))); }

TEST(NetflixFixture, rmse_3) { ASSERT_EQ(1.25, trunc2(rmse(15.7, 10))); }