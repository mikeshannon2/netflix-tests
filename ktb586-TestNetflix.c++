// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// --------
// truncate
// --------

TEST(NetflixFixture, truncate_1) {
    string s = truncate_double(4.232, 2);
    ASSERT_EQ("4.23", s);
}

TEST(NetflixFixture, truncate_2) {
    string s = truncate_double(3.259932, 1);
    ASSERT_EQ("3.2", s);
}

TEST(NetflixFixture, truncate_3) {
    string s = truncate_double(1.99, 1);
    ASSERT_EQ("1.9", s);
}

// -----
// strip
// -----

TEST(NetflixFixture, strip_1) {
    int v = strip_colon("2034:");
    ASSERT_EQ(2034, v);
}

TEST(NetflixFixture, strip_2) {
    int v = strip_colon("17770:");
    ASSERT_EQ(17770, v);
}

TEST(NetflixFixture, strip_3) {
    int v = strip_colon("9:");
    ASSERT_EQ(9, v);
}

// --------
// lastchar
// --------

TEST(NetflixFixture, lastchar_1) {
    string s = strip_lastchar("1234");
    ASSERT_EQ("123", s);
}

TEST(NetflixFixture, lastchar_2) {
    string s = strip_lastchar("1043:");
    ASSERT_EQ("1043", s);
}

TEST(NetflixFixture, lastchar_3) {
    string s = strip_lastchar("12");
    ASSERT_EQ("1", s);
}

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
  istringstream r("1:\n\n");
  int movie_id;
  int user_id;
  bool is_user_id;
  const bool b = netflix_read(r, movie_id, user_id, is_user_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, movie_id);
}

TEST(NetflixFixture, read_2) {
  istringstream r("23401938\n\n");
  int movie_id;
  int user_id;
  bool is_user_id;
  const bool b = netflix_read(r, movie_id, user_id, is_user_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(23401938, user_id);
}

TEST(NetflixFixture, read_3) {
  istringstream r("17770:\n\n");
  int movie_id;
  int user_id;
  bool is_user_id;
  const bool b = netflix_read(r, movie_id, user_id, is_user_id);
  ASSERT_TRUE(b);
  ASSERT_EQ(17770, movie_id);
}

// -----
// parse
// -----

TEST(NetflixFixture, parse_ratings_1) {
    istringstream f("1 30878 4\n");
    unordered_map<int, unordered_map<int, double>> cache = parse_rating_cache(f);
    unordered_map<int, double> movie_info = cache[1];
    ASSERT_EQ(1, movie_info.size());
}

TEST(NetflixFixture, parse_ratings_2) {
    istringstream f("1 30878 4\n");
    unordered_map<int, unordered_map<int, double>> cache = parse_rating_cache(f);
    unordered_map<int, double> movie_info = cache[1];
    int rating = movie_info[30878];
    ASSERT_EQ(4, rating);
}

TEST(NetflixFixture, parse_ratings_3) {
    istringstream f("1023 299998 5\n");
    unordered_map<int, unordered_map<int, double>> cache = parse_rating_cache(f);
    unordered_map<int, double> movie_info = cache[1023];
    int rating = movie_info[299998];
    ASSERT_EQ(5, rating);
}

// -----------
// parse_cache
// -----------

TEST(NetflixFixture, parse_cache_1) {
    istringstream f("187423 4.0");
    unordered_map<int, double> c = parse_cache(f);
    int rating = c[187423];
    ASSERT_EQ(4.0, rating);
}

TEST(NetflixFixture, parse_cache_2) {
    istringstream f("9 1");
    unordered_map<int, double> c = parse_cache(f);
    int rating = c[9];
    ASSERT_EQ(1, rating);
}

TEST(NetflixFixture, parse_cache_3) {
    istringstream f("20 5.0");
    unordered_map<int, double> c = parse_cache(f);
    int rating = c[20];
    ASSERT_EQ(5.0, rating);
}

// ----
// eval
// ----

TEST(NetflixFixture, eval_1) {
    string r = netflix_eval(1, 22, false);
    ASSERT_EQ("1:\n", r);
}

TEST(NetflixFixture, eval_2) {
    string r = netflix_eval(17770, 22, false);
    ASSERT_EQ("17770:\n", r);
}

TEST(NetflixFixture, eval_3) {
    string r = netflix_eval(1023, 30878, false);
    ASSERT_EQ("1023:\n", r);
}

// -------------
// squared_error
// -------------

TEST(NetflixFixture, squared_error_1) {
    double d = squared_error(4.5, 4);
    ASSERT_DOUBLE_EQ(0.25, d);
}

TEST(NetflixFixture, squared_error_2) {
    double d = squared_error(5.0, 1);
    ASSERT_DOUBLE_EQ(16.0, d);
}

TEST(NetflixFixture, squared_error_3) {
    double d = squared_error(2.8, 2);
    ASSERT_DOUBLE_EQ(0.64, d);
}

// ----
// rmse
// ----

TEST(NetflixFixture, rmse_1) {
    string s = do_rmse(4.0, 15);
    ASSERT_EQ("RMSE: 0.51\n", s);
}

TEST(NetflixFixture, rmse_2) {
    string s = do_rmse(4.0, 10000);
    ASSERT_EQ("RMSE: 0.02\n", s);
}

TEST(NetflixFixture, rmse_3) {
    string s = do_rmse(2.3, 1100);
    ASSERT_EQ("RMSE: 0.04\n", s);
}

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
    ostringstream o;
    netflix_print(o, "1023:");
    ASSERT_EQ("1023:\n", o.str());
}

TEST(NetflixFixture, print_2) {
    ostringstream o;
    netflix_print(o, "2198400");
    ASSERT_EQ("2198400\n", o.str());
}

TEST(NetflixFixture, print_3) {
    ostringstream o;
    netflix_print(o, "17770:");
    ASSERT_EQ("17770:\n", o.str());
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream i("1:\n30878\n2647871\n");
    ostringstream o;
    istringstream avg_customer("30878 3.63\n2647871 3.95\n1283744 2.23\n2488120 4.65\n317050 4.75\n");
    istringstream avg_movie("1 3.75\n");
    istringstream ratings("1 30878 4\n1 2647871 4\n1 1283744 3\n1 2488120 5\n1 317050 5\n");
    netflix_solve(i, o, avg_customer, avg_movie, ratings);
    ASSERT_EQ("1:\n3.6\n4.0\nRMSE: 0.22\n", o.str());

}

TEST(NetflixFixture, solve_2) {
    istringstream i("1:\n1283744\n2488120\n317050\n");
    ostringstream o;
    istringstream avg_customer("30878 3.63\n2647871 3.95\n1283744 2.23\n2488120 4.65\n317050 4.75\n");
    istringstream avg_movie("1 3.75\n");
    istringstream ratings("1 30878 4\n1 2647871 4\n1 1283744 3\n1 2488120 5\n1 317050 5\n");
    netflix_solve(i, o, avg_customer, avg_movie, ratings);
    ASSERT_EQ("1:\n2.2\n4.7\n4.8\nRMSE: 0.38\n", o.str());

}

TEST(NetflixFixture, solve_3) {
    istringstream i("1:\n30878\n2647871\n1283744\n2488120\n317050\n");
    ostringstream o;
    istringstream avg_customer("30878 3.63\n2647871 3.95\n1283744 2.23\n2488120 4.65\n317050 4.75\n");
    istringstream avg_movie("1 3.75\n");
    istringstream ratings("1 30878 4\n1 2647871 4\n1 1283744 3\n1 2488120 5\n1 317050 5\n");
    netflix_solve(i, o, avg_customer, avg_movie, ratings);
    ASSERT_EQ("1:\n3.6\n4.0\n2.2\n4.7\n4.8\nRMSE: 0.38\n", o.str());

}
