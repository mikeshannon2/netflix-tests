// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <algorithm>  //equal
#include <vector> //vector
#include <cmath>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

TEST(NetflixFixture, read_1) {
	int i;
	vector<int> j;
	istringstream r("413:\n777\n0\n47884286");
	const bool b = netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 413);
	vector<int> check = {777,0,47884286};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
}

TEST(NetflixFixture, read_2) {
	int i;
	vector<int> j;
	istringstream r("2048:\n300\n405\n20\n30045:\n19923\n12345");
	bool b = netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 2048);
	vector<int> check = {300,405,20};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
	b= netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 30045);
	check = {19923,12345};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
}

TEST(NetflixFixture, read_3) {
	int i;
	vector<int> j;
	istringstream r("413:\n777\n0\n47884286\n2048:\n300\n405\n20\n30045:\n19923"
		"\n12345\n");
	bool b = netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 413);
	vector<int> check = {777,0,47884286};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
	b = netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 2048);
	check = {300,405,20};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
	b = netflix_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(i, 30045);
	check = {19923,12345};
	ASSERT_TRUE(equal(j.begin(), j.end(), check.begin()));
}

TEST(NetflixFixture, print_1) {
	int i = 2048;
	vector<float> j = {0,4.3,5};
	ostringstream r;
	netflix_print(r, i, j);
	ASSERT_EQ("2048:\n0.0\n4.3\n5.0\n", r.str());

}
TEST(NetflixFixture, print_2) {
	int i = 5555;
	vector<float> j = {99,2,-5};
	ostringstream r;
	netflix_print(r, i, j);
	ASSERT_EQ("5555:\n99.0\n2.0\n-5.0\n", r.str());

}
TEST(NetflixFixture, print_3) {
	int i = 413;
	vector<float> j = {5.555,10,1.0};
	ostringstream r;
	netflix_print(r, i, j);
	ASSERT_EQ("413:\n5.6\n10.0\n1.0\n", r.str());

}

TEST(NetflixFixture, error_1)
{
	vector<float> p = {3.7, 3.7, 3.7};
	vector<int> a = {4, 4, 4};
	float res = calc_error(p, a);
	ASSERT_FLOAT_EQ(res, 0.3);
}
TEST(NetflixFixture, error_2)
{
	vector<float> p = {1.5, 2.3, 4.1};
	vector<int> a = {2, 5, 1};
	float res = calc_error(p, a);
	ASSERT_NEAR(res, 2.3909, .001);
}
TEST(NetflixFixture, error_3)
{
	vector<float> p = {3.2, 1.7, 3.9};
	vector<int> a = {3, 2, 3};
	float res = calc_error(p, a);
	ASSERT_NEAR(res, 0.5597, .001);
}

TEST(NetflixFixture, build_caches_1)
{
	build_caches();
	bool roughlyEqual = abs(average.getCustomerData(2198786).getAverageRating()-
		3.83f) < 0.01f;
	ASSERT_TRUE(roughlyEqual);
}

TEST(NetflixFixture, build_caches_2)
{
	ASSERT_EQ(actual.getRating(12017, 472558), 5);
}

TEST(NetflixFixture, build_caches_3)
{
	ASSERT_EQ(actual.getRating(10074, 210601), 4);
}

TEST(NetflixFixture, build_caches_4) //Apparently only includes data in probe
{
	ASSERT_EQ(actual.getRating(413, 77471), 0);
}

TEST(NetflixFixture, build_caches_5)
{
	ASSERT_NEAR(average.getCustomerData(257684).getAverageRating(), 4.11 , .01);
}
TEST(NetflixFixture, build_caches_6)
{
	ASSERT_NEAR(average.getMovieData(1919).getAverageRating(), 3.00, .01);
}

TEST(NetflixFixture, solve_1)
{
	istringstream r("1:\n2647871\n"); //read
	ostringstream w(""); //write
	netflix_solve(r, w);
	ASSERT_EQ("1:\n3.3\nRMSE: 0.72\n", w.str());

}
TEST(NetflixFixture, solve_2)
{
	istringstream r("10:\n1952305\n1531863\n"); //read
	ostringstream w(""); //write
	netflix_solve(r, w);
	ASSERT_EQ("10:\n2.9\n2.6\nRMSE: 1.24\n", w.str());

}
TEST(NetflixFixture, solve_3)
{
	istringstream r("1001:\n1050889\n67976\n1025642\n"); //read
	ostringstream w(""); //write
	netflix_solve(r, w);
	ASSERT_EQ("1001:\n4.3\n3.3\n2.9\nRMSE: 0.43\n", w.str());

}

TEST(NetflixFixture, predict_1)
{
	int i = 1;
	vector<int> j = {2647871}; 
	vector<float> o;
	netflix_predict(i, j, o);
	vector<float> check = {3.3};
	ASSERT_NEAR(o.at(0), check.at(0), .1 );
}
TEST(NetflixFixture, predict_2)
{
	int i = 10;
	vector<int> j = {1952305, 1531863}; 
	vector<float> o;
	netflix_predict(i, j, o);
	vector<float> check = {2.9,2.6};
	for(int k = 0 ; k<2; k++)
		ASSERT_NEAR(o.at(k), check.at(k), .1 );
}
TEST(NetflixFixture, predict_3)
{
	int i = 1001;
	vector<int> j = {1050889, 67976, 1025642}; 
	vector<float> o;
	netflix_predict(i, j, o);
	vector<float> check = {4.3, 3.3, 2.9};
	for(int k = 0; k<3; k++)
		ASSERT_NEAR(o.at(k), check.at(k), .1 );
}
TEST(NetflixFixture, get_avg_m_1){
	float i = avg_rating_m(1);
	ASSERT_NEAR(i, 3.75, .01);
}
TEST(NetflixFixture, get_avg_m_2){
	float i = avg_rating_m(155);
	ASSERT_NEAR(i, 3.6, .01);
}
TEST(NetflixFixture, get_avg_m_3){
	float i = avg_rating_m(6864);
	ASSERT_NEAR(i, 3.11, .01);
}
TEST(NetflixFixture, get_avg_c_1){
	float i = avg_rating_c(247);
	ASSERT_NEAR(i, 4.08, .01);
}
TEST(NetflixFixture, get_avg_c_2){
	float i = avg_rating_c(305);
	ASSERT_NEAR(i, 4.1, .01);
}
TEST(NetflixFixture, get_avg_c_3){
	float i = avg_rating_c(1206);
	ASSERT_NEAR(i, 3.67, .01);
}