// TestNetflix.c++

// --------
// includes
// --------

#include <iostream> //cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // string
#include <map>      // map

#include "gtest/gtest.h"

#include "Netflix.h"
#include "Equal.h"

using namespace std;

// write the tests!!!

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
	istringstream r("2043:\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("2043:", i);
}

TEST(NetflixFixture, read_2) {
	istringstream r("985849\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("985849", i);
}

TEST(NetflixFixture, read_3) {
	istringstream r("42\n");
	string           i;
	const bool b = netflix_read(r, i);
	ASSERT_TRUE(b);
	ASSERT_EQ("42", i);
}

// -------
// predict
// -------

#ifdef OFFSETS
TEST(NetflixFixture, oPredict_1) {
	string i = "10:";
	string j = "1952305";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 3.54));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 3.87));
	double rSum = 0;
	// double avg = 3.7;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 3.7);
}

TEST(NetflixFixture, oPredict_2) {
	string i = "6197:";
	string j = "1756789";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 2.96));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 3.42));
	double rSum = 0;
	// double avg = 3.7;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 2.6);
}

TEST(NetflixFixture, oPredict_3) {
	string i = "4060:";
	string j = "827168";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 3.71));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 4.50));
	double rSum = 0;
	// double avg = 3.7;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 4.5);
}
#elif defined COMPARE_MOVIES  // cPredict_1
// make vectors
// double p = netflix_predict(i, j, map1, map2, rSum, avg, mNum, cRatings);
#else
TEST(NetflixFixture, oPredict_1) {
	string i = "10:";
	string j = "1952305";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 3.54));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 3.87));
	double rSum = 0;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 3.7);
}

TEST(NetflixFixture, oPredict_2) {
	string i = "6197:";
	string j = "1756789";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 2.96));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 3.42));
	double rSum = 0;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 3.7);
}

TEST(NetflixFixture, oPredict_3) {
	string i = "4060:";
	string j = "827168";
	map<string, double> map1;
	map1.insert(pair<string, double> (i, 3.71));
	map<string, double> map2;
	map2.insert(pair<string, double> (j, 4.50));
	double rSum = 0;
	double p = netflix_predict(i, j, map1, map2, rSum); //, avg);
	ASSERT_EQ(p, 3.7);
}
#endif

// -----
// print
// -----

TEST(NetflixFixture, print_1) {
	ostringstream w;
	string i = "1264";
	netflix_print(w, i);
	ASSERT_EQ("1264\n", w.str());
}

TEST(NetflixFixture, print_2) {
	ostringstream w;
	string i = "94857";
	netflix_print(w, i);
	ASSERT_EQ("94857\n", w.str());
}

TEST(NetflixFixture, print_3) {
	ostringstream w;
	string i = "2156:";
	netflix_print(w, i);
	ASSERT_EQ("2156:\n", w.str());
}

// ----
// RMSE
// ----

TEST(NetflixFixture, RMSE_1) {
	vector<double> v1 = {3.2, 2.5, 1.4};
	vector<double> v2 = {2.4, 3.8, 4.9};
	string r = RMSE(v1, v2);
	ASSERT_EQ(r, "2.20");
}

TEST(NetflixFixture, RMSE_2) {
	vector<double> v1 = {4.3, 1.8, 3.5};
	vector<double> v2 = {2.5, 3.2, 4.0};
	string r = RMSE(v1, v2);
	ASSERT_EQ(r, "1.34");
}

TEST(NetflixFixture, RMSE_3) {
	vector<double> v1 = {5.0, 5.0, 5.0};
	vector<double> v2 = {2.0, 2.0, 2.0};
	string r = RMSE(v1, v2);
	ASSERT_EQ(r, "3.00");
}

// ----
//solve
// ----

#ifdef OFFSETS
TEST(NetflixFixture, solve_1) {
	istringstream r("2043:\n1417435\n2312054\n1000:\n977808\n1010534\n1861759\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("2043", 3.78));
    mID.insert(pair<string, double> ("1000", 3.28));
    map<string, double> cID;
    cID.insert(pair<string, double> ("1417435", 3.51));
    cID.insert(pair<string, double> ("2312054", 4.46));
    cID.insert(pair<string, double> ("977808", 3.29));
    cID.insert(pair<string, double> ("1010534", 3.00));
    cID.insert(pair<string, double> ("1861759", 5.00));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("2043:1417435", 3));
    actRating.insert(pair<string, double> ("2043:2312054", 1));
    actRating.insert(pair<string, double> ("1000:977808", 3));
    actRating.insert(pair<string, double> ("1000:1010534", 2));
    actRating.insert(pair<string, double> ("1000:1861759", 5));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("2043:\n3.5\n4.5\n1000:\n2.8\n2.5\n4.5\nRMSE: 1.61\n", w.str());
}

TEST(NetflixFixture, solve_2) {
	istringstream r("2191:\n360520\n318142\n2236399\n6114:\n1912995\n2402110\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("2191", 3.63));
    mID.insert(pair<string, double> ("6114", 3.22));
    map<string, double> cID;
    cID.insert(pair<string, double> ("360520", 3.61));
    cID.insert(pair<string, double> ("318142", 4.44));
    cID.insert(pair<string, double> ("2236399", 3.08));
    cID.insert(pair<string, double> ("1912995", 3.68));
    cID.insert(pair<string, double> ("2402110", 4.34));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("2191:360520", 4));
    actRating.insert(pair<string, double> ("2191:318142", 5));
    actRating.insert(pair<string, double> ("6114:2236399", 3));
    actRating.insert(pair<string, double> ("6114:1912995", 2));
    actRating.insert(pair<string, double> ("6114:2402110", 1));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("2191:\n3.5\n4.3\n3.0\n6114:\n3.2\n3.8\nRMSE: 1.94\n", w.str());
}

TEST(NetflixFixture, solve_3) {
	istringstream r("6197:\n2332407\n1756789\n6199:\n2581095\n1655656\n62:\n1560144\n1431710\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("6197", 2.96));
    mID.insert(pair<string, double> ("6199", 3.62));
    mID.insert(pair<string, double> ("62", 3.62));
    map<string, double> cID;
    cID.insert(pair<string, double> ("2332407", 2.92));
    cID.insert(pair<string, double> ("1756789", 3.42));
    cID.insert(pair<string, double> ("2581095", 4.10));
    cID.insert(pair<string, double> ("1655656", 2.57));
    cID.insert(pair<string, double> ("1560144", 3.94));
    cID.insert(pair<string, double> ("1431710", 3.51));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("6197:2332407", 3));
    actRating.insert(pair<string, double> ("6197:1756789", 4));
    actRating.insert(pair<string, double> ("6199:2581095", 5));
    actRating.insert(pair<string, double> ("6199:1655656", 3));
    actRating.insert(pair<string, double> ("62:1560144", 4));
    actRating.insert(pair<string, double> ("62:1431710", 3));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("6197:\n2.1\n2.6\n6199:\n4.0\n2.4\n62:\n3.8\n3.4\nRMSE: 0.84\n", w.str());
}
#else
TEST(NetflixFixture, solve_1) {
	istringstream r("2043:\n1417435\n2312054\n1000:\n977808\n1010534\n1861759\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("2043", 3.78));
    mID.insert(pair<string, double> ("1000", 3.28));
    map<string, double> cID;
    cID.insert(pair<string, double> ("1417435", 3.51));
    cID.insert(pair<string, double> ("2312054", 4.46));
    cID.insert(pair<string, double> ("977808", 3.29));
    cID.insert(pair<string, double> ("1010534", 3.00));
    cID.insert(pair<string, double> ("1861759", 5.00));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("2043:1417435", 3));
    actRating.insert(pair<string, double> ("2043:2312054", 1));
    actRating.insert(pair<string, double> ("1000:977808", 3));
    actRating.insert(pair<string, double> ("1000:1010534", 2));
    actRating.insert(pair<string, double> ("1000:1861759", 5));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("2043:\n3.7\n3.7\n1000:\n3.7\n3.7\n3.7\nRMSE: 1.60\n", w.str());
}

TEST(NetflixFixture, solve_2) {
	istringstream r("2191:\n360520\n318142\n2236399\n6114:\n1912995\n2402110\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("2191", 3.63));
    mID.insert(pair<string, double> ("6114", 3.22));
    map<string, double> cID;
    cID.insert(pair<string, double> ("360520", 3.61));
    cID.insert(pair<string, double> ("318142", 4.44));
    cID.insert(pair<string, double> ("2236399", 3.08));
    cID.insert(pair<string, double> ("1912995", 3.68));
    cID.insert(pair<string, double> ("2402110", 4.34));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("2191:360520", 4));
    actRating.insert(pair<string, double> ("2191:318142", 5));
    actRating.insert(pair<string, double> ("6114:2236399", 3));
    actRating.insert(pair<string, double> ("6114:1912995", 2));
    actRating.insert(pair<string, double> ("6114:2402110", 1));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("2191:\n3.7\n3.7\n3.7\n6114:\n3.7\n3.7\nRMSE: 2.26\n", w.str());
}

TEST(NetflixFixture, solve_3) {
	istringstream r("6197:\n2332407\n1756789\n6199:\n2581095\n1655656\n62:\n1560144\n1431710\n");
    ostringstream w;
    map<string, double> mID;
    mID.insert(pair<string, double> ("6197", 2.96));
    mID.insert(pair<string, double> ("6199", 3.62));
    mID.insert(pair<string, double> ("62", 3.62));
    map<string, double> cID;
    cID.insert(pair<string, double> ("2332407", 2.92));
    cID.insert(pair<string, double> ("1756789", 3.42));
    cID.insert(pair<string, double> ("2581095", 4.10));
    cID.insert(pair<string, double> ("1655656", 2.57));
    cID.insert(pair<string, double> ("1560144", 3.94));
    cID.insert(pair<string, double> ("1431710", 3.51));
    map<string, double> actRating;
    actRating.insert(pair<string, double> ("6197:2332407", 3));
    actRating.insert(pair<string, double> ("6197:1756789", 4));
    actRating.insert(pair<string, double> ("6199:2581095", 5));
    actRating.insert(pair<string, double> ("6199:1655656", 3));
    actRating.insert(pair<string, double> ("62:1560144", 4));
    actRating.insert(pair<string, double> ("62:1431710", 3));
    netflix_solve(r, w, mID, cID, actRating);
    ASSERT_EQ("6197:\n3.7\n3.7\n6199:\n3.7\n3.7\n62:\n3.7\n3.7\nRMSE: 0.74\n", w.str());
}
#endif // OFFSETS

// ---------
// fileToMap
// ---------

TEST(NetflixFixture, fileToMap_1) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "1174466 3.16\n1543642 3.85\n";
	myFile.close();

	map<string, double> m = fileToMap(fileName);
	double n = m.find("1174466")->second;
	ASSERT_EQ(n, 3.16);
	n = m.find("1543642")->second;
	ASSERT_EQ(n, 3.85);
}

TEST(NetflixFixture, fileToMap_2) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "3214601 3.46\n5439185 1.04\n";
	myFile.close();

	map<string, double> m = fileToMap(fileName);
	double n = m.find("3214601")->second;
	ASSERT_EQ(n, 3.46);
	n = m.find("5439185")->second;
	ASSERT_EQ(n, 1.04);
}

TEST(NetflixFixture, fileToMap_3) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "8156904 2.35\n3954244 4.21\n";
	myFile.close();

	map<string, double> m = fileToMap(fileName);
	double n = m.find("8156904")->second;
	ASSERT_EQ(n, 2.35);
	n = m.find("3954244")->second;
	ASSERT_EQ(n, 4.21);
}

// -------
// arCache
// -------

TEST(NetflixFixture, arCache_1) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "356:\n298497 2\n2604891 5\n";
	myFile.close();

	map<string, double> m = arCache(fileName);
	double n = m.find("356:298497")->second;
	ASSERT_EQ(n, 2);
	n = m.find("356:2604891")->second;
	ASSERT_EQ(n, 5);
} 

TEST(NetflixFixture, arCache_2) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "1:\n30878 4\n1283744 3\n";
	myFile.close();

	map<string, double> m = arCache(fileName);
	double n = m.find("1:30878")->second;
	ASSERT_EQ(n, 4);
	n = m.find("1:1283744")->second;
	ASSERT_EQ(n, 3);
} 

TEST(NetflixFixture, arCache_3) {
	string fileName = "test1.txt";
	ofstream myFile;
	myFile.open(fileName);
	myFile << "469:\n16158 2\n2849918 1\n2978:\n746894 4\n5946317 3\n";
	myFile.close();

	map<string, double> m = arCache(fileName);
	double n = m.find("469:16158")->second;
	ASSERT_EQ(n, 2);
	n = m.find("469:2849918")->second;
	ASSERT_EQ(n, 1);
	n = m.find("2978:746894")->second;
	ASSERT_EQ(n, 4);
	n = m.find("2978:5946317")->second;
	ASSERT_EQ(n, 3);
} 
