#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// netflix_print Tests:
TEST(NetflixFixture, netflix_print_1){
  ostringstream w;
  string movieID = "123456";
  netflix_print(true, 3.7, movieID, w);
  ASSERT_EQ(w.str(), "3.7\n");
}

TEST(NetflixFixture, netflix_print_2){
  ostringstream w;
  string movieID = "123456";
  netflix_print(false, 3.7, movieID, w);
  ASSERT_EQ(w.str(), "123456:\n");
}

TEST(NetflixFixture, netflix_print_3){
  ostringstream w;
  string movieID = "123456";
  netflix_print(true, 3.723343242, movieID, w);
  ASSERT_EQ(w.str(), "3.7\n");
}

TEST(NetflixFixture, netflix_print_4){
  ostringstream w;
  string movieID = "123456";
  netflix_print(true, 0, movieID, w);
  ASSERT_EQ(w.str(), "0\n");
}

// netflix_read Tests:
TEST(NetflixFixture, netflix_read_1){
  string line = "1234:";
  string c = "";
  string m = "";

  bool result = netflix_read(line, c, m);
  ASSERT_EQ(result, false);
}

TEST(NetflixFixture, netflix_read_2){
  string line = "1234";
  string c = "";
  string m = "";

  bool result = netflix_read(line, c, m);
  ASSERT_EQ(result, true);
}

TEST(NetflixFixture, netflix_read_3){
  string line = "1234:";
  string c = "";
  string m = "";

  netflix_read(line, c, m);
  ASSERT_EQ(m, "1234");
}

TEST(NetflixFixture, netflix_read_4){
  string line = "1000000:";
  string c = "";
  string m = "";

  netflix_read(line, c, m);
  ASSERT_EQ(m, "1000000");
}

// split Tests:
TEST(NetflixFixture, split_1){
  string line = "Hello*World";

  vector<string> tokens = split(line, '*');
  ASSERT_EQ(tokens[0], "Hello");
}

TEST(NetflixFixture, split_2){
  string line = "Hello*World";

  vector<string> tokens = split(line, '*');
  ASSERT_EQ(tokens[1], "World");
}

TEST(NetflixFixture, split_3){
  string line = "0:World";

  vector<string> tokens = split(line, ':');
  ASSERT_EQ(tokens[0], "0");
}

TEST(NetflixFixture, split_4){
  string line = "0:1";

  vector<string> tokens = split(line, ':');
  ASSERT_EQ(tokens[1], "1");
}

TEST(NetflixFixture, split_5){
  string line = "i love cstmAvg";

  vector<string> tokens = split(line, ' ');
  ASSERT_EQ(tokens[1], "love");
}

// netflix_eval Tests:
TEST(NetflixFixture, netflix_eval_1){
  map<string, double> cacheAvgRatings;
  map<string, double> cacheAvgMovieRatings;
  string c = "0";
  string m = "1827";
  cacheAvgRatings["0"] = 3.5;
  cacheAvgMovieRatings["1827"] = 2.1;

  double result = netflix_eval(c, m, cacheAvgRatings, cacheAvgMovieRatings);
  ASSERT_DOUBLE_EQ(1.9, result);
}

TEST(NetflixFixture, netflix_eval_2){
  map<string, double> cacheAvgRatings;
  map<string, double> cacheAvgMovieRatings;
  string c = "0";
  string m = "1827";
  cacheAvgRatings["0"] = 0;
  cacheAvgMovieRatings["1827"] = 0;

  double result = netflix_eval(c, m, cacheAvgRatings, cacheAvgMovieRatings);
  ASSERT_DOUBLE_EQ(-3.7, result);
}

TEST(NetflixFixture, netflix_eval_3){
  map<string, double> cacheAvgRatings;
  map<string, double> cacheAvgMovieRatings;
  string c = "0";
  string m = "1827";
  cacheAvgRatings["0"] = 1;
  cacheAvgMovieRatings["1827"] = 2.7;

  double result = netflix_eval(c, m, cacheAvgRatings, cacheAvgMovieRatings);
  ASSERT_DOUBLE_EQ(0, result);
}

// generateCache Tests:
TEST(NetflixFixture, generateCache_1){
  ostringstream cacheFile;
  map<string, double> cacheAvgRatings;
  generateCache(cacheAvgRatings, "/u/downing/cs/netflix-cs371p/cat3239-rhl495-movie-averages.txt", ' ');
  ASSERT_DOUBLE_EQ(cacheAvgRatings["1"], 3.75);
}

TEST(NetflixFixture, generateCache_2){
  ostringstream cacheFile;
  map<string, double> cacheAvgRatings;
  generateCache(cacheAvgRatings, "/u/downing/cs/netflix-cs371p/cat3239-rhl495-movie-averages.txt", ' ');
  ASSERT_DOUBLE_EQ(cacheAvgRatings["2"], 3.56);
}

TEST(NetflixFixture, generateCache_3){
  ostringstream cacheFile;
  map<string, double> cacheAvgRatings;
  generateCache(cacheAvgRatings, "/u/downing/cs/netflix-cs371p/cat3239-rhl495-movie-averages.txt", ' ');
  ASSERT_DOUBLE_EQ(cacheAvgRatings["3"], 3.64);
}

TEST(NetflixFixture, generateCache_4){
  ostringstream cacheFile;
  map<string, double> cacheAvgRatings;
  generateCache(cacheAvgRatings, "/u/downing/cs/netflix-cs371p/cat3239-rhl495-movie-averages.txt", ' ');
  ASSERT_DOUBLE_EQ(cacheAvgRatings["4"], 2.74);
}

// netflix_solve Tests:
TEST(NetflixFixture, netflix_solve_1){
  istringstream r("1:\n30878\n2647871\n1283744");
  ostringstream w;
  
  netflix_solve(r, w);
  ASSERT_EQ(3.5, 3.5);

}




