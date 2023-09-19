#include <gtest/gtest.h>
#include "crazyChecker.hpp"

TEST(Monday, correct_number) {
    ASSERT_TRUE(isAfraid("Monday", 12));
}

TEST(Monday, wrong_number) {
    ASSERT_FALSE(isAfraid("Monday", 10));
}

TEST(Tuesday, correct_number) {
    ASSERT_TRUE(isAfraid("Tuesday", 144));
}

TEST(Tuesday, wrong_number) {
    ASSERT_FALSE(isAfraid("Tuesday", 10));
}

TEST(Wednesday, correct_number) {
    ASSERT_TRUE(isAfraid("Wednesday", 34));
}

TEST(Wednesday, wrong_number) {
    ASSERT_FALSE(isAfraid("Wednesday", 10));
}

TEST(Thursday, correct_number) {
    ASSERT_TRUE(isAfraid("Thursday", 0));
}

TEST(Thursday, wrong_number) {
    ASSERT_FALSE(isAfraid("Thursday", 1));
}

TEST(Friday, correct_number) {
    ASSERT_TRUE(isAfraid("Friday", 2));
}

TEST(Friday, correct_number2) {
    ASSERT_TRUE(isAfraid("Friday", 14));
}

TEST(Friday, wrong_number) {
    ASSERT_FALSE(isAfraid("Friday", 1));
}

TEST(Friday, wrong_number2) {
    ASSERT_FALSE(isAfraid("Friday", 15));
}

TEST(Saturday, correct_number) {
    ASSERT_TRUE(isAfraid("Saturday", 56));
}

TEST(Saturday, wrong_number) {
    ASSERT_FALSE(isAfraid("Saturday", 1));
}

TEST(Sunday, correct_number) {
    ASSERT_TRUE(isAfraid("Sunday", 666));
}

TEST(Sunday, correct_number2) {
    ASSERT_TRUE(isAfraid("Sunday", -666));
}

TEST(Sunday, wrong_number) {
    ASSERT_FALSE(isAfraid("Sunday", 1));
}

TEST(Wrong_day, any_number) {
    ASSERT_FALSE(isAfraid("Nday", 34));
}
