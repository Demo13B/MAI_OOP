#include <gtest/gtest.h>
#include "seven.hpp"

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
