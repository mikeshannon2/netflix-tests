// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <fstream>  // ifstream
#include <math.h>   // trunc

#include "gtest/gtest.h"

#include "Netflix.h"

#define NUM_OF_MOVIES 17770
#define NUM_OF_CUSTOMERS 480189

using namespace std;

// ----
// read
// ----

TEST(NetflixFixture, read_1) {
    istringstream r("2034:\n");
    int           movieID;
    int           customerID;
    const bool b = netflix_read(r, movieID, customerID);
    ASSERT_TRUE(b);
    ASSERT_EQ(2034, movieID);}

TEST(NetflixFixture, read_2) {
    istringstream r("10896753\n");
    int           movieID;
    int           customerID;
    const bool b = netflix_read(r, movieID, customerID);
    ASSERT_TRUE(b);
    ASSERT_EQ(10896753, customerID);}

TEST(NetflixFixture, read_3) {
    static istringstream r("23456789,2015-10-10\n");
    int           movieID;
    int           customerID;
    const bool b = netflix_read(r, movieID, customerID);
    ASSERT_TRUE(b);
    ASSERT_EQ(23456789, customerID);}

// -----
// print
// -----
TEST(NetflixFixture, print_1) {
    ostringstream w;
    int movieID = 7777;
    int customerID = -1;
    double rating = 0;
    netflix_print(w, movieID, customerID, rating);
    ASSERT_EQ("7777:\n", w.str());}

TEST(NetflixFixture, print_2) {
    ostringstream w;
    int movieID = -1;
    int customerID = 101010;
    double rating = 3.25;
    netflix_print(w, movieID, customerID, rating);
    ASSERT_EQ("3.2\n", w.str());}

TEST(NetflixFixture, print_3) {
    ostringstream w;
    int movieID = -1;
    int customerID = -1;
    double rating = 0.88;
    netflix_print(w, movieID, customerID, rating);
    ASSERT_EQ("RMSE: 0.88\n", w.str());}

TEST(NetflixFixture, print_4) {
    ostringstream w;
    int movieID = -1;
    int customerID = 500;
    double rating = 1.75;
    netflix_print(w, movieID, customerID, rating);
    ASSERT_EQ("1.7\n", w.str());}

// ---------------------
// netflix_calculateRMSE
// ---------------------
// double netflix_calculateRMSE(double predictedRating, int actualRating) {
TEST(NetflixFixture, calculateRMSE_1) {
    double prediction = 3.68;
    int actual = 3;
    double error = prediction - actual;
    ASSERT_EQ(0.68, trunc(100 * error)/100);}

TEST(NetflixFixture, calculateRMSE_2) {
    double prediction = 4.44;
    int actual = 2;
    double error = prediction - actual;
    ASSERT_EQ(2.44, trunc(100 * error)/100);}

TEST(NetflixFixture, calculateRMSE_3) {
    double prediction = 1.79;
    int actual = 3;
    double error = prediction - actual;
    ASSERT_EQ(-1.21, trunc(100 * error)/100);}

TEST(NetflixFixture, calculateRMSE_4) {
    double prediction = 3.89;
    int actual = 4;
    double error = prediction - actual;
    ASSERT_EQ(-0.1, trunc(100 * error)/100);}


// ------------------
// createAvgMovieRate
// ------------------
TEST(NetflixFixture, createMovie_1) {
    ofstream out("tmp.txt");
    out << "1 3.74\n2 4.91\n3 1.55\n4 3.01";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    vector<double> v = createAvgMovieRate(in);
    in.close();

    std::vector<double> expected(NUM_OF_MOVIES);
    expected[1] = 3.74;
    expected[2] = 4.91;
    expected[3] = 1.55;
    expected[4] = 3.01;

    ASSERT_EQ(expected, v);}

TEST(NetflixFixture, createMovie_2) {
    ofstream out("tmp.txt");
    out << "7007 1.11\n8008 2.22\n9009 3.33\n10010 4.44";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::vector<double> v = createAvgMovieRate(in);
    in.close();

    std::vector<double> expected(NUM_OF_MOVIES);
    expected[7007] = 1.11;
    expected[8008] = 2.22;
    expected[9009] = 3.33;
    expected[10010] = 4.44;

    ASSERT_EQ(expected, v);}

TEST(NetflixFixture, createMovie_3) {
    ofstream out("tmp.txt");
    out << "5298 1.23\n7456 1.99\n575 4.56\n8951 4.22";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::vector<double> v = createAvgMovieRate(in);
    in.close();

    std::vector<double> expected(NUM_OF_MOVIES);
    expected[5298] = 1.23;
    expected[7456] = 1.99;
    expected[575] = 4.56;
    expected[8951] = 4.22;

    ASSERT_EQ(expected, v);}

// ---------------------
// createAvgCustomerRate
// ---------------------
TEST(NetflixFixture, createCustomer_1) {
    ofstream out("tmp.txt");
    out << "755555 3.12";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<int, double> c = createAvgCustomerRate(in);
    in.close();

    std::map<int, double> expected;
    expected[755555] = 3.12;

    ASSERT_EQ(expected, c);}

TEST(NetflixFixture, createCustomer_2) {
    ofstream out("tmp.txt");
    out << "301 3.01\n6552 2.18\n479868 1.89";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<int, double> c = createAvgCustomerRate(in);
    in.close();

    std::map<int, double> expected;
    expected[301] = 3.01;
    expected[6552] = 2.18;
    expected[479868] = 1.89;

    ASSERT_EQ(expected, c);}

TEST(NetflixFixture, createCustomer_3) {
    ofstream out("tmp.txt");
    out << "123456 4.32\n2 3.56\n80029 2.92\n2012 4.01\n177889 3.55";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<int, double> c = createAvgCustomerRate(in);
    in.close();

    std::map<int, double> expected;
    expected[123456] = 4.32;
    expected[2] = 3.56;
    expected[80029] = 2.92;
    expected[2012] = 4.01;
    expected[177889] = 3.55;

    ASSERT_EQ(expected, c);}

// -------------------
// createActualRatings
// -------------------
// std::map<std::pair<int, int>, int> createActualRatings(ifstream& file) {
TEST(NetflixFixture, createActual_1) {
    ofstream out("tmp.txt");
    out << "1:\n100 3\n200 2\n300 3";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<std::pair<int, int>, int> a = createActualRatings(in);
    in.close();

    std::map<std::pair<int, int>, int> expected;
    expected[make_pair(1, 100)] = 3;
    expected[make_pair(1, 200)] = 2;
    expected[make_pair(1, 300)] = 3;

    ASSERT_EQ(expected, a);}

TEST(NetflixFixture, createActual_2) {
    ofstream out("tmp.txt");
    out << "505:\n454545 5\n9989 2\n6666 4\n508 3\n7777:\n101 5\n30303 3";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<std::pair<int, int>, int> a = createActualRatings(in);
    in.close();

    std::map<std::pair<int, int>, int> expected;
    expected[make_pair(505, 454545)] = 5;
    expected[make_pair(505, 9989)] = 2;
    expected[make_pair(505, 6666)] = 4;
    expected[make_pair(505, 508)] = 3;
    expected[make_pair(7777, 101)] = 5;
    expected[make_pair(7777, 30303)] = 3;

    ASSERT_EQ(expected, a);}

TEST(NetflixFixture, createActual_3) {
    ofstream out("tmp.txt");
    out << "5:\n1010 1\n202020 2\n3333 4\n5000:\n10 4\n100 5\n1000 3\n10000:\n3333 2\n777 2\n10 3";
    out.close();
    ifstream in;
    in.open("tmp.txt");
    const std::map<std::pair<int, int>, int> a = createActualRatings(in);
    in.close();

    std::map<std::pair<int, int>, int> expected;
    expected[make_pair(5, 1010)] = 1;
    expected[make_pair(5, 202020)] = 2;
    expected[make_pair(5, 3333)] = 4;
    expected[make_pair(5000, 10)] = 4;
    expected[make_pair(5000, 100)] = 5;
    expected[make_pair(5000, 1000)] = 3;
    expected[make_pair(10000, 3333)] = 2;
    expected[make_pair(10000, 777)] = 2;
    expected[make_pair(10000, 10)] = 3;

    ASSERT_EQ(expected, a);}

// ------------------------
// getOverallCustomerRating
// ------------------------
TEST(NetflixFixture, getOverallCustomerRating_1) {
    double total = 400;
    int count = 100;
    double v = total/count;
    ASSERT_EQ(4, v);}

TEST(NetflixFixture, getOverallCustomerRating_2) {
    double total = 100;
    int count = 100;
    double v = total/count;
    ASSERT_EQ(1, v);}

TEST(NetflixFixture, getOverallCustomerRating_3) {
    double total = 300;
    int count = 100;
    double v = total/count;
    ASSERT_EQ(3, v);}

TEST(NetflixFixture, getOverallCustomerRating_4) {
    double total = 40250;
    int count = 10000;
    double v = total/count;
    ASSERT_EQ(4.025, trunc(1000 * v)/1000);}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("1000:\n977808\n1010534\n1861759\n10013:\n1222878\n843201\n2271154\n");
    ostringstream w;

    ifstream actualRatingsFile;
    ifstream customerAvgFile;
    ifstream movieAvgFile;
    actualRatingsFile.open("/u/downing/cs/netflix-cs371p/cyt276-as63439-ids-and-actual-ratings.txt");
    customerAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt");
    movieAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-movie-avg-rating.txt");

    if(!actualRatingsFile.is_open())
        actualRatingsFile.open("cyt276-as63439-ids-and-actual-ratings.txt");

    if(!customerAvgFile.is_open())
        customerAvgFile.open("jl48629-customer_avg_rating.txt");

    if(!movieAvgFile.is_open())
        movieAvgFile.open("jl48629-movie-avg-rating.txt");

    netflix_solve(r, w, movieAvgFile, customerAvgFile, actualRatingsFile);

    actualRatingsFile.close();
    customerAvgFile.close();
    movieAvgFile.close();
    ASSERT_EQ("1000:\n2.8\n2.6\n4.6\n10013:\n3.1\n3.4\n3.6\nRMSE: 0.39\n", w.str());}

TEST(NetflixFixture, solve_2) {
    istringstream r("10040:\n2417853\n1207062\n2487973\n10036:\n842613\n2557615\n");
    ostringstream w;

    ifstream actualRatingsFile;
    ifstream customerAvgFile;
    ifstream movieAvgFile;
    actualRatingsFile.open("/u/downing/cs/netflix-cs371p/cyt276-as63439-ids-and-actual-ratings.txt");
    customerAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt");
    movieAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-movie-avg-rating.txt");

    if(!actualRatingsFile.is_open())
        actualRatingsFile.open("cyt276-as63439-ids-and-actual-ratings.txt");

    if(!customerAvgFile.is_open())
        customerAvgFile.open("jl48629-customer_avg_rating.txt");

    if(!movieAvgFile.is_open())
        movieAvgFile.open("jl48629-movie-avg-rating.txt");

    netflix_solve(r, w, movieAvgFile, customerAvgFile, actualRatingsFile);
    ASSERT_EQ("10040:\n2.9\n2.8\n3.4\n10036:\n3.4\n3.5\nRMSE: 0.69\n", w.str());}

TEST(NetflixFixture, solve_3) {
    istringstream r("1:\n30878\n2647871\n1283744\n2488120\n10007:\n1204847\n2160216\n248206\n835054\n");
    ostringstream w;

    ifstream actualRatingsFile;
    ifstream customerAvgFile;
    ifstream movieAvgFile;
    actualRatingsFile.open("/u/downing/cs/netflix-cs371p/cyt276-as63439-ids-and-actual-ratings.txt");
    customerAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-customer_avg_rating.txt");
    movieAvgFile.open("/u/downing/cs/netflix-cs371p/jl48629-movie-avg-rating.txt");

    if(!actualRatingsFile.is_open())
        actualRatingsFile.open("cyt276-as63439-ids-and-actual-ratings.txt");

    if(!customerAvgFile.is_open())
        customerAvgFile.open("jl48629-customer_avg_rating.txt");

    if(!movieAvgFile.is_open())
        movieAvgFile.open("jl48629-movie-avg-rating.txt");

    netflix_solve(r, w, movieAvgFile, customerAvgFile, actualRatingsFile);
    ASSERT_EQ("1:\n3.7\n3.3\n3.6\n4.7\n10007:\n2\n2.6\n2.2\n2.2\nRMSE: 1.08\n", w.str());}