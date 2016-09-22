#include "Netflix.h"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cmath> //sqrt

using namespace std;


// ------------
// netflix_read
// ------------

TEST(NetflixFixture, read_1) 
{
	istringstream r("1:\n");
	int x;
	bool c = false;
	const bool b = netflix_read(r, x, c);	
	ASSERT_TRUE(b);
	ASSERT_TRUE(c);
	ASSERT_EQ(1, x);	
}

TEST(NetflixFixture, read_2)
{
	istringstream r("2345\n");
	int x;
	bool c = false;
	const bool b = netflix_read(r, x, c);
	ASSERT_TRUE(b);
	ASSERT_FALSE(c);
	ASSERT_EQ(2345, x);
}

TEST(NetflixFixture, read_3)
{
	istringstream r("");
	int x;
	bool c = false;
	const bool b = netflix_read(r, x, c);
	ASSERT_FALSE(b);
	ASSERT_FALSE(c);	
}

TEST(NetflixFixture, read_answer_triple_1)
{
	istringstream r("456 245 4\n");
	int x, y, z;
	const bool b = read_answer_triple(r, x, y, z);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 456);
	ASSERT_EQ(y, 245);
	ASSERT_EQ(z, 4);
}

TEST(NetflixFixture, read_answer_triple_2)
{
	istringstream r("234224 4223 2\n");
	int x, y, z;
	const bool b = read_answer_triple(r, x, y, z);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 234224);
	ASSERT_EQ(y, 4223);
	ASSERT_EQ(z, 2);
}

TEST(NetflixFixture, read_answer_triple_3)
{
	istringstream r("2342 923 3\n");
	int x, y, z;
	const bool b = read_answer_triple(r, x, y, z);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 2342);
	ASSERT_EQ(y, 923);
	ASSERT_EQ(z, 3);
}

TEST(NetflixFixture, read_answer_triple_4)
{
	istringstream r("");
	int x, y, z;
	const bool b = read_answer_triple(r, x, y, z);
	ASSERT_FALSE(b);
}

TEST(NetflixFixture, map_1)
{
	map<int, map<int, int> >answers;
	istringstream ans("1 30878 4\n1 2647871 4\n1 1283744 3\n");
	const bool b = map_answers(ans, answers);
	ASSERT_TRUE(b);
	map<int, map<int, int> >::iterator iter = answers.find(1);
	ASSERT_NE(iter, answers.end());
	map<int, int>::iterator iter2 = answers[1].find(1283744);
	ASSERT_NE(iter2, answers[1].end());	
	ASSERT_EQ(answers[1][1283744], 3);
}

TEST(NetflixFixture, map_2)
{
	map<int, map<int, int> >answers;
	istringstream ans("10 30878 2\n50 2647871 4\n2403 1283744 4\n");
	const bool b = map_answers(ans, answers);
	ASSERT_TRUE(b);
	map<int, map<int, int> >::iterator iter = answers.find(50);
	ASSERT_NE(iter, answers.end());
	map<int, int>::iterator iter2 = answers[50].find(2647871);
	ASSERT_NE(iter2, answers[50].end());	
	ASSERT_EQ(answers[50][2647871], 4);
}

TEST(NetflixFixture, map_3)
{
	map<int, map<int, int> >answers;
	istringstream ans("");
	const bool b = map_answers(ans, answers);
	ASSERT_TRUE(b);
	map<int, map<int, int> >::iterator iter = answers.find(2775);
	ASSERT_TRUE(answers.empty());
	ASSERT_EQ(iter, answers.end());
}

TEST(NetflixFixture, read_avg_rating_1)
{
	istringstream r("32541 3.20\n");
	int x;
	double y;
	const bool b = read_avg_rating(r, x, y);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 32541);
	ASSERT_EQ(y, 3.20);	 
}

TEST(NetflixFixture, read_avg_rating_2)
{
	istringstream r("987234 2.73\n");
	int x;
	double y;
	const bool b = read_avg_rating(r, x, y);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 987234);
	ASSERT_EQ(y, 2.73);	 
}

TEST(NetflixFixture, read_avg_rating_3)
{
	istringstream r("1248 1.04\n");
	int x;
	double y;
	const bool b = read_avg_rating(r, x, y);
	ASSERT_TRUE(b);
	ASSERT_EQ(x, 1248);
	ASSERT_EQ(y, 1.04);	 
}

TEST(NetflixFixture, read_avg_rating_4)
{
	istringstream r("");
	int x;
	double y;
	const bool b = read_avg_rating(r, x, y);
	ASSERT_FALSE(b);
}

TEST(NetflixFixture, map_avg_ratings_1)
{
	istringstream r("23452 4.23\n2323 3.56\n2352 2.34\n");
	map<int, double> avg_ratings;
	const bool b = map_avg_ratings(r, avg_ratings);
	ASSERT_TRUE(b);
	map<int, double>::iterator iter = avg_ratings.find(2352);
	ASSERT_NE(iter, avg_ratings.end());
	ASSERT_EQ(avg_ratings[2352], 2.34);
}

TEST(NetflixFixture, map_avg_ratings_2)
{
	istringstream r("23452 4.23\n2323 3.56\n2352 2.34\n");
	map<int, double> avg_ratings;
	const bool b = map_avg_ratings(r, avg_ratings);
	ASSERT_TRUE(b);
	map<int, double>::iterator iter = avg_ratings.find(43);
	ASSERT_EQ(iter, avg_ratings.end());
}

TEST(NetflixFixture, map_avg_ratings_3)
{
	istringstream r("");
	map<int, double> avg_ratings;
	const bool b = map_avg_ratings(r, avg_ratings);
	ASSERT_TRUE(b);
	map<int, double>::iterator iter = avg_ratings.find(23452);
	ASSERT_TRUE(avg_ratings.empty());
	ASSERT_EQ(iter, avg_ratings.end());
}

// ---------------
// netflix_predict
// ---------------

TEST(NetflixFixture, predict_1)
{
	istringstream movs("1 3.43\n2 4.21\n3 2.45\n");
	istringstream custs("4 2.2\n5 4.2\n6 3.5\n");
	cache_data d;
	const bool b = map_avg_ratings(custs, d.cust_averages);
	ASSERT_TRUE(b);
	d.curr_movie_id = 2;
	d.curr_movie_avg = 4.21;
	int cid = 5; 
	const double v = netflix_predict(d, cid);
	const double ans = max(1.0, (OVERALL_MOVIE_AVG + (4.21 - OVERALL_MOVIE_AVG) + 
											(4.2 - OVERALL_CUST_AVG)));
	ASSERT_EQ(v, ans);
}

TEST(NetflixFixture, predict_2)
{
	istringstream movs("1 3.43\n2 4.21\n3 2.45\n");
	istringstream custs("4 2.2\n5 4.2\n6 3.5\n");
	cache_data d;
	const bool b = map_avg_ratings(custs, d.cust_averages);
	ASSERT_TRUE(b);
	d.curr_movie_id = 3;
	d.curr_movie_avg = 2.45;
	int cid = 4; 
	const double v = netflix_predict(d, cid);
	const double ans = max(1.0, (OVERALL_MOVIE_AVG + (2.45 - OVERALL_MOVIE_AVG) + 
											(2.2 - OVERALL_CUST_AVG)));
	ASSERT_EQ(v, ans);
}

TEST(NetflixFixture, predict_3)
{
	istringstream movs("1 3.43\n2 4.21\n3 2.45\n");
	istringstream custs("4 2.2\n5 4.2\n6 3.5\n");
	cache_data d;
	const bool b = map_avg_ratings(custs, d.cust_averages);
	ASSERT_TRUE(b);
	d.curr_movie_id = 1;
	d.curr_movie_avg = 3.43;
	int cid = 6; 
	const double v = netflix_predict(d, cid);
	const double ans = max(1.0, (OVERALL_MOVIE_AVG + (3.43 - OVERALL_MOVIE_AVG) + 
											(3.5 - OVERALL_CUST_AVG)));
	ASSERT_EQ(v, ans);
}
// -------------
// netflix_solve
// -------------
TEST(NetflixFeature, solve_1)
{
	istringstream in("1:\n30878:\n2647871:\n1283744:\n2488120:\n317050:\n1904905:\n1989766:\n14756:\n1027056:\n1149588:\n1394012:\n1406595:\n2529547:\n1682104:\n2625019:\n2603381:\n1774623:\n470861:\n712610:\n1772839:\n1059319:\n2380848:\n548064:\n2:\n1959936:\n748922:\n1131325:\n1312846:\n2314531:\n1636093:\n584750:\n2418486:\n715897:\n1172326:\n3:\n2344483:\n2229289:\n311641:\n2428502:\n475143:\n44402:\n47512:\n1246260:\n1148318:\n307313:\n1434479:\n1043428:\n2477231:\n349821:\n1514528:\n1641505:\n1993442:\n114072:\n2561674:\n2390623:\n2251677:\n2297310:\n823979:\n1543897:\n1347925:\n177678:\n1822229:\n2081473:\n4:\n410199:\n2434289:\n2498512:\n2573419:\n5:\n2101722:\n2187025:\n2064033:\n2469155:\n1293611:\n467152:\n2425992:\n952944:\n1919770:\n100750:\n927276:\n1722346:\n1670942:\n430715:\n1407684:\n401117:\n2573143:\n382445:\n485369:\n70199:\n1207257:\n358664:\n2620775:\n1160178:\n1595756:\n2145693:\n2170665:\n409927:\n81979:\n1866900:\n1794541:\n1146126:\n1597116:\n2203182:\n553668:\n2194429:\n959168:\n1488781:\n221630:\n966156:\n2022147:\n2300421:\n755078:\n2604633:\n209999:\n258801:\n760104:\n2118727:\n2629637:\n1210905:\n691460:\n1496861:\n1874618:\n1808686:\n789965:\n2498681:\n1132285:\n368977:\n1210948:\n1203279:\n1128196:\n1117357:\n1538319:\n2311028:\n");
	istringstream movs("1 3.75\n2 3.56\n3 3.64\n4 2.74\n5 3.92\n");
	istringstream custs("30878 3.63\n2647871 3.23\n1283744 3.54\n2488120 4.66\n317050 3.65\n1904905 3.85\n1989766 3.33\n14756 3.64\n1027056 3.98\n1149588 3.46\n1394012 2.91\n1406595 3.53\n2529547 3.92\n1682104 3.94\n2625019 2.73\n2603381 3.89\n1774623 3.53\n470861 4.45\n712610 4.08\n1772839 4.13\n1059319 3.02\n2380848 5.0\n548064 3.47\n1959936 3.57\n748922 3.42\n1131325 2.95\n1312846 3.48\n2314531 3.5\n1636093 3.85\n584750 3.62\n2418486 3.17\n715897 4.69\n1172326 4.7\n2344483 3.3\n2229289 3.68\n311641 1.88\n2428502 3.67\n475143 3.86\n44402 3.49\n47512 3.37\n1246260 3.0\n1148318 4.29\n307313 3.95\n1434479 4.32\n1043428 3.39\n2477231 3.64\n349821 4.56\n1514528 3.46\n1641505 3.34\n1993442 3.76\n114072 3.73\n2561674 2.06\n2390623 3.53\n2251677 3.1\n2297310 4.85\n823979 3.36\n1543897 3.6\n1347925 3.54\n177678 3.22\n1822229 3.71\n2081473 3.65\n410199 4.53\n2434289 3.83\n2498512 4.23\n2573419 4.03\n2101722 4.73\n2187025 3.99\n2064033 2.84\n2469155 3.6\n1293611 4.4\n467152 4.16\n2425992 3.71\n952944 3.0\n1919770 3.22\n100750 3.86\n927276 4.03\n1722346 3.83\n1670942 3.08\n430715 3.75\n1407684 3.8\n401117 3.96\n2573143 4.38\n382445 4.11\n485369 3.43\n70199 4.01\n1207257 4.26\n358664 3.71\n2620775 3.24\n1160178 4.24\n1595756 4.0\n2145693 3.34\n2170665 3.98\n409927 4.24\n81979 3.83\n1866900 4.03\n1794541 3.04\n1146126 4.45\n1597116 4.15\n2203182 3.83\n553668 4.18\n2194429 3.41\n959168 3.4\n1488781 3.78\n221630 3.44\n966156 3.68\n2022147 3.97\n2300421 3.61\n755078 3.62\n2604633 3.1\n209999 3.89\n258801 5.0\n760104 4.33\n2118727 3.45\n2629637 4.5\n1210905 3.68\n691460 4.32\n1496861 3.33\n1874618 3.18\n1808686 4.25\n789965 4.15\n2498681 3.22\n1132285 3.5\n368977 3.9\n1210948 3.64\n1203279 3.12\n1128196 3.84\n1117357 3.35\n1538319 3.91\n2311028 2.71\n");	
	istringstream ans("1 30878 4\n1 2647871 4\n1 1283744 3\n1 2488120 5\n1 317050 5\n1 1904905 4\n1 1989766 4\n1 14756 4\n1 1027056 3\n1 1149588 4\n1 1394012 5\n1 1406595 4\n1 2529547 5\n1 1682104 4\n1 2625019 3\n1 2603381 5\n1 1774623 4\n1 470861 5\n1 712610 4\n1 1772839 5\n1 1059319 3\n1 2380848 5\n1 548064 5\n2 1959936 5\n2 748922 5\n2 1131325 2\n2 1312846 3\n2 2314531 4\n2 1636093 5\n2 584750 3\n2 2418486 4\n2 715897 5\n2 1172326 5\n3 2344483 4\n3 2229289 4\n3 311641 1\n3 2428502 4\n3 475143 4\n3 44402 4\n3 47512 4\n3 1246260 3\n3 1148318 4\n3 307313 5\n3 1434479 5\n3 1043428 2\n3 2477231 4\n3 349821 4\n3 1514528 4\n3 1641505 4\n3 1993442 5\n3 114072 5\n3 2561674 1\n3 2390623 3\n3 2251677 2\n3 2297310 5\n3 823979 3\n3 1543897 4\n3 1347925 4\n3 177678 4\n3 1822229 5\n3 2081473 4\n4 410199 5\n4 2434289 2\n4 2498512 4\n4 2573419 3\n5 2101722 4\n5 2187025 2\n5 2064033 1\n5 2469155 5\n5 1293611 5\n5 467152 5\n5 2425992 4\n5 952944 3\n5 1919770 4\n5 100750 5\n5 927276 5\n5 1722346 5\n5 1670942 3\n5 430715 4\n5 1407684 5\n5 401117 3\n5 2573143 4\n5 382445 4\n5 485369 4\n5 70199 4\n5 1207257 5\n5 358664 5\n5 2620775 4\n5 1160178 5\n5 1595756 4\n5 2145693 5\n5 2170665 5\n5 409927 5\n5 81979 5\n5 1866900 5\n5 1794541 5\n5 1146126 5\n5 1597116 5\n5 2203182 1\n5 553668 5\n5 2194429 1\n5 959168 3\n5 1488781 5\n5 221630 1\n5 966156 5\n5 2022147 4\n5 2300421 3\n5 755078 5\n5 2604633 2\n5 209999 5\n5 258801 5\n5 760104 5\n5 2118727 4\n5 2629637 5\n5 1210905 5\n5 691460 3\n5 1496861 4\n5 1874618 1\n5 1808686 5\n5 789965 4\n5 2498681 5\n5 1132285 3\n5 368977 5\n5 1210948 3\n5 1203279 5\n5 1128196 3\n5 1117357 3\n5 1538319 4\n5 2311028 1\n");	
	ostringstream w;
	const int i = netflix_solve(in, ans, movs, custs, w);
	ASSERT_EQ(i, 0);
	string s = w.str();
	int idx_beg = s.length()-5;
	istringstream t(s.substr(idx_beg, 4));	
	double rmse;
	t >> rmse ;	
	ASSERT_LT(rmse, 1.0);
}

TEST(NetflixFixture, solve_2)
{
	istringstream in("2043:\n1\n2\n3\n");
	istringstream ans("");	
	istringstream movs("234 2.4\n23412 4.2\n");
	istringstream custs("234223 2.2\n23425 4.2\n13123 3.5\n");
	ostringstream w;
	const int i = netflix_solve(in, ans, movs, custs,w);
	ASSERT_EQ(i, 1);
}

TEST(NetflixFixture, solve_3)
{
	istringstream in("2043:\n1\n2\n3\n");
	istringstream ans("4 53242 3\n1 5234 2\n");	
	istringstream movs("");
	istringstream custs("234223 2.2\n23425 4.2\n13123 3.5\n");
	ostringstream w;
	const int i = netflix_solve(in, ans, movs, custs, w);
	ASSERT_EQ(i, 2);
}

TEST(NetflixFixture, solve_4)
{
	istringstream in("2043:\n1\n2\n3\n");
	istringstream ans("4 53242 3\n1 5234 2\n");	
	istringstream movs("234 2.4\n23412 4.2\n");
	istringstream custs("");
	ostringstream w;
	const int i = netflix_solve(in, ans, movs, custs, w);
	ASSERT_EQ(i, 3);
}
