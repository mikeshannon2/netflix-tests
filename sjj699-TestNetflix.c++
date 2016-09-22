#include <sstream>
#include <regex>
#include <cmath>

#include "gtest/gtest.h"

#include "Netflix.h"

using namespace std;

bool compareFloats(float a, float b) {
	return abs(a - b) < .001;
}

TEST(Netflix, compareFloats) {
	EXPECT_TRUE(compareFloats(1.0, 1.0));
}

TEST(Netflix, compareFloats_2) {
	EXPECT_FALSE(compareFloats(1.0, 2.0));
}

TEST(Netflix, compareFloats_3) {
	EXPECT_TRUE(compareFloats(1.0, 1.000000001));
}

TEST(Netflix, solve_format) {
	istringstream input("1:\n30878");
	stringstream output("");
	netflix_solve(input, output);

	string word;

	output >> word;
	EXPECT_EQ("1:", word);

	output >> word;
	EXPECT_TRUE(isdigit(word[0]));
	EXPECT_EQ(word[1], '.');
	EXPECT_TRUE(isdigit(word[2]));

	output >> word;
	EXPECT_EQ(word, "RMSE:");
	output >> word;
	EXPECT_TRUE(isdigit(word[0]));
	EXPECT_EQ(word[1], '.');
	EXPECT_TRUE(isdigit(word[2]));
	EXPECT_TRUE(isdigit(word[3]));
}

TEST(Netflix, rmse) {
	EXPECT_EQ(0, calculateRMSE({1}, {1}));
	EXPECT_EQ(6, calculateRMSE({1}, {7}));
}

TEST(Netflix, rmse_2) {
	EXPECT_EQ(0, calculateRMSE({1, 1, 1}, {1, 1, 1}));
	EXPECT_EQ(1, calculateRMSE({1, 1, 1}, {2, 2, 2}));
	EXPECT_EQ(1, calculateRMSE({2, 2, 2}, {1, 1, 1}));
	EXPECT_EQ(3, calculateRMSE({1, 1, 1}, {4, 4, 4}));
	EXPECT_EQ(3, calculateRMSE({4, 4, 4}, {1, 1, 1}));
}

TEST(Netflix, rmse_3) {
	EXPECT_TRUE(compareFloats(sqrt(14.0/3.0), calculateRMSE({1, 1, 1}, {2, 3, 4})));
}

TEST(Netflix, prediction) {
	int value = getPrediction(1, 30878);
	EXPECT_TRUE(value >= 1.0);
	EXPECT_TRUE(value <= 5.0);
}

TEST(Netflix, prediction_rmse) {
	const int movieId = 2043;
	RatingMap predictions = {
		{{movieId, 22537}, 3.0},
		{{movieId, 32229}, 3.0},
		{{movieId, 65883}, 3.0},
		{{movieId, 92970}, 3.0}
	};
	EXPECT_EQ(1, calculateRMSE(predictions));
}

TEST(Netflix, prediction_rmse_2) {
	const int movieId = 1;
	RatingMap predictions = {
		{{movieId, 14756}, 3.0},
		{{movieId, 30878}, 3.0},
		{{movieId, 317050}, 3.0},
		{{movieId, 470861}, 3.0}
	};
	EXPECT_TRUE(compareFloats(sqrt(5.0/2.0), calculateRMSE(predictions)));
}

TEST(Netflix, prediction_rmse_3) {
	const int movieId = 1376;
	RatingMap predictions = {
		{{movieId, 27822}, 3.0},
		{{movieId, 109127}, 3.0},
		{{movieId, 212424}, 3.0},
		{{movieId, 355278}, 3.0}
	};
	EXPECT_EQ(2, calculateRMSE(predictions));
}

TEST(Netflix, actual_rating) {
	const int movieId = 2043;
	RatingMap actualRating = {
		{{movieId, 22537}, 4.0},
		{{movieId, 32229}, 4.0},
		{{movieId, 65883}, 2.0},
		{{movieId, 92970}, 4.0}
	};
	for (const auto& kv : actualRating)
		EXPECT_EQ(kv.second, getActualRating(kv.first));
}

TEST(Netflix, actual_rating_2) {
	const int movieId = 1;
	RatingMap actualRating = {
		{{movieId, 14756}, 4.0},
		{{movieId, 30878}, 4.0},
		{{movieId, 317050}, 5.0},
		{{movieId, 470861}, 5.0}
	};
	for (const auto& kv : actualRating)
		EXPECT_EQ(kv.second, getActualRating(kv.first));
}

TEST(Netflix, actual_rating_3) {
	const int movieId = 1376;
	RatingMap actualRating = {
		{{movieId, 27822}, 5.0},
		{{movieId, 109127}, 5.0},
		{{movieId, 212424}, 5.0},
		{{movieId, 355278}, 5.0}
	};
	for (const auto& kv : actualRating)
		EXPECT_EQ(kv.second, getActualRating(kv.first));
}
