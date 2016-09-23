#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;


// PREDICT
TEST(NetflixFixture, predict1) {
    istringstream r("1:\n30878\n2647871\n1283744");
    ostringstream w;
    netflix_predict(r, w);
    ASSERT_EQ("1:\n4\n4\n3\n5\n5\n", w.str());
}


TEST(NetflixFixture, predict2) {
    istringstream r("1000:\n2326571\n977808\n1010534\n1861759\n79755");
    ostringstream w;
    netflix_predict(r, w);
    //ASSERT_EQ("1:\n4\n4\n3\n5\n5\n", w.str());
}

