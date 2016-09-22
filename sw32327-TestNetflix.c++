#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;



// -----------------
// netflix_binsearch
// -----------------

TEST(NetflixFixture, binsearch_1) {
	ifstream stream;
	stream.open(MOVIECACHE, ifstream::in);
	printf(MOVIECACHE);
  	ASSERT_EQ(netflix_binsearch(stream, MOVIELINE, 6000, 0, MOVIESIZE), 3.26);
}

TEST(NetflixFixture, binsearch_2) {
	ifstream stream;
	stream.open(MOVIECACHE, ifstream::in);
  	ASSERT_EQ(netflix_binsearch(stream, MOVIELINE, 1, 0, MOVIESIZE), 3.75);
}

TEST(NetflixFixture, binsearch_3) {
	ifstream stream;
	stream.open(USERCACHE, ifstream::in);
  	ASSERT_EQ(netflix_binsearch(stream, USERLINE, 6, 0, USERSIZE), 3.42);
}

TEST(NetflixFixture, binsearch_4) {
	ifstream stream;
	stream.open(USERCACHE, ifstream::in);
  	ASSERT_EQ(netflix_binsearch(stream, USERLINE, 2649429, 0, USERSIZE), 4.18);
}

TEST(NetflixFixture, binsearch_5) {
	ifstream stream;
	stream.open(USERCACHE, ifstream::in);
  	ASSERT_EQ(netflix_binsearch(stream, USERLINE, 536429, 0, USERSIZE), 3.58);
}

// ------------
// netflix_eval
// ------------

TEST(NetflixFixture, eval_1)
{
	ifstream ucache;
	ucache.open(USERCACHE, ifstream::in);
	ifstream mcache;
	mcache.open(MOVIECACHE, ifstream::in);
	double rating = netflix_eval(1, 30878, mcache, ucache);
	rating = abs((double)(rating - 4.0));
	ASSERT_TRUE(rating < 1);
}

TEST(NetflixFixture, eval_2)
{
	ifstream ucache;
	ucache.open(USERCACHE, ifstream::in);
	ifstream mcache;
	mcache.open(MOVIECACHE, ifstream::in);
	double rating = netflix_eval(1000, 977808, mcache, ucache);
	rating = abs((double)(rating - 3.0));
	ASSERT_TRUE(rating < 1);
}

TEST(NetflixFixture, eval_3)
{
	ifstream ucache;
	ucache.open(USERCACHE, ifstream::in);
	ifstream mcache;
	mcache.open(MOVIECACHE, ifstream::in);
	double rating = netflix_eval(1000, 977808, mcache, ucache);
	ostringstream stream;
	stream << rating;
	ASSERT_EQ(stream.str().length(), 3); 
}

// -------------
// netflix_error
// -------------


TEST(NetflixFixture, error_1)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	#ifdef OPT_Map
	netflix_hash(actual, 2135, 2152);
	#endif
	ostringstream stream;
	stream << netflix_error(2147047, 2.0, actual, 2135, 2152);
	ASSERT_EQ(stream.str(), "9");
}

TEST(NetflixFixture, error_2)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	#ifdef OPT_Map
	netflix_hash(actual, 0, 23);
	#endif
	ostringstream stream;
	stream << netflix_error(1149588, 3.7, actual, 0, 23);
	ASSERT_EQ(stream.str(), "0.09");
}


TEST(NetflixFixture, error_3)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	#ifdef OPT_Map
	netflix_hash(actual, 815712,815733);
	#endif
	ostringstream stream;
	stream << netflix_error(1572159, 1.1, actual, 815712, 815733);
	ASSERT_EQ(stream.str(), "15.21");
}


// ------------
// netflix_hash
// ------------

#ifdef OPT_Map
TEST(NetflixFixture, hash_1)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	// there is only one customer for movie 9999
	netflix_hash(actual, 971778,971779);
	// if netflix_error returns 0, this mean the hash value is exactly correct
	ASSERT_EQ(netflix_error(1473765, 2.0, actual, 971778, 971779), 0);
}

TEST(NetflixFixture, hash_2)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	netflix_hash(actual, 1408387, 1408395);
	// if netflix_error returns 0, this mean the hash value is exactly correct
	ASSERT_EQ(netflix_error(1476398, 2.0, actual, 1408387, 1408395), 0);
}

TEST(NetflixFixture, hash_3)
{
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	netflix_hash(actual, 0, 23);
	// if netflix_error returns 0, this mean the hash value is exactly correct
	ASSERT_EQ(netflix_error(548064, 5.0, actual, 0, 23), 0);
}
#endif

// ------------
// netflix_read
// ------------

TEST(NetflixFixture, read_1)
{
	istringstream input("1:\n30878\n2647871\n1283744\n");
	int movie, customer, start, end;
	ifstream meta;
	meta.open(METACACHE, ifstream::in);
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	netflix_read(input, movie, customer, meta, actual, start, end);
	ASSERT_EQ(movie, 1);
	ASSERT_EQ(customer, 30878);
	ASSERT_EQ(start, 0);
	ASSERT_EQ(end, 23);
}

TEST(NetflixFixture, read_2)
{
	istringstream input("75414\n2647871\n1283744\n");
	int movie, customer, start, end;
	ifstream meta;
	meta.open(METACACHE, ifstream::in);
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	// if there isn't a new movie, these variables should not change
	movie = 5;
	start = 65;
	end = 129;
	netflix_read(input, movie, customer, meta, actual, start, end);
	ASSERT_EQ(movie, 5);
	ASSERT_EQ(customer, 75414);
	ASSERT_EQ(start, 65);
	ASSERT_EQ(end, 129);
}

TEST(NetflixFixture, read_3)
{
	istringstream input("10:\n1952305\n1531863\n");
	int movie, customer, start, end;
	ifstream meta;
	meta.open(METACACHE, ifstream::in);
	ifstream actual;
	actual.open(ACTUALCACHE, ifstream::in);
	// if a new movie is encountered, it should overwrite the previous movie
	movie = 5;
	start = 65;
	end = 129;
	netflix_read(input, movie, customer, meta, actual, start, end);
	ASSERT_EQ(movie, 10);
	ASSERT_EQ(customer, 1952305);
	ASSERT_EQ(start, 1127);
	ASSERT_EQ(end, 1129);
}

// -------------
// netflix_print
// -------------

TEST(NetflixFixture, print_1)
{
	ostringstream out;
	int movie = 22;
	netflix_print(out, movie, movie, 2.2);
	ASSERT_EQ("2.2\n", out.str());
}

TEST(NetflixFixture, print_2)
{
	ostringstream out;
	int movie = 3541;
	int last = 22;
	netflix_print(out, movie, last, 4.1);
	ASSERT_EQ("3541:\n4.1\n", out.str());
}

TEST(NetflixFixture, print_3)
{
	ostringstream out;
	int movie = 3541;
	int last = 22;
	netflix_print(out, last, movie, 4.1);
	ASSERT_EQ("22:\n4.1\n", out.str());
}

// -------------
// netflix_solve
// -------------


TEST(NetflixFixture, solve_1)
{
	
	ostringstream out;
	istringstream in("10:\n1952305\n1531863\n1000:\n2326571\n977808\n1010534\n1861759\n79755\n98259\n1960212\n97460\n2623506\n2409123\n1959111\n809597\n2251189\n537705\n929584\n506737\n708895\n1900790\n2553920\n");
	netflix_solve(in, out);
	// get the RMSE
	istringstream output(out.str());
	string rmse;
	while(output.good())
		output >> rmse;
	// check if value begins with a zero (meaning it is less than 1)
	ASSERT_EQ(rmse[0], '0');
}