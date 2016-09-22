// --------------------------------
// using TeestCollatz.c++ as platform
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"
#include <iostream> // cout, endl
#include <list>
#include <map>
#include <sstream> // istringtstream, ostringstream
#include <string>  // string

#include "Netflix.h"

using namespace std;

// -----------
// check_exist
// -----------

TEST(NetflixFixture, check_exist_1) {
  string path = "/u/downing/cs/netflix-cs371p/nothing.txt";
  string directory = "nothing.txt";
  ASSERT_EQ(check_exist(path, directory), path);
}

TEST(NetflixFixture, check_exist_2) {
  string path =
      "/u/downing/cs/netflix-cs371p/took-forever-to-do-this-project.txt";
  string directory = "took-forever-to-do-this-project.txt";
  ASSERT_EQ(check_exist(path, directory), path);
}

TEST(NetflixFixture, check_exist_3) {
  string path = "/u/downing/cs/netflix-cs371p/Netflix.c++";
  string directory = "Netflix.c++";
  ASSERT_EQ(check_exist(path, directory), directory);
}

// ----------
// get_answer
// ----------

list<double> answers;
string path_to_actual_rating =
    "/u/downing/cs/netflix-cs371p/cyt276-as63439-actual-ratings.txt";

TEST(NetflixFixture, get_answer_1) {
  string path =
      check_exist(path_to_actual_rating, "cyt276-as63439-actual-ratings.txt");
  list<double> result = get_answer(path);
  answers.push_back(4);
  answers.push_back(4);
  answers.push_back(3);
  list<double>::iterator it1 = result.begin();
  for (list<double>::iterator it2 = answers.begin(); it2 != answers.end();
       ++it2) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
  }
}

TEST(NetflixFixture, get_answer_2) {
  string path =
      check_exist(path_to_actual_rating, "cyt276-as63439-actual-ratings.txt");
  list<double> result = get_answer(path);
  answers.push_back(5);
  answers.push_back(5);
  answers.push_back(4);
  answers.push_back(4);
  answers.push_back(4);
  list<double>::iterator it1 = result.begin();
  for (list<double>::iterator it2 = answers.begin(); it2 != answers.end();
       ++it2) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
  }
}

TEST(NetflixFixture, get_answer_3) {
  string path =
      check_exist(path_to_actual_rating, "cyt276-as63439-actual-ratings.txt");
  list<double> result = get_answer(path);
  list<double> reverse;
  reverse.push_back(2);
  reverse.push_back(5);
  reverse.push_back(4);
  reverse.push_back(3);
  reverse.push_back(3);
  list<double>::reverse_iterator it1 = result.rbegin();
  for (list<double>::iterator it2 = reverse.begin(); it2 != reverse.end();
       ++it2) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
  }
}

// ---------
// get_cache
// ---------
string path_to_avg_movie_rate =
    "/u/downing/cs/netflix-cs371p/sw32327-trc2346-movie-ratings.txt";
string path_to_avg_customer_rate =
    "/u/downing/cs/netflix-cs371p/sw32327-trc2346-customer-ratings.txt";

TEST(NetflixFixture, get_cache_1) {
  string path =
      check_exist(path_to_avg_movie_rate, "sw32327-trc2346-movie-ratings.txt");
  map<int, double> avg_movie = get_cache(path);
  ostringstream avg;
  avg << avg_movie[1];
  ASSERT_EQ(avg.str(), "3.75");
}

TEST(NetflixFixture, get_cache_2) {
  string path =
      check_exist(path_to_avg_movie_rate, "sw32327-trc2346-movie-ratings.txt");
  map<int, double> avg_movie = get_cache(path);
  ostringstream avg;
  avg << avg_movie[1000];
  ASSERT_EQ(avg.str(), "3.28");
}

TEST(NetflixFixture, get_cache_3) {
  string path = check_exist(path_to_avg_customer_rate,
                            "sw32327-trc2346-customer-ratings.txt");
  map<int, double> avg_customer = get_cache(path);
  ostringstream avg;
  avg << avg_customer[6];
  ASSERT_EQ(avg.str(), "3.42");
}

TEST(NetflixFixture, get_cache_4) {
  string path = check_exist(path_to_avg_customer_rate,
                            "sw32327-trc2346-customer-ratings.txt");
  map<int, double> avg_customer = get_cache(path);
  ostringstream avg;
  avg << avg_customer[719];
  ASSERT_EQ(avg.str(), "4.18");
}

// ------------
// netflix_read
// ------------

extern list<int> movie_ids;
extern list<list<int>> customer_ids;
string total = "";

TEST(NetflixFixture, read_1) {
  string input = "2043:\n1417435\n2312054\n10851:\n1417435\n2312054\n462685\n";
  total = input;
  istringstream r(input);
  istringstream k(total);
  netflix_read(r);
  string s;
  list<list<int>>::iterator customer_it = customer_ids.begin();
  for (list<int>::iterator it = movie_ids.begin(); it != movie_ids.end();
       ++it) {
    k >> s;
    ASSERT_EQ(*it, atoi(s.data()));
    list<int> ids = *customer_it;
    for (list<int>::iterator sub = ids.begin(); sub != ids.end(); ++sub) {
      k >> s;
      ASSERT_EQ(*sub, atoi(s.data()));
    }
    ++customer_it;
  }
}

TEST(NetflixFixture, read_2) {
  string input = "1:\n123\n456\n123456\n2:\n2468\n3579\n";
  total += input;
  istringstream r(input);
  istringstream k(total);
  netflix_read(r);
  string s;
  list<list<int>>::iterator customer_it = customer_ids.begin();
  for (list<int>::iterator it = movie_ids.begin(); it != movie_ids.end();
       ++it) {
    k >> s;
    ASSERT_EQ(*it, atoi(s.data()));
    list<int> ids = *customer_it;
    for (list<int>::iterator sub = ids.begin(); sub != ids.end(); ++sub) {
      k >> s;
      ASSERT_EQ(*sub, atoi(s.data()));
    }
    ++customer_it;
  }
}

TEST(NetflixFixture, read_3) {
  string input =
      "150:\n123215324\n87866534\n232446\n32434657\n9999:999999\n1234667\n";
  total += input;
  istringstream r(input);
  istringstream k(total);
  netflix_read(r);
  string s;
  list<list<int>>::iterator customer_it = customer_ids.begin();
  for (list<int>::iterator it = movie_ids.begin(); it != movie_ids.end();
       ++it) {
    k >> s;
    ASSERT_EQ(*it, atoi(s.data()));
    list<int> ids = *customer_it;
    for (list<int>::iterator sub = ids.begin(); sub != ids.end(); ++sub) {
      k >> s;
      ASSERT_EQ(*sub, atoi(s.data()));
    }
    ++customer_it;
  }
}

// ---------
// calc_rmse
// ---------

TEST(NetflixFixture, calc_rmse_1) {
  list<double> prediction;
  list<double> actual;
  prediction.push_back(1.5);
  actual.push_back(2.0);
  double answer = calc_rmse(prediction, actual);
  ostringstream os;
  os << answer;
  ASSERT_EQ(os.str(), "0.5");
}

TEST(NetflixFixture, calc_rmse_2) {
  list<double> prediction;
  list<double> actual;
  prediction.push_back(1.5);
  prediction.push_back(4.2);
  prediction.push_back(3.5);
  actual.push_back(2.0);
  actual.push_back(2.0);
  actual.push_back(2.0);
  double answer = calc_rmse(prediction, actual);
  ostringstream os;
  os << answer;
  ASSERT_EQ(os.str(), "1.56");
}

TEST(NetflixFixture, calc_rmse_3) {
  list<double> prediction;
  list<double> actual;
  prediction.push_back(1.5);
  prediction.push_back(4.2);
  prediction.push_back(3.5);
  actual.push_back(3.0);
  actual.push_back(3.0);
  actual.push_back(3.0);
  double answer = calc_rmse(prediction, actual);
  ostringstream os;
  os << answer;
  ASSERT_EQ(os.str(), "1.14");
}

// reset
// -----

TEST(NetflixFixture, reset_1) {
  reset();
  ASSERT_EQ(movie_ids.size(), 0);
}

TEST(NetflixFixture, reset_2) {
  reset();
  ASSERT_EQ(customer_ids.size(), 0);
}

TEST(NetflixFixture, reset_3) {
  movie_ids.push_back(100);
  movie_ids.push_back(300);
  list<int> l;
  l.push_back(100);
  l.push_back(200);
  customer_ids.push_back(l);
  reset();
  ASSERT_EQ(movie_ids.size(), 0);
  ASSERT_EQ(customer_ids.size(), 0);
}

// --------------
// get_prediction
// --------------

list<double> answer;
map<int, double> avg_movie;
map<int, double> avg_customer;

TEST(NetflixFixture, get_prediction_1) {
  string path =
      check_exist(path_to_actual_rating, "az6257-actual-user-ratings.txt");
  answer = get_answer(path);
  path =
      check_exist(path_to_avg_movie_rate, "sw32327-trc2346-movie-ratings.txt");
  avg_movie = get_cache(path);
  path = check_exist(path_to_avg_customer_rate,
                     "sw32327-trc2346-customer-ratings.txt");
  avg_customer = get_cache(path);

  reset();
  string input = "1:\n30878\n2647871\n1283744\n2488120\n317050\n";
  double pred[] = {3.6, 3.2, 3.5, 4.7, 3.7};
  istringstream r(input);
  netflix_read(r);

  list<double> result = get_prediction(avg_movie, avg_customer);
  list<double> prediction(pred, pred + 5);

  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (int i = 0; i < 5; ++i) {
    ostringstream os1;
    ostringstream os2;
    os1 << *it1;
    os2 << *it2;
    ASSERT_EQ(os1.str(), os2.str());
    ++it1;
    ++it2;
  }
}

TEST(NetflixFixture, get_prediction_2) {
  reset();
  string input = "1000:\n2326571\n977808\n1010534\n1861759\n79755\n98259\n";
  double pred[] = {3.1, 2.8, 2.5, 4.5, 3.7, 3.3};
  istringstream r(input);
  netflix_read(r);

  list<double> result = get_prediction(avg_movie, avg_customer);
  list<double> prediction(pred, pred + 6);

  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (int i = 0; i < 6; ++i) {
    ostringstream os1;
    ostringstream os2;
    os1 << *it1;
    os2 << *it2;
    ASSERT_EQ(os1.str(), os2.str());
    ++it1;
    ++it2;
  }
}

TEST(NetflixFixture, get_prediction_3) {
  reset();
  string input = "10005:\n254775\n1892654\n469365\n793736\n926698\n";
  double pred[] = {3.5, 3.9, 3.1, 2.8, 2.9};
  istringstream r(input);
  netflix_read(r);

  list<double> result = get_prediction(avg_movie, avg_customer);
  list<double> prediction(pred, pred + 5);

  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (int i = 0; i < 5; ++i) {
    ostringstream os1;
    ostringstream os2;
    os1 << *it1;
    os2 << *it2;
    ASSERT_EQ(os1.str(), os2.str());
    ++it1;
    ++it2;
  }
}

// ------------
// netflix_calc
// ------------

TEST(NetflixFixture, netflix_calc_1) {
  reset();
  string input = "1:\n30878\n2647871\n1283744\n2488120\n317050\n";
  string output = "1:\n3.6\n3.2\n3.5\n4.7\n3.7\nRMSE: 0.75\n";
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os);
  ASSERT_EQ(os.str(), output);
}

TEST(NetflixFixture, netflix_calc_2) {
  reset();
  string input = "1000:\n2326571\n977808\n1010534\n1861759\n79755\n98259\n";
  string output = "1000:\n3.1\n2.8\n2.5\n4.5\n3.7\n3.3\nRMSE: 0.90\n";
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os);
  ASSERT_EQ(os.str(), output);
}

TEST(NetflixFixture, netflix_calc_3) {
  reset();
  string input = "10005:\n254775\n1892654\n469365\n793736\n926698\n";
  string output = "10005:\n3.5\n3.9\n3.1\n2.8\n2.9\nRMSE: 1.37\n";
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os);
  ASSERT_EQ(os.str(), output);
}
