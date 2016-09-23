// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

//PRINT TESTS

TEST(PrintFixture, print1)
{
  ostringstream w;
  netflix_print(w, 2175.24);
  ASSERT_EQ("2175.24\n", w.str());
}

TEST(PrintFixture, print2)
{
  ostringstream w;
  netflix_print(w, 0);
  ASSERT_EQ("0\n", w.str());
}

TEST(PrintFixture, print3)
{
  ostringstream w;
  netflix_print(w, 3.05);
  ASSERT_EQ("3.05\n", w.str());
}

//READ_CACHE TESTS

TEST(ReadCacheFixture, cache1)
{
  istringstream mockCache("1234 3.04\n4321 3.00\n");
  int i;
  double j;
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(1234, i);
  ASSERT_EQ(3.04, j);
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(4321, i);
  ASSERT_EQ(3.00, j);
  ASSERT_TRUE(netflix_read_cache(mockCache, i, j) == false);
}

TEST(ReadCacheFixture, cache2)
{
  istringstream mockCache("9999 4.01\n17770 4.01\n1 1.23\n");
  int i;
  double j;
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(9999, i);
  ASSERT_EQ(4.01, j);
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(17770, i);
  ASSERT_EQ(4.01, j);
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(1, i);
  ASSERT_EQ(1.23, j);
  ASSERT_TRUE(netflix_read_cache(mockCache, i, j) == false);
}

TEST(ReadCacheFixture, cache3)
{
  istringstream mockCache("1 0.14\n2 0.99\n");
  int i;
  double j;
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(1, i);
  ASSERT_EQ(0.14, j);
  netflix_read_cache(mockCache, i, j);
  ASSERT_EQ(2, i);
  ASSERT_EQ(0.99, j);
  ASSERT_TRUE(netflix_read_cache(mockCache, i, j) == false);
}

//READ_INPUT TESTS

TEST(ReadInputFixture, input1)
{
  istringstream input("1:\n1\n");
  string movie;
  netflix_read(input, movie);
  ASSERT_EQ("1:", movie);
  netflix_read(input, movie);
  ASSERT_EQ("1", movie);
  ASSERT_TRUE(netflix_read(input, movie) == false);
}

TEST(ReadInputFixture, input2)
{
  istringstream input("1568256:\n3535\n");
  string movie;
  netflix_read(input, movie);
  ASSERT_EQ("1568256:", movie);
  netflix_read(input, movie);
  ASSERT_EQ("3535", movie);
  ASSERT_TRUE(netflix_read(input, movie) == false);
}

TEST(ReadInputFixture, input3)
{
  istringstream input("\n");
  string movie;
  ASSERT_TRUE(netflix_read(input, movie) == false);
}

//SOLVE TESTS

TEST(SolveFixture, solve1)
{
  istringstream movieCache("8 3.19\n5561 4.14\n5427 2.88\n15158 2.91\n9160 3.54\n13352 3.01\n5030 2.27\n4800 2.79\n12003 3.64\n8012 3.07\n11412 3.13\n");
  istringstream customerCache("8 3.31\n2042147 4.32\n1576831 3.86\n477798 3.20\n1055551 4.08\n1751276 3.91\n2377886 3.67\n2345472 3.98\n626934 3.45\n858516 4.08\n598465 3.77\n546449 3.13\n");
  istringstream actualCache("8:\n3\n3\n3\n3\n3\n5561:\n4\n5\n5\n5\n11412:\n3\n5\n1\n3\n1\n2\n4\n3\n3\n3\n2\n4\n1\n12003:\n4\n4\n5\n2\n4\n4\n3\n");
  istringstream mockProbe("8:\n8\n8\n8\n8\n8\n10006:\n8\n8\n8\n8\n11412:\n8\n8\n8\n8\n8\n8\n8\n8\n8\n8\n8\n8\n8\n12003:\n8\n8\n8\n8\n8\n8\n8\n");
  ostringstream w;
  netflix_solve(mockProbe, w, movieCache, customerCache, actualCache);
  ASSERT_EQ("8:\n3.2\n3.2\n3.2\n3.2\n3.2\n10006:\n1.6\n1.6\n1.6\n1.6\n11412:\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n3.2\n12003:\n3.4\n3.4\n3.4\n3.4\n3.4\n3.4\n3.4\nRMSE: 1.54\n", w.str());
}

TEST(SolveFixture, solve2)
{
  istringstream movieCache("8 3.19\n5561 4.14\n");
  istringstream customerCache("1 3.31\n2042147 4.32\n8 3.31\n34 3.31\n");
  istringstream actualCache("8:\n3\n3\n3\n3\n5561:\n4\n3\n2\n3\n");
  istringstream mockProbe("8:\n1\n2042147\n8\n34\n5561:\n1\n2042147\n8\n34\n");
  ostringstream w;
  netflix_solve(mockProbe, w, movieCache, customerCache, actualCache);
  ASSERT_EQ("8:\n3.2\n3.7\n3.2\n3.2\n5561:\n3.7\n4.2\n3.7\n3.7\nRMSE: 0.83\n", w.str());
}

TEST(SolveFixture, solve3)
{
  istringstream movieCache("\n");
  istringstream customerCache("\n");
  istringstream actualCache("\n");
  istringstream mockProbe("\n");
  ostringstream w;
  netflix_solve(mockProbe, w, movieCache, customerCache, actualCache);
  ASSERT_EQ("RMSE: -nan\n", w.str());
}
