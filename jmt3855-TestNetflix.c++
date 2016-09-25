// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;
using namespace boost::archive;

/* 	az5385-probe-lookup */

TruthCache::TruthCache() : truth() {}

uint32_t TruthCache::get_rating(uint32_t customer_id, uint32_t movie_id) {
    return this->truth[movie_id][customer_id];
}

void TruthCache::set_ratings(uint32_t movie_id, std::map<uint32_t, uint32_t> &mr) {
    this->truth.emplace(movie_id, mr);
}

/* 	xz4493-data-cache */

const string DataCache::default_training_path = "/u/downing/cs/netflix/training_set";

DataCache::DataCache() : customers(), movies() {}

template <class Archive>
void DataCache::serialize(Archive &ar, const unsigned int version)
{
    ar & this->customers;
    ar & this->movies;
}

AggregatedRating& DataCache::get_customer(uint32_t customer_id)
{
    return this->customers[customer_id];
}

AggregatedRating& DataCache::get_movie(uint32_t movie_id)
{
    return this->movies[movie_id];
}

void DataCache::set_customer(uint32_t customer_id, float rating_avg, float rating_stdev)
{
    AggregatedRating c = AggregatedRating();
    c.rating_avg = rating_avg;
    c.rating_stdev = rating_stdev;
    this->customers.insert({customer_id, c});
}

void DataCache::set_movie(uint32_t movie_id, float rating_avg, float rating_stdev)
{
    AggregatedRating c = AggregatedRating();
    c.rating_avg = rating_avg;
    c.rating_stdev = rating_stdev;
    this->movies.insert({movie_id, c});
}

template<class Archive>
void AggregatedRating::serialize(Archive &ar, const unsigned int version)
{
    ar & this->rating_avg;
    ar & this->rating_stdev;
}


// -----------
// mocke_cache
// -----------

class DataCacheTest : public ::testing::Test {
protected:
    DataCacheTest() : c() {}

    virtual void SetUp() {
        c.set_customer(30878, 3.63f, 0.83f);   // customer1
        c.set_customer(2647871, 3.23f, 1.06f); // customer2
        c.set_customer(1283744, 3.54f, 1.08f); // customer3
        c.set_customer(1417435, 3.51f, 0.91f); // customer4
        c.set_customer(2312054, 4.46f, 1.10f); // customer5
        c.set_customer(2250944, 3.62f, 0.79f); // customer6
        c.set_customer(44772, 3.22f, 1.08f);   // customer7
        c.set_customer(395311, 2.91f, 0.88f);  // customer8
        c.set_customer(1099917, 3.46f, 0.87f); // customer9
        c.set_movie(1, 3.75f, 0.18f);
        c.set_movie(2043, 3.78f, 0.28f);
        c.set_movie(206, 3.86f, 0.27f);
    }

    DataCache c;
};

TEST_F(DataCacheTest, GetCustomerOne) {
    auto& cust = c.get_customer(30878);
    EXPECT_EQ(3.63f, cust.rating_avg);
    EXPECT_EQ(0.83f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerTwo) {
    auto& cust = c.get_customer(2647871);
    EXPECT_EQ(3.23f, cust.rating_avg);
    EXPECT_EQ(1.06f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerThree) {
    auto& cust = c.get_customer(1283744);
    EXPECT_EQ(3.54f, cust.rating_avg);
    EXPECT_EQ(1.08f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerFour) {
    auto& cust = c.get_customer(1417435);
    EXPECT_EQ(3.51f, cust.rating_avg);
    EXPECT_EQ(0.91f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerFive) {
    auto& cust = c.get_customer(2312054);
    EXPECT_EQ(4.46f, cust.rating_avg);
    EXPECT_EQ(1.10f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerSix) {
    auto& cust = c.get_customer(2250944);
    EXPECT_EQ(3.62f, cust.rating_avg);
    EXPECT_EQ(0.79f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerSeven) {
    auto& cust = c.get_customer(44772);
    EXPECT_EQ(3.22f, cust.rating_avg);
    EXPECT_EQ(1.08f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerEight) {
    auto& cust = c.get_customer(395311);
    EXPECT_EQ(2.91f, cust.rating_avg);
    EXPECT_EQ(0.88f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetCustomerNine) {
    auto& cust = c.get_customer(1099917);
    EXPECT_EQ(3.46f, cust.rating_avg);
    EXPECT_EQ(0.87f, cust.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieOne) {
    auto& movie = c.get_movie(1);
    EXPECT_EQ(3.75f, movie.rating_avg);
    EXPECT_EQ(0.18f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieTwo) {
    auto& movie = c.get_movie(2043);
    EXPECT_EQ(3.78f, movie.rating_avg);
    EXPECT_EQ(0.28f, movie.rating_stdev);
}

TEST_F(DataCacheTest, GetMovieThree) {
    auto& movie = c.get_movie(206);
    EXPECT_EQ(3.86f, movie.rating_avg);
    EXPECT_EQ(0.27f, movie.rating_stdev);
}

class TruthCacheTest : public ::testing::Test {
protected:
    TruthCacheTest() : c() {}

    virtual void SetUp() {
        map<uint32_t, uint32_t> movie1_ratings;
        map<uint32_t, uint32_t> movie2_ratings;
        map<uint32_t, uint32_t> movie3_ratings;

        movie1_ratings[30878] = 4;
        movie1_ratings[2647871] = 4;
        movie1_ratings[1283744] = 3;

        movie2_ratings[1417435] = 3;
        movie2_ratings[2312054] = 1;
        movie2_ratings[2250944] = 4;

        movie3_ratings[44772] = 4;
        movie3_ratings[395311] = 3;
        movie3_ratings[1099917] = 4;

        c.set_ratings(1, movie1_ratings);
        c.set_ratings(2043, movie2_ratings);
        c.set_ratings(206, movie3_ratings);
    }

    TruthCache c;
};

TEST_F(TruthCacheTest, GetMovieRating1) {
    uint32_t rating = c.get_rating(30878, 1);
    ASSERT_EQ(4, rating);
    rating = c.get_rating(2647871, 1);
    ASSERT_EQ(4, rating);
    c.get_rating(1283744, 1);
    ASSERT_EQ(4, rating);
}

TEST_F(TruthCacheTest, GetMovieRating2) {
    uint32_t rating = c.get_rating(1417435, 2043);
    ASSERT_EQ(3, rating);
    rating = c.get_rating(2312054, 2043);
    ASSERT_EQ(1, rating);
    rating = c.get_rating(2250944, 2043);
    ASSERT_EQ(4, rating);
}


TEST_F(TruthCacheTest, GetMovieRating3) {
    uint32_t rating = c.get_rating(44772, 206);
    ASSERT_EQ(4, rating);
    rating = c.get_rating(395311, 206);
    ASSERT_EQ(3, rating);
    rating = c.get_rating(1099917, 206);
    ASSERT_EQ(4, rating);
}

// -----
// solve
// -----

TEST(NetflixFixture, solve_1) {
    istringstream r("1:\n30878\n2647871\n1283744");
    DataCache dc;
    dc.set_customer(30878, 3.63f, 0.83f);   // customer1
    dc.set_customer(2647871, 3.23f, 1.06f); // customer2
    dc.set_customer(1283744, 3.54f, 1.08f); // customer3
    dc.set_movie(1, 3.75f, 0.18f);
    TruthCache tc;
    map<uint32_t, uint32_t> movie1_ratings;
    movie1_ratings[30878] = 4;
    movie1_ratings[2647871] = 4;
    movie1_ratings[1283744] = 3;
    tc.set_ratings(1, movie1_ratings);
    ostringstream w;
    netflix_solve(r, w, tc, dc);
    ASSERT_EQ("1:\n3.6\n3.2\n3.5\nThe RMSE: 0.57\n", w.str());
}

TEST(NetflixFixture, solve_2) {
    istringstream r("2043:\n1417435\n2312054\n2250944");
    ostringstream w;
    DataCache dc;
    dc.set_customer(1417435, 3.51f, 0.91f); // customer4
    dc.set_customer(2312054, 4.46f, 1.10f); // customer5
    dc.set_customer(2250944, 3.62f, 0.79f); // customer6
    dc.set_movie(2043, 3.78f, 0.28f);
    TruthCache tc;
    map<uint32_t, uint32_t> movie2_ratings;
    movie2_ratings[1417435] = 3;
    movie2_ratings[2312054] = 1;
    movie2_ratings[2250944] = 4;
    tc.set_ratings(2043, movie2_ratings);
    netflix_solve(r, w, tc, dc);
    ASSERT_EQ("2043:\n3.5\n4.5\n3.6\nThe RMSE: 2.08\n", w.str());
}

TEST(NetflixFixture, solve_3) {
    istringstream r("206:\n44772\n395311\n1099917");
    ostringstream w;
    DataCache dc;
    dc.set_customer(44772, 3.22f, 1.08f);   // customer7
    dc.set_customer(395311, 2.91f, 0.88f);  // customer8
    dc.set_customer(1099917, 3.46f, 0.87f); // customer9
    dc.set_movie(206, 3.86f, 0.27f);
    TruthCache tc;
    map<uint32_t, uint32_t> movie3_ratings;
    movie3_ratings[44772] = 4;
    movie3_ratings[395311] = 3;
    movie3_ratings[1099917] = 4;
    tc.set_ratings(206, movie3_ratings);
    netflix_solve(r, w, tc, dc);
    ASSERT_EQ("206:\n3.3\n3.0\n3.6\nThe RMSE: 0.42\n", w.str());
}

// ----------
// prediction
// ----------


TEST(NetflixFixture, predict_1) {
    double p = netflix_prediction(3.0, 0, 3.78, 0);
    ASSERT_DOUBLE_EQ(3.08, p);
}

TEST(NetflixFixture, predict_2) {
    double p = netflix_prediction(1.0, 0, 3.78, 0);
    ASSERT_DOUBLE_EQ(1.08, p);
}

TEST(NetflixFixture, predict_3) {
    double p = netflix_prediction(4.0, 0, 3.78, 0);
    ASSERT_DOUBLE_EQ(4.08, p);
}
