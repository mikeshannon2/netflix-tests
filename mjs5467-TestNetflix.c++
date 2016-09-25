#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, print_1) {
  ostringstream w;
  netflix_print(w, 1, 2.0);
  ASSERT_EQ("1:\n", w.str());}

TEST(NetflixFixture, print_2) {
  ostringstream w;
  netflix_print(w, 0, 3.52);
  ASSERT_EQ("3.5\n", w.str());}

TEST(NetflixFixture, print_3) {
  ostringstream w;
  netflix_print(w, 0, 2.2);
  ASSERT_EQ("2.2\n", w.str());}

TEST(NetflixFixture, load_data_1) {
  istringstream user_string("1,2.2\n5,3.9\n2,1.0\n");
  istringstream ratings_string("10:\n1,3\n2,1\n5,5\n4:\n1,5\n2,2\n5,4\n8:\n1,1\n2,2\n5,3\n");
  istringstream movie_string("4,2.3\n8,4.3\n10,3.5\n");
  
  double user_data[6];
  double movie_data[11];
  unordered_map<int, int> actual_ratings[11];
  load_data(user_string, ratings_string, movie_string, user_data,
	    movie_data, actual_ratings);
  ASSERT_EQ(user_data[1], 2.2);
  ASSERT_EQ(user_data[5], 3.9);
  ASSERT_EQ(user_data[2], 1.0);
  ASSERT_EQ(movie_data[4], 2.3);
  ASSERT_EQ(movie_data[8], 4.3);
  ASSERT_EQ(movie_data[10], 3.5);
  ASSERT_EQ(actual_ratings[10].at(1), 3);
  ASSERT_EQ(actual_ratings[10].at(2), 1);
  ASSERT_EQ(actual_ratings[10].at(5), 5);
  ASSERT_EQ(actual_ratings[4].at(1), 5);
  ASSERT_EQ(actual_ratings[4].at(2), 2);
  ASSERT_EQ(actual_ratings[4].at(5), 4);
  ASSERT_EQ(actual_ratings[8].at(1), 1);
  ASSERT_EQ(actual_ratings[8].at(2), 2);
  ASSERT_EQ(actual_ratings[8].at(5), 3);
}


TEST(NetflixFixture, load_data_2) {
  istringstream user_string("10,2.1\n3,1.1\n2,1.0\n");
  istringstream ratings_string("12:\n10,3\n3,1\n2,5\n3:\n10,5\n3,2\n2,4\n10:\n10,1\n3,2\n2,3\n");
  istringstream movie_string("12,4.9\n3,4.3\n10,2.7\n");
  
  double user_data[11];
  double movie_data[13];
  unordered_map<int, int> actual_ratings[13];
  load_data(user_string, ratings_string, movie_string, user_data,
	    movie_data, actual_ratings);
  ASSERT_EQ(user_data[2], 1.0);
  ASSERT_EQ(user_data[3], 1.1);
  ASSERT_EQ(user_data[10], 2.1);
  ASSERT_EQ(movie_data[12], 4.9);
  ASSERT_EQ(movie_data[3], 4.3);
  ASSERT_EQ(movie_data[10], 2.7);
  ASSERT_EQ(actual_ratings[10].at(2), 3);
  ASSERT_EQ(actual_ratings[10].at(3), 2);
  ASSERT_EQ(actual_ratings[10].at(10), 1);
  ASSERT_EQ(actual_ratings[3].at(2), 4);
  ASSERT_EQ(actual_ratings[3].at(3), 2);
  ASSERT_EQ(actual_ratings[3].at(10), 5);
  ASSERT_EQ(actual_ratings[12].at(2), 5);
  ASSERT_EQ(actual_ratings[12].at(3), 1);
  ASSERT_EQ(actual_ratings[12].at(10), 3);
}

TEST(NetflixFixture, load_data_3) {
  istringstream user_string("10,2.1\n3,1.1\n2,1.0\n");
  istringstream ratings_string("10:\n2,4\n3,3\n10,1\n3:\n3,5\n2,4\n10,2\n12:\n2,3\n3,1\n10,5\n");
  istringstream movie_string("12,4.9\n3,4.3\n10,2.7\n");
  
  double user_data[11];
  double movie_data[13];
  unordered_map<int, int> actual_ratings[13];
  load_data(user_string, ratings_string, movie_string, user_data,
	    movie_data, actual_ratings);
  ASSERT_EQ(user_data[2], 1.0);
  ASSERT_EQ(user_data[3], 1.1);
  ASSERT_EQ(user_data[10], 2.1);
  ASSERT_EQ(movie_data[12], 4.9);
  ASSERT_EQ(movie_data[3], 4.3);
  ASSERT_EQ(movie_data[10], 2.7);
  ASSERT_EQ(actual_ratings[10].at(2), 4);
  ASSERT_EQ(actual_ratings[10].at(3), 3);
  ASSERT_EQ(actual_ratings[10].at(10), 1);
  ASSERT_EQ(actual_ratings[3].at(2), 4);
  ASSERT_EQ(actual_ratings[3].at(3), 5);
  ASSERT_EQ(actual_ratings[3].at(10), 2);
  ASSERT_EQ(actual_ratings[12].at(2), 3);
  ASSERT_EQ(actual_ratings[12].at(3), 1);
  ASSERT_EQ(actual_ratings[12].at(10), 5);
}

TEST(NetflixFixture, read_1) {
  int a;
  int b;
  istringstream s("55:\n1025\n200\n");
  bool c = netflix_read(s, a, b);
  ASSERT_TRUE(c);
  ASSERT_EQ(a, 55);
  ASSERT_EQ(b, 0);
}

TEST(NetflixFixture, read_2) {
  int a;
  int b;
  istringstream s("1025\n200\n");
  bool c = netflix_read(s, a, b);
  ASSERT_TRUE(c);
  ASSERT_EQ(a, 0);
  ASSERT_EQ(b, 1025);
}

TEST(NetflixFixture, eval_1) {
  double u[] = {1.2, 2.4, 0, 4.3};
  double m[] = {2.1, 0, 0, 3.1};
  double pred = netflix_eval(1, 2, u, m);
  ASSERT_EQ(pred, 0.8);
}

TEST(NetflixFixture, eval_2) {
  double u[] = {1.2, 2.4, 0, 4.3};
  double m[] = {2.1, 0, 0, 3.1};
  double pred = netflix_eval(4, 4, u, m);
  ASSERT_EQ(pred, 3.7);
}

TEST(NetflixFixture, eval_3) {
  double u[] = {1.2, 4.5};
  double m[] = {4.0};
  double pred = netflix_eval(1, 2, u, m);
  ASSERT_EQ(pred, 2.0);
}

TEST(NetflixFixture, eval_4) {
  double u[] = {3.4};
  double m[] = {4.5, 3.9, 3.8};
  double pred = netflix_eval(3, 1, u, m);
  ASSERT_EQ(pred, 3.5);
}

TEST(NetflixFixture, solve_1) {
  istringstream r("3:\n10\n2\n4:\n5\n");
  ostringstream output;
  istringstream user_file("2,3.4\n3,4.0\n5,3.5\n10,4.1\n");
  istringstream ratings_stream("3:\n10,4\n2,4\n4:\n5,3\n");
  istringstream movie_file("3,4.1\n4,3.8\n");
  double user_data[11] = {0};
  double movie_data[5] = {0};
  unordered_map<int, int> actual_ratings[5];
  netflix_solve(r, output, user_file, ratings_stream, movie_file,
		user_data, movie_data, actual_ratings);
  ASSERT_EQ("3:\n4.5\n3.8\n4:\n3.6\nRMSE: 0.46\n", output.str());
}

TEST(NetflixFixture, solve_2) {
  istringstream r("7:\n1\n3:\n5\n");
  ostringstream output;
  istringstream user_file("1,4.4\n3,4.0\n5,3.0\n");
  istringstream ratings_stream("3:\n5,2\n2,4\n7:\n1,5\n");
  istringstream movie_file("3,3.4\n7,4.0\n");
  double user_data[6] = {0};
  double movie_data[8] = {0};
  unordered_map<int, int> actual_ratings[8];
  netflix_solve(r, output, user_file, ratings_stream, movie_file,
		user_data, movie_data, actual_ratings);
  ASSERT_EQ("7:\n4.7\n3:\n2.7\nRMSE: 0.53\n", output.str());
}

TEST(NetflixFixture, solve_3) {
  istringstream r("4:\n2\n11:\n8\n");
  ostringstream output;
  istringstream user_file("1,4.4\n2,4.0\n8,3.0\n");
  istringstream ratings_stream("4:\n2,3\n11:\n8,1\n");
  istringstream movie_file("4,3.1\n11,2.2\n");
  double user_data[9] = {0};
  double movie_data[12] = {0};
  unordered_map<int, int> actual_ratings[12];
  netflix_solve(r, output, user_file, ratings_stream, movie_file,
		user_data, movie_data, actual_ratings);
  ASSERT_EQ("4:\n3.4\n11:\n1.5\nRMSE: 0.41\n", output.str());
}
