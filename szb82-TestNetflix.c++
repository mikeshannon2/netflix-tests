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
#include <map>      // memoization
#include <fstream> // ifstream

#include "gtest/gtest.h"

#include "Netflix.h"
using namespace std;


TEST(NetflixFixture, eval_1) {
	const double answer = netflix_eval(0, 0);
	ASSERT_EQ(answer, -3.7);
}

TEST(NetflixFixture, eval_2) {
	const double answer = netflix_eval(3.7, 3.7);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_3) {
	const double answer = netflix_eval(3.7, -1);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_4) {
	const double answer = netflix_eval(-1, -1);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_5) {
	const double answer = netflix_eval(7, 3.7);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_6) {
	const double answer = netflix_eval(3.7, 7);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_7) {
	const double answer = netflix_eval(7, 7);
	ASSERT_EQ(answer, 3.7);
}

TEST(NetflixFixture, eval_8) {
	const double answer = netflix_eval(5, 5);
	ASSERT_NEAR(answer, 6.7, 1);
}

TEST(NetflixFixture, eval_9) {
	const double answer = netflix_eval(2.2, 1);
	ASSERT_NEAR(answer, 0.5, 1);
}

TEST(NetflixFixture, eval_10) {
	const double answer = netflix_eval(3.2, 1);
	ASSERT_NEAR(answer, 1.5, 1);
}

TEST(NetflixFixture, eval_11) {
	const double answer = netflix_eval(2.2, 2);
	ASSERT_NEAR(answer, 1.5, 1);
}

TEST(NetflixFixture, eval_12) {
	const double answer = netflix_eval(3.2, 2);
	ASSERT_NEAR(answer, 2.5, 1);
}

TEST(NetflixFixture, eval_13) {
	const double answer = netflix_eval(3.2, 3);
	ASSERT_NEAR(answer, 3.5, 1);
}

TEST(NetflixFixture, eval_14) {
	const double answer = netflix_eval(4.2, 3);
	ASSERT_NEAR(answer, 4.5, 1);
}

TEST(NetflixFixture, eval_15) {
	const double answer = netflix_eval(4.2, 4);
	ASSERT_NEAR(answer, 5.5, 1);
}

TEST(NetflixFixture, netflix_read_1) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    checkBool = netflix_read(stream, checkInt, checkBool);
    ASSERT_TRUE(checkBool);
}

TEST(NetflixFixture, netflix_read_2) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    netflix_read(stream, checkInt, checkBool);
    ASSERT_EQ(1, checkInt);
}

TEST(NetflixFixture, netflix_read_3) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    ASSERT_TRUE(netflix_read(stream, checkInt, checkBool));
}

TEST(NetflixFixture, netflix_read_4) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    netflix_read(stream, checkInt, checkBool);
    netflix_read(stream, checkInt, checkBool);
    ASSERT_FALSE(checkBool);
}

TEST(NetflixFixture, netflix_read_5) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    netflix_read(stream, checkInt, checkBool);
    netflix_read(stream, checkInt, checkBool);
    ASSERT_EQ(checkInt, 30878);
}

TEST(NetflixFixture, netflix_read_6) {
    ifstream stream;
    stream.open("RunNetflix.in");
    bool checkBool;
    int checkInt;
    netflix_read(stream, checkInt, checkBool);
    ASSERT_TRUE(netflix_read(stream, checkInt, checkBool));
}

TEST(NetflixFixture, netflix_solve_1) {

	std::filebuf fbl;
  	fbl.open ("temporary.txt",std::ios::out);
    std::ostream iss(&fbl);

    iss << "1:\n30878\n2647871\n1283744\n2488120\n317050\n";
    fbl.close();

	std::filebuf fbs;
  	fbs.open ("temporary.txt",std::ios::in);
    std::istream is(&fbs);

	std::filebuf fbv;
  	fbv.open ("tempOut.txt",std::ios::out);
    std::ostream isb(&fbv);

 	netflix_solve(is, isb);

 	fbs.close();
 	fbv.close();


    ifstream ifs;
    ifs.open("tempOut.txt");
    int holder;
    ifs >> holder;

    ASSERT_EQ(1, holder);
    remove("temporary.txt");
    remove("tempOut.txt");
}
