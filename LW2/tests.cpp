#include <gtest/gtest.h>
#include "seven.hpp"

// Constructors test

TEST(Constructors, default_correct) {
    Seven num = Seven();
    EXPECT_EQ(num.get_stringified(), "\0");
    EXPECT_EQ(num.get_size(), 0);
}

TEST(Constructors, n_and_t) {
    Seven num = Seven(3, '1');
    EXPECT_EQ(num.get_size(), 3);
    EXPECT_EQ(num.get_stringified(), "111");
}

TEST(Constructors, n_and_t_bad_t) {
    EXPECT_ANY_THROW(Seven num = Seven(3, 'a'));
}

TEST(Constructors, n_and_t_another_bad_t) {
    EXPECT_ANY_THROW(Seven num = Seven(3, '7'));
}

TEST(Constructors, initializer_list_filled) {
    Seven num = Seven({'1', '2'});
    EXPECT_EQ(num.get_size(), 2);
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Constructors, initializer_list_empty) {
    Seven num = Seven({});
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "");
}

TEST(Constructors, initializer_list_exception) {
    EXPECT_ANY_THROW(Seven num = Seven({'a', '2'}));
}

TEST(Constructors, initializer_another_exception) {
    EXPECT_ANY_THROW(Seven num = Seven({'7', '2'}));
}

TEST(Constructors, string_filled) {
    Seven num = Seven("12");
    EXPECT_EQ(num.get_size(), 2);
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Constructors, string_empty) {
    Seven num = Seven("");
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "");
}

TEST(Constructors, string_exception) {
    EXPECT_ANY_THROW(Seven num = Seven("a2"));
}

TEST(Constructors, string_another_exception) {
    EXPECT_ANY_THROW(Seven num = Seven("72"));
}

TEST(Constructors, copy) {
    Seven num = Seven("12");
    Seven num2 = Seven(num);
    num = Seven("34");
    EXPECT_EQ(num2.get_stringified(), "12");
    EXPECT_EQ(num.get_stringified(), "34");
}

TEST(Constructors, rvalue_copy) {
    Seven num = Seven(Seven("12"));
    EXPECT_EQ(num.get_stringified(), "12");
}

// Operators testing

TEST(Operators, sum_normal) {
    Seven num = Seven("12");
    Seven num2 = Seven("12");
    EXPECT_EQ((num + num2).get_stringified(), "24");
}

TEST(Operators, sum_overboard) {
    Seven num = Seven("15");
    Seven num2 = Seven("12");
    EXPECT_EQ((num + num2).get_stringified(), "30");
}

TEST(Operators, sum_changeable_size) {
    Seven num = Seven("3");
    Seven num2 = Seven("5");
    EXPECT_EQ((num + num2).get_stringified(), "11");
}

TEST(Operators, sum_zero) {
    Seven num = Seven("0");
    Seven num2 = Seven("5");
    EXPECT_EQ((num + num2).get_stringified(), "5");
}

TEST(Operators, sum_empty) {
    Seven num = Seven("");
    Seven num2 = Seven("5");
    EXPECT_EQ((num + num2).get_stringified(), "5");
}

TEST(Operators, sub_normal) {
    Seven num = Seven("24");
    Seven num2 = Seven("12");
    EXPECT_EQ((num - num2).get_stringified(), "12");
}

TEST(Operators, sub_with_transfer) {
    Seven num = Seven("21");
    Seven num2 = Seven("12");
    EXPECT_EQ((num - num2).get_stringified(), "6");
}

TEST(Operators, sub_uneven_transfer) {
    Seven num = Seven("12000");
    Seven num2 = Seven("1");
    EXPECT_EQ((num - num2).get_stringified(), "11666");
}

TEST(Operators, sub_exception) {
    Seven num = Seven("12000");
    Seven num2 = Seven("1");
    EXPECT_ANY_THROW(num2 - num);
}

TEST(Operators, sub_uneven_transfer_2) {
    Seven num = Seven("12000");
    Seven num2 = Seven("111");
    EXPECT_EQ((num - num2).get_stringified(), "11556");
}

TEST(Operators, sub_uneven_transfer_3) {
    Seven num = Seven("12000");
    Seven num2 = Seven("110");
    EXPECT_EQ((num - num2).get_stringified(), "11560");
}

TEST(Operators, sub_zero) {
    Seven num = Seven("12000");
    Seven num2 = Seven("0");
    EXPECT_EQ((num - num2).get_stringified(), "12000");
}

TEST(Operators, sub_empty) {
    Seven num = Seven("12000");
    Seven num2 = Seven("0");
    EXPECT_EQ((num - num2).get_stringified(), "12000");
}

TEST(Operators, assignment) {
    Seven num;
    num = Seven("12");
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Operators, comparison) {
    Seven num = Seven("12");
    Seven num2 = Seven("11");
    EXPECT_TRUE(num > num2);
    EXPECT_FALSE(num < num2);
    EXPECT_TRUE(num2 < num);
    EXPECT_FALSE(num2 > num);
}

TEST(Operators, equality) {
    Seven num = Seven("12");
    Seven num2 = num;
    EXPECT_TRUE(num == num2);
    EXPECT_FALSE(num > num);
    EXPECT_FALSE(num > num);
}
