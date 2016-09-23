// ----------------------------
// Fernando Mendoza and Kshitij Delvadiya
// FEM392       KMD2557
// CS371p Fall 2016
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

  

// -----
// solve
// -----

//Test solve in a small space of movie-user pairs
TEST(NetflixFixture, solve_small) {

  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[3];

  for(int i = 1; i < 4; ++i){
  	for(int j = 1; j < 4; ++j){
  		realSolutions[i][j] = (i+j)%5;
  		userEffects[j] = 0.1;
  	}
  	movieAverage[i-1] = (float)i;
  	
  }

  istringstream r("1:\n2\n3\n3:\n2\n");
  ostringstream w;
  netflixSolve(r, w, realSolutions, userEffects, movieAverage);
  ASSERT_EQ("1:\n1.1\n1.1\n3:\n3.1\nRMSE: 2.68\n", w.str());
}

//Test solve in a large, narrow space.
TEST(NetflixFixture, solve_large) {

  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[1000];

  for(int i = 1; i <= 1000; ++i){
  	for(int j = 1; j < 3; ++j){
  		realSolutions[i][j] = (i+j)%5;
  		userEffects[j] = 0.3;
  	}
  	movieAverage[i-1] = i%5;
  		
  }

  istringstream r("1:\n1\n8:\n1\n2\n19:\n2\n1\n30:\n2\n400:\n578:\n1\n2\n933:\n1\n2\n145:\n1\n366:\n2");
  ostringstream w;
  netflixSolve(r, w, realSolutions, userEffects, movieAverage);
  ASSERT_EQ("1:\n1.3\n8:\n3.3\n3.3\n19:\n4.3\n4.3\n30:\n0.3\n400:\n578:\n3.3\n3.3\n933:\n3.3\n3.3\n145:\n0.3\n366:\n1.3\nRMSE: 2.42\n", w.str());
}

//Test solve's stability with negative inputs
TEST(NetflixFixture, solve_negative) {

  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[3];

  for(int i = -10; i < 10; ++i){
  	for(int j = -10; j < 10; ++j){
  		realSolutions[i][j] = (i+j)%5;
  		userEffects[j] = 2.0;
  	}
  	movieAverage[i-1] = i%5;
  	
  }

  istringstream r("-5:\n2\n3\n-10:\n6\n8:\n4\n1");
  ostringstream w;
  netflixSolve(r, w, realSolutions, userEffects, movieAverage);
  ASSERT_EQ("-5:\n2.0\n2.0\n-10:\n2.0\n8:\n5.0\n5.0\nRMSE: 4.17\n", w.str());
}


// -----
// Evaluate
// -----

//Test Evaluate in a small space of user pairs
TEST(NetflixFixture, Evaluate1) {
  map<int, float> userEffects;
  float movieAverage[10];

  for(int i = 0; i < 10; ++i){
  	for(int j = 0; j < 10; ++j){
  		userEffects[j] = 0.2;
  	}
  	movieAverage[i-1] = 3;
  }

  float f = netflixEvaluate(2, 2, userEffects, movieAverage);
  ostringstream holder;
  holder << f << endl;
  string s(holder.str());
	ASSERT_EQ("3.2\n" ,s);

}

//Test Evaluate in a medium space of user pairs
TEST(NetflixFixture, Evaluate2) {
  map<int, float> userEffects;
  float movieAverage[40];

  for(int i = 0; i < 40; ++i){
  	for(int j = 0; j < 20; ++j){
  		userEffects[j] = 0.1;
  	}
  	movieAverage[i-1] = 2.5;
  }

  float f = netflixEvaluate(15, 25, userEffects, movieAverage);
  ostringstream holder;
  holder << f << endl;
  string s(holder.str());
	ASSERT_EQ("2.6\n" ,s);

}

//Test Evaluate in a large space of user pairs
TEST(NetflixFixture, Evaluate3) {
  map<int, float> userEffects;
  float movieAverage[1000];

  for(int i = 0; i < 1000; ++i){
  	for(int j = 0; j < 30; ++j){
  		userEffects[j] = (i*j)%5 + 0.1;
  	}
  	movieAverage[i-1] = 3;
  	
  }

  float f = netflixEvaluate(549, 20, userEffects, movieAverage);
  ostringstream holder;
  holder << f << endl;
  string s(holder.str());
	ASSERT_EQ("3\n" ,s);

}

// -----
// ParseCaches
// -----

//Test correctness of parsing method
TEST(NetflixFixture, ParseCaches1) {
  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[3];

  istringstream SolutionFile("1 1 1\n1 2 2\n2 1 1\n2 2 2\n");
  istringstream EffectFile("1 1.0\n2 2.0\n3 3.0\n");
  istringstream AverageFile("1 1.0\n2 2.0\n3 3.0\n");

  netflixParseCaches(realSolutions, userEffects, movieAverage, SolutionFile, EffectFile, AverageFile);
  
  for(int i = 1; i < 3; ++i){
  	for(int j = 1; j < 3; ++j){
  		ASSERT_EQ(realSolutions[i][j], j);
  	}
  }

  for(int i = 1; i <= 3; ++i){
  	ASSERT_EQ(movieAverage[i-1], i);

  }

}

//Test replacement of values in cache files.
//If the value is specified more than once, the last value will be in the cache.
TEST(NetflixFixture, ParseCaches2) {
  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[3];

  istringstream SolutionFile("1 1 1\n1 2 2\n2 1 1\n2 2 2\n2 1 2\n1 1 2");
  istringstream EffectFile("1 1.0\n2 2.0\n3 3.0\n3 4.0\n1 2.0\n2 3.0");
  istringstream AverageFile("1 1.0\n2 2.0\n3 3.0\n3 4.0\n1 2.0\n2 3.0");

  netflixParseCaches(realSolutions, userEffects, movieAverage, SolutionFile, EffectFile, AverageFile);
  
  for(int i = 1; i < 3; ++i){
    for(int j = 1; j < 3; ++j){
      ASSERT_EQ(realSolutions[i][j], 2);
    }
  }

  for(int i = 1; i <= 3; ++i){
    ASSERT_EQ(movieAverage[i-1], (i+1));
  }

  for(int i = 1; i <= 3; ++i){
    ASSERT_EQ(userEffects[i], (float)(i+1));
  }

}

//Test illegal user ID / movie ID handling. 
TEST(NetflixFixture, ParseCaches3) {
  map<int, map<int, int>> realSolutions;
  map<int, float> userEffects;
  float movieAverage[3];

  istringstream SolutionFile("1 1 1\n1 2 2\n2 1 1\n2 2 2\n");
  istringstream EffectFile("1 1.0\n2 2.0\n3 3.0\n");
  istringstream AverageFile("1 1.0\n2 2.0\n3 3.0\n20000 5.0");

  netflixParseCaches(realSolutions, userEffects, movieAverage, SolutionFile, EffectFile, AverageFile);
  
  for(int i = 1; i < 3; ++i){
    for(int j = 1; j < 3; ++j){
      ASSERT_EQ(realSolutions[i][j], j);
    }
  }

  for(int i = 1; i <= 3; ++i){
    ASSERT_EQ(movieAverage[i-1], i);
  }

  for(int i = 1; i <= 3; ++i){
    ASSERT_EQ(userEffects.size(), 3);
  }

}

// -----
// Print
// -----

//test movie printing format
TEST(NetflixFixture, Print1) {
	ostringstream o;
	float outputF = 3.0;
	bool movieFlag = true;

	netflixPrint(outputF, movieFlag, o);

	ASSERT_EQ(o.str(), "3:\n");
}

//test movie printing format stability on bad input
TEST(NetflixFixture, Print2) {
	ostringstream o;
	float outputF = -50.0;
	bool movieFlag = true;

	netflixPrint(outputF, movieFlag, o);

	ASSERT_EQ(o.str(), "-50:\n");
}

//test prediction printing format
TEST(NetflixFixture, Print3) {
	ostringstream o;
	float outputF = 1.0;
	bool movieFlag = false;

	netflixPrint(outputF, movieFlag, o);

	ASSERT_EQ(o.str(), "1.0\n");
}