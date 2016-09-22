#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

// ----
// read
// ----

TEST(NetflixTests, read_1) {
  istringstream r("Shane\n");
  string line="";
  bool ans=netflix_read(r,line);
  ASSERT_TRUE(ans);
}

TEST(NetflixTests, read_2) {
  istringstream r("102344\n");
  string line="";
  bool ans=netflix_read(r,line);
  ASSERT_TRUE(ans);
}

TEST(NetflixTests, read_3) {
  istringstream r("Movie\n");
  string line="";
  bool ans=netflix_read(r,line);
  ASSERT_TRUE(ans);
}

// -------------
// Print MovieID
// -------------

TEST(NetflixTests,printID1){
  int movieID=7645;
  ostringstream w;
  netflix_print_movieID(w,movieID);
  ASSERT_EQ("7645:\n",w.str());
 
}

TEST(NetflixTests,printID2){
  int movieID=8;
  ostringstream w;
  netflix_print_movieID(w,movieID);
  ASSERT_EQ("8:\n",w.str());

}

TEST(NetflixTests,printID3){
  int movieID=7645123;
  ostringstream w;
  netflix_print_movieID(w,movieID);
  ASSERT_EQ("7645123:\n",w.str());

}

// ---------------------
// Print Customer Rating
// ---------------------

TEST(NetflixTests,printcstmRg1){
  float cstmRtg=3.4;
  ostringstream w;
  netflix_print_cstmRtg(w,cstmRtg);
  ASSERT_EQ("3.40\n",w.str());

}

TEST(NetflixTests,printcstmRg2){
  float cstmRtg=1.43;
  ostringstream w;
  netflix_print_cstmRtg(w,cstmRtg);
  ASSERT_EQ("1.43\n",w.str());

}

TEST(NetflixTests,printcstmRg3){
  float cstmRtg=4.99;
  ostringstream w;
  netflix_print_cstmRtg(w,cstmRtg);
  ASSERT_EQ("4.99\n",w.str());

}

// ----------
// Print RMSE
// ----------

TEST(NetflixTests,printRMSE1){
  double rmse=0.95;
  ostringstream w;
  netflix_print_rmse(w,rmse);
  ASSERT_EQ("RMSE: 0.95\n",w.str());

}

TEST(NetflixTests,printRMSE2){
  double rmse=0.99;
  ostringstream w;
  netflix_print_rmse(w,rmse);
  ASSERT_EQ("RMSE: 0.99\n",w.str());

}

TEST(NetflixTests,printRMSE3){
  double rmse=0.94;
  ostringstream w;
  netflix_print_rmse(w,rmse);
  ASSERT_EQ("RMSE: 0.94\n",w.str());

}

// ---------
// Evaluator
// ---------

TEST(NetflixTests,eval_1){
  int movieID = 15802;
  int cstmID = 1234518;
  map<int,float> moviesAvg;
  moviesAvg[movieID] = 4.04;
  map<int,float> cstmAvg;
  cstmAvg[cstmID] = 3.64;
  double rslt = netflix_eval(movieID, cstmID, moviesAvg, cstmAvg);
  ostringstream strs;
  strs << rslt;
  string str = strs.str();
  ASSERT_EQ("3.96879",str);
}

TEST(NetflixTests,eval_2){
  int movieID = 152;
  int cstmID = 649692;
  map<int,float> moviesAvg;
  moviesAvg[movieID] = 3.94;
  map<int,float> cstmAvg;
  cstmAvg[cstmID] = 3.69;
  double rslt = netflix_eval(movieID, cstmID, moviesAvg, cstmAvg);
  ostringstream strs;
  strs << rslt;
  string str = strs.str();
  ASSERT_EQ("3.92444",str);
}

TEST(NetflixTests,eval_3){
  int movieID = 3890;
  int cstmID = 1102770;
  map<int,float> moviesAvg;
  moviesAvg[movieID] = 2.94;
  map<int,float> cstmAvg;
  cstmAvg[cstmID] = 3.54;
  double rslt = netflix_eval(movieID, cstmID, moviesAvg, cstmAvg);
  ostringstream strs;
  strs << rslt;
  string str = strs.str();
  ASSERT_EQ("2.9044",str);
}

TEST(NetflixTests,eval_4){
  int movieID = 1514;
  int cstmID = 947257;
  map<int,float> moviesAvg;
  moviesAvg[movieID] = 3.15;
  map<int,float> cstmAvg;
  cstmAvg[cstmID] = 2.88;
  double rslt = netflix_eval(movieID, cstmID, moviesAvg, cstmAvg);
  ostringstream strs;
  strs << rslt;
  string str = strs.str();
  ASSERT_EQ("2.50525",str);
}

TEST(NetflixTests,eval_5){
  int movieID = 8842;
  int cstmID = 1245387;
  map<int,float> moviesAvg;
  moviesAvg[movieID] = 3.52;
  map<int,float> cstmAvg;
  cstmAvg[cstmID] = 3.70;
  double rslt = netflix_eval(movieID, cstmID, moviesAvg, cstmAvg);
  ostringstream strs;
  strs << rslt;
  string str = strs.str();
  ASSERT_EQ("3.56077",str);
}

// -----
// solve
// -----

 TEST(NetflixTests, solve) {
   istringstream r("10:\n11");
   ostringstream w;
   int movieID=10;
   int cstmID=11;
   map<int,float> moviesAvg;
   moviesAvg[movieID] = 3.52;
   map<int,float> cstmAvg;
   cstmAvg[cstmID] = 3.70;
   map<long long, int> actual;
   actual[cstmID*movieID]=3;
   netflix_solve(r,w,moviesAvg,cstmAvg,actual);
   ASSERT_EQ("10:\n3.56\nRMSE: 0.56\n", w.str());
}

 TEST(NetflixTests, solve2) {
   istringstream r("13:\n11\n12");
   ostringstream w;
   map<int,float> moviesAvg;
   moviesAvg[13] = 4.51;
   map<int,float> cstmAvg;
   cstmAvg[11] = 1.70;
   cstmAvg[12] = 4.30;
   map<long long, int> actual;
   actual[11*13]=3;
   actual[12*13]=5;
   netflix_solve(r,w,moviesAvg,cstmAvg,actual);
   ASSERT_EQ("13:\n2.66\n4.97\nRMSE: 0.24\n", w.str());
}

TEST(NetflixTests,solve3){
   istringstream r("13:\n11\n12\n27\n46");
   ostringstream w;
   map<int,float> moviesAvg;
   moviesAvg[13] = 3.24;;
   map<int,float> cstmAvg;
   cstmAvg[11] = 2.70;
   cstmAvg[12] = 3.30;
   cstmAvg[27] = 3.42;
   cstmAvg[46] = 2.56;
   map<long long, int> actual;
   actual[11*13]=3;
   actual[12*13]=4;
   actual[27*13]=3;
   actual[46*13]=3;
   netflix_solve(r,w,moviesAvg,cstmAvg,actual);
   ASSERT_EQ("13:\n2.43\n2.96\n3.06\n2.30\nRMSE: 0.69\n", w.str());
}
