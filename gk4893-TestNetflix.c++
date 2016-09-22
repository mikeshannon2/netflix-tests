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
#include <stdio.h>
#include <string> // string

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

TEST(NetflixFixture, get_answer_1) {
  ofstream ofs("temporary_cache_to_answer.txt");
  ofs << "1:\n4\n4\n3\n";
  ofs.close();
  list<double> result = get_answer("temporary_cache_to_answer.txt");
  answers.push_back(4);
  answers.push_back(4);
  answers.push_back(3);
  list<double>::iterator it1 = result.begin();
  for (list<double>::iterator it2 = answers.begin(); it2 != answers.end();
       ++it2) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
  }
  remove("temporary_cache_to_answer.txt");
}

TEST(NetflixFixture, get_answer_2) {
  ofstream ofs("temporary_cache_to_answer.txt");
  ofs << "1:\n4\n4\n3\n5\n5\n4\n4\n4\n";
  ofs.close();
  list<double> result = get_answer("temporary_cache_to_answer.txt");
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
  remove("temporary_cache_to_answer.txt");
}

TEST(NetflixFixture, get_answer_3) {
  ofstream ofs("temporary_cache_to_answer.txt");
  ofs << "1:\n4\n4\n3\n5\n5\n4\n4\n4\n2\n5\n4\n3\n3\n";
  ofs.close();
  list<double> result = get_answer("temporary_cache_to_answer.txt");
  answers.push_back(2);
  answers.push_back(5);
  answers.push_back(4);
  answers.push_back(3);
  answers.push_back(3);
  list<double>::iterator it1 = result.begin();
  for (list<double>::iterator it2 = answers.begin(); it2 != answers.end();
       ++it2) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
  }
  remove("temporary_cache_to_answer.txt");
}

// ---------
// get_cache
// ---------
TEST(NetflixFixture, get_cache_1) {
  ofstream ofs("temporary_movie_rate.txt");
  ofs << "00001 3.75\n01000 3.28\n";
  ofs.close();
  map<int, double> avg_movie = get_cache("temporary_movie_rate.txt");
  ostringstream avg;
  avg << avg_movie[1];
  ASSERT_EQ(avg.str(), "3.75");
  remove("temporary_movie_rate.txt");
}

TEST(NetflixFixture, get_cache_2) {
  ofstream ofs("temporary_movie_rate.txt");
  ofs << "00001 3.75\n01000 3.28\n";
  ofs.close();
  map<int, double> avg_movie = get_cache("temporary_movie_rate.txt");
  ostringstream avg;
  avg << avg_movie[1000];
  ASSERT_EQ(avg.str(), "3.28");
  remove("temporary_movie_rate.txt");
}

TEST(NetflixFixture, get_cache_3) {
  ofstream ofs("temporary_customer_rate.txt");
  ofs << "0000006 3.42\n0000719 4.18\n";
  ofs.close();
  map<int, double> avg_customer = get_cache("temporary_customer_rate.txt");
  ostringstream avg;
  avg << avg_customer[6];
  ASSERT_EQ(avg.str(), "3.42");
  remove("temporary_customer_rate.txt");
}

TEST(NetflixFixture, get_cache_4) {
  ofstream ofs("temporary_customer_rate.txt");
  ofs << "0000006 3.42\n0000719 4.18\n";
  ofs.close();
  map<int, double> avg_customer = get_cache("temporary_customer_rate.txt");
  ostringstream avg;
  avg << avg_customer[719];
  ASSERT_EQ(avg.str(), "4.18");
  remove("temporary_customer_rate.txt");
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

// -----
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

map<int, double> avg_movie_rate1;
map<int, double> avg_movie_rate2;
map<int, double> avg_movie_rate3;
map<int, double> avg_customer_rate1;
map<int, double> avg_customer_rate2;
map<int, double> avg_customer_rate3;

TEST(NetflixFixture, get_prediction_1) {
  reset();
  string input = "1:\n30878\n2647871\n1283744\n2488120\n";
  istringstream is(input);
  netflix_read(is);
  list<double> prediction;
  list<int>::iterator movie_it = movie_ids.begin();
  for (list<list<int>>::iterator customer_it = customer_ids.begin();
       customer_it != customer_ids.end(); ++customer_it) {
    avg_movie_rate1[*movie_it] = 3.5;
    list<int> customers = *customer_it;
    for (list<int>::iterator customer = customers.begin();
         customer != customers.end(); ++customer) {
      avg_customer_rate1[*customer] = 4.0;
      prediction.push_back(3.8);
    }
    ++movie_it;
  }
  list<double> result = get_prediction(avg_movie_rate1, avg_customer_rate1);
  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (unsigned int i = 0; i < avg_customer_rate1.size(); ++i) {
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
  string input =
      "1:\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766\n14756\n";
  istringstream is(input);
  netflix_read(is);
  list<double> prediction;
  list<int>::iterator movie_it = movie_ids.begin();
  for (list<list<int>>::iterator customer_it = customer_ids.begin();
       customer_it != customer_ids.end(); ++customer_it) {
    avg_movie_rate2[*movie_it] = 3.5;
    list<int> customers = *customer_it;
    for (list<int>::iterator customer = customers.begin();
         customer != customers.end(); ++customer) {
      avg_customer_rate2[*customer] = 4.0;
      prediction.push_back(3.8);
    }
    ++movie_it;
  }
  list<double> result = get_prediction(avg_movie_rate2, avg_customer_rate2);
  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (unsigned int i = 0; i < avg_customer_rate2.size(); ++i) {
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
  string input = "1:"
                 "\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766"
                 "\n14756\n1000:\n2326571\n977808\n1010534\n1861759\n";
  istringstream is(input);
  netflix_read(is);
  list<double> prediction;
  list<int>::iterator movie_it = movie_ids.begin();
  for (list<list<int>>::iterator customer_it = customer_ids.begin();
       customer_it != customer_ids.end(); ++customer_it) {
    avg_movie_rate3[*movie_it] = 3.5;
    list<int> customers = *customer_it;
    for (list<int>::iterator customer = customers.begin();
         customer != customers.end(); ++customer) {
      avg_customer_rate3[*customer] = 4.0;
      prediction.push_back(3.8);
    }
    ++movie_it;
  }
  list<double> result = get_prediction(avg_movie_rate3, avg_customer_rate3);
  list<double>::iterator it1 = result.begin();
  list<double>::iterator it2 = prediction.begin();
  for (unsigned int i = 0; i < avg_customer_rate3.size(); ++i) {
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
  string input = "1:\n30878\n2647871\n1283744\n2488120\n";
  string output = "1:\n3.8\n3.8\n3.8\n3.8\nRMSE: 0.20\n";
  ofstream ofs("answer.txt");
  ofs << "1:\n4\n4\n4\n4\n";
  ofs.close();
  list<double> answers = get_answer("answer.txt");
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os, answers, avg_movie_rate1, avg_customer_rate1);
  ASSERT_EQ(os.str(), output);
}

TEST(NetflixFixture, netflix_calc_2) {
  reset();
  string input =
      "1:\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766\n14756\n";
  string output = "1:\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\nRMSE: 0.20\n";
  ofstream ofs("answer.txt");
  ofs << "1:\n4\n4\n4\n4\n4\n4\n4\n4\n";
  ofs.close();
  list<double> answers = get_answer("answer.txt");
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os, answers, avg_movie_rate2, avg_customer_rate2);
  ASSERT_EQ(os.str(), output);
}

TEST(NetflixFixture, netflix_calc_3) {
  reset();
  string input = "1:"
                 "\n30878\n2647871\n1283744\n2488120\n317050\n1904905\n1989766"
                 "\n14756\n1000:\n2326571\n977808\n1010534\n1861759\n";
  string output = "1:\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\n3.8\n1000:\n3.8\n3."
                  "8\n3.8\n3.8\nRMSE: 0.20\n";
  ofstream ofs("answer.txt");
  ofs << "1:\n4\n4\n4\n4\n4\n4\n4\n4\n1000:\n4\n4\n4\n4\n";
  ofs.close();
  list<double> answers = get_answer("answer.txt");
  istringstream is(input);
  ostringstream os;
  netflix_calc(is, os, answers, avg_movie_rate3, avg_customer_rate3);
  ASSERT_EQ(os.str(), output);
}
