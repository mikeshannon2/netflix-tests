// --------------------------
// projects/Netflix/Netflix.h
// Copyright (C) 2016
// Gilad Oved / Vincent Chow
// --------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <fstream> // for files
#include <sstream> //sstream
#include <unordered_map> //unordered maps
#include <cmath> //pow and sqrt

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

//-------------
//netflix_solve
//-------------

TEST(NetflixFixture, netflix_solve1) {
  istringstream r("13842:\n313881");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[13842] = 3.76;
  customer_map[313881] = 4.64;
  answer_map[13842][313881] = 5;

  netflix_solve(r, w, answer_map, movie_map, customer_map);
  ASSERT_EQ("13842:\n4.3\nRMSE: 0.71\n", w.str());
}

TEST(NetflixFixture, netflix_solve2) {
  istringstream r("10010:\n1462925\n52050\n650466\n1813166\n2224061\n815731");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[10010] = 2.4;

  customer_map[1462925] = 3.51;
  customer_map[52050] = 3.3;
  customer_map[650466] = 3.34;
  customer_map[1813166] = 4.18;
  customer_map[2224061] = 3.89;
  customer_map[815731] = 3.47;

  answer_map[10010][1462925] = 4;
  answer_map[10010][52050] = 3;
  answer_map[10010][650466] = 1;
  answer_map[10010][1813166] = 1;
  answer_map[10010][2224061] = 2;
  answer_map[10010][815731] = 4;

  netflix_solve(r, w, answer_map, movie_map, customer_map);
  ASSERT_EQ("10010:\n2.9\n2.8\n2.8\n3.2\n3.1\n2.8\nRMSE: 1.40\n", w.str());
}

TEST(NetflixFixture, netflix_solve3) {
  istringstream r("1002:\n2174660\n1685301\n2030264\n1419286\n10020:\n922636\n1967058\n1949297\n1562927\n");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[1002] = 3.45;
  movie_map[10020] = 3.83;

  customer_map[2174660] = 3.38;
  customer_map[1685301] = 2.98;
  customer_map[2030264] = 3.53;
  customer_map[1419286] = 3.70;
  
  customer_map[922636] = 3.78;
  customer_map[1967058] = 3.94;
  customer_map[1949297] = 3.55;
  customer_map[1562927] = 4.08;

  answer_map[1002][2174660] = 4;
  answer_map[1002][1685301] = 4;
  answer_map[1002][2030264] = 4;
  answer_map[1002][1419286] = 3;

  answer_map[10020][922636] = 4;
  answer_map[10020][1967058] = 4;
  answer_map[10020][1949297] = 5;
  answer_map[10020][1562927] = 5;

  netflix_solve(r, w, answer_map, movie_map, customer_map);
  ASSERT_EQ("1002:\n3.5\n3.3\n3.6\n3.7\n10020:\n3.9\n4.0\n3.8\n4.0\nRMSE: 0.68\n", w.str());
}


//-----------------
//calculate_rating
//-----------------

TEST(NetflixFixture, calculate_rating1) {
  istringstream r("13842:\n313881");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[13842] = 3.76;
  customer_map[313881] = 4.64;
  answer_map[13842][313881] = 5;
  int movie_id = 13842;
  string customer_id = "313881"; 

  ASSERT_EQ("4.3", netflix_calculate_rating(answer_map, movie_map, customer_map, customer_id, movie_id));
}

TEST(NetflixFixture, calculate_rating2) {
  istringstream r("1002:\n2030264");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[1002] = 3.45;
  customer_map[2030264] = 3.38;
  answer_map[1002][2030264] = 4;
  int movie_id = 1002;
  string customer_id = "2030264"; 

  ASSERT_EQ("3.5", netflix_calculate_rating(answer_map, movie_map, customer_map, customer_id, movie_id));
}

TEST(NetflixFixture, calculate_rating3) {
  istringstream r("1002:\n2174660");
  ostringstream w;

  unordered_map<int, unordered_map<int, int>> answer_map;
  unordered_map<int, float> movie_map;
  unordered_map<int, float> customer_map;

  movie_map[1002] = 3.45;
  customer_map[2174660] = 3.53;
  answer_map[1002][2174660] = 4;
  int movie_id = 1002;
  string customer_id = "2174660"; 

  ASSERT_EQ("3.6", netflix_calculate_rating(answer_map, movie_map, customer_map, customer_id, movie_id));
}


//------------
//netflix_read
//------------

TEST(NetflixFixture, netflix_read1) {
	istringstream r("1");
	string i;
	bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("1", i);
}

TEST(NetflixFixture, netflix_read2) {
	istringstream r("133249");
	string i;
	bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("133249", i);
}

TEST(NetflixFixture, netflix_read3) {
	istringstream r("133249 1");
	string i;
	bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("133249", i);
}


//------------
//netflix_print
//------------

TEST(NetflixFixture, netflix_print1) {
  string str = "1:\n1.1\n2.2\n3.3\n4.4\n5.5";
  ostringstream w;
  netflix_print(w, str);
  ASSERT_EQ("1:\n1.1\n2.2\n3.3\n4.4\n5.5\n", w.str());
}

TEST(NetflixFixture, netflix_print2) {
  string str = "1:\n1.1\n2.2\n3.3\n4.4\n5.5";
  ostringstream w;
  netflix_print(w, str);
  ASSERT_EQ("1:\n1.1\n2.2\n3.3\n4.4\n5.5\n", w.str());
}

TEST(NetflixFixture, netflix_print3) {
  string str = "1:\n1.1\n2.2\n3.3\n4.4\n5.5";
  ostringstream w;
  netflix_print(w, str);
  ASSERT_EQ("1:\n1.1\n2.2\n3.3\n4.4\n5.5\n", w.str());
}

//------------------
// read_answer_data
//------------------

TEST(NetflixFixture, read_answer_cache1) {
  ofstream outfile("test.txt");
  outfile << "1 30878 4" << endl;
  unordered_map<int, unordered_map<int, int>> answer_map;
  read_answer_data("test.txt", answer_map);

  EXPECT_EQ(answer_map[1][30878], 4);

  outfile.close();
}

TEST(NetflixFixture, read_answer_cache2) {
  ofstream outfile("test.txt");
  outfile << "10773 2300424 5" << endl;
  outfile << "11987 2621910 5" << endl;
  outfile << "1406 2570707 3" << endl;
  unordered_map<int, unordered_map<int, int>> answer_map;
  read_answer_data("test.txt", answer_map);

  EXPECT_EQ(answer_map[10773][2300424], 5);
  EXPECT_EQ(answer_map[11987][2621910], 5);
  EXPECT_EQ(answer_map[1406][2570707], 3);

  outfile.close();
}

TEST(NetflixFixture, read_answer_cache3) {
  ofstream outfile("test.txt");
  outfile << "5732 1930531 4" << endl;
  outfile << "6153 228846 1" << endl;
  outfile << "6386 2635453 4" << endl;
  outfile << "809 1082038 5" << endl;
  outfile << "9866 2420826 4" << endl;
  unordered_map<int, unordered_map<int, int>> answer_map;
  read_answer_data("test.txt", answer_map);

  EXPECT_EQ(answer_map[5732][1930531], 4);
  EXPECT_EQ(answer_map[6153][228846], 1);
  EXPECT_EQ(answer_map[6386][2635453], 4);
  EXPECT_EQ(answer_map[809][1082038], 5);
  EXPECT_EQ(answer_map[9866][2420826], 4);

  outfile.close();
}


//----------------------
//read_avg_movie_ratings
//----------------------

TEST(NetflixFixture, read_avg_movie1) {
  ofstream outfile("test.txt");
  outfile << "685132 3.36" << endl;
  outfile << "628932 3.45" << endl;
  outfile << "593155 2.91" << endl;
  outfile << "2408184 2.73" << endl;
  outfile << "1017098 3.58" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[685132], 3.36);
  EXPECT_FLOAT_EQ(movie_map[628932], 3.45);
  EXPECT_FLOAT_EQ(movie_map[593155], 2.91);
  EXPECT_FLOAT_EQ(movie_map[2408184], 2.73);
  EXPECT_FLOAT_EQ(movie_map[1017098], 3.58);

  outfile.close();
}

TEST(NetflixFixture, read_avg_movie2) {
  ofstream outfile("test.txt");
  outfile << "1973587 4.30" << endl;
  outfile << "2118740 3.36" << endl;
  outfile << "2424902 3.52" << endl;
  outfile << "454077 3.45" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[1973587], 4.30);
  EXPECT_FLOAT_EQ(movie_map[2118740], 3.36);
  EXPECT_FLOAT_EQ(movie_map[2424902], 3.52);
  EXPECT_FLOAT_EQ(movie_map[454077], 3.45);

  outfile.close();
}

TEST(NetflixFixture, read_avg_movie3) {
  ofstream outfile("test.txt"); 
  outfile << "2543291 3.50" << endl;
  outfile << "1570218 3.82" << endl;
  outfile << "468660 3.30" << endl;
  outfile << "786468 3.79" << endl;
  outfile << "887488 3.65" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[2543291], 3.50);
  EXPECT_FLOAT_EQ(movie_map[1570218], 3.82);
  EXPECT_FLOAT_EQ(movie_map[468660], 3.30);
  EXPECT_FLOAT_EQ(movie_map[786468], 3.79);
  EXPECT_FLOAT_EQ(movie_map[887488], 3.65);

  outfile.close();
}


//-------------------------
//read_avg_customer_ratings
//-------------------------

TEST(NetflixFixture, read_avg_customer1) {
  ofstream outfile("test.txt"); 
  outfile << "15802 4.04" << endl;
  outfile << "152 3.93" << endl;
  outfile << "3890 2.94" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[15802], 4.04);
  EXPECT_FLOAT_EQ(movie_map[152], 3.93);
  EXPECT_FLOAT_EQ(movie_map[3890], 2.94);

  outfile.close();
}

TEST(NetflixFixture, read_avg_customer2) {
  ofstream outfile("test.txt"); 
  outfile << "13136 3.67" << endl;
  outfile << "6758 3.60" << endl;
  outfile << "278 2.14" << endl;
  outfile << "5678 2.68" << endl;
  outfile << "8409 2.88" << endl;
  outfile << "387 3.52" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[13136], 3.67);
  EXPECT_FLOAT_EQ(movie_map[6758], 3.60);
  EXPECT_FLOAT_EQ(movie_map[278], 2.14);
  EXPECT_FLOAT_EQ(movie_map[5678], 2.68);
  EXPECT_FLOAT_EQ(movie_map[8409], 2.88);
  EXPECT_FLOAT_EQ(movie_map[387], 3.52);

  outfile.close();
}

TEST(NetflixFixture, read_avg_customer3) {
  ofstream outfile("test.txt");
  outfile << "11825 4.05" << endl;
  outfile << "11865 3.39" << endl;
  outfile << "11422 2.89" << endl;
  unordered_map<int, float> movie_map;
  read_avg_movie_ratings("test.txt", movie_map);

  EXPECT_FLOAT_EQ(movie_map[11825], 4.05);
  EXPECT_FLOAT_EQ(movie_map[11865], 3.39);
  EXPECT_FLOAT_EQ(movie_map[11422], 2.89);

  outfile.close();
}


//------------
//get_movie_id
//------------

TEST(NetflixFixture, get_movie_id1) {
  string str = "2016";
  ASSERT_EQ(2016, get_movie_id(str));
}

TEST(NetflixFixture, get_movie_id2) {
  string str = "1992";
  ASSERT_EQ(1992, get_movie_id(str));
}

TEST(NetflixFixture, get_movie_id3) {
  string str = "1899";
  ASSERT_EQ(1899, get_movie_id(str));
}