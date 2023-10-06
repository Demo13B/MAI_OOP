# Лабораторная работа 2. Классы
## Автор: Салихов Тимур, группа М8О-212Б-22, вариант 8

Используя в качестве образца класс Array (см. ниже), реализовать динамические контейнеры с использова- нием динамического массива.
- Каждый класс должен быть разделен на интерфейс и реализацию.
- Самостоятельно определить необходимые типы, поля и дополнительные методы.
- Реализовать генерацию исключений в конструкторах и методах при необходимости (использовать стандартные исключения).
- Реализовать арифметические операции: сложение, вычитание, копирование
- Реализовать операции сравнения: (больше, меньше, равно).
- Арифметические операции с присваиванием должны быть реализованы как методы класса.

Создать класс Seven для работы с беззнаковыми целыми семеричными числами, используя для представления числа массив из элементов типа unsigned char, каждый элемент которого является семиричной цифрой. Младшая цифра имеет меньший индекс (единицы — в нулевом элементе массива).

## Программы

### main.cpp
```
#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        std::string val1, val2;
        std::cout << "Enter first number: ";
        std::cin >> val1;
        std::cout << "Enter second number: ";
        std::cin >> val2;

        Seven num1 = Seven(val1);
        Seven num2 = Seven(val2);

        char op;
        std::cout << "What operation do you want to perform: ";
        std::cin >> op;

        bool res;
        switch (op) {
            case '+':
                std::cout << "Result: " << (num1 + num2).get_stringified() << std::endl;
                break;

            case '-':
                std::cout << "Result: " << (num1 - num2).get_stringified() << std::endl;
                break;

            case '>':
                res = num1 > num2;
                std::cout << "Result: " << res;
                break;

            case '<':
                res = num1 < num2;
                std::cout << "Result: " << res;
                break;

            case '=':
                res = num1 == num2;
                std::cout << "Result: " << res;
                break;

            default:
                std::cout << "No such operation";
                break;
        }

    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument exception caught: " << ex.what() << std::endl;
    }
    return 0;
}
```

### seven.hpp
```
#pragma once

#include <string>

class Seven {
   private:
    unsigned char* _value;
    size_t _size;

    auto _resize() -> void;

   public:
    Seven();
    Seven(const size_t& n, const unsigned char t = 0);
    Seven(const std::initializer_list<unsigned char>& t);
    Seven(const std::string& t);

    Seven(const Seven& other);
    Seven(Seven&& other) noexcept;
    virtual ~Seven() noexcept;

    auto get_value() -> unsigned char*;
    auto get_stringified() -> std::string;
    auto get_size() -> size_t;

    auto operator+(const Seven& other) -> Seven;
    auto operator-(const Seven& other) -> Seven;
    auto operator=(const Seven& other) -> Seven&;

    auto operator>(const Seven& other) -> bool;
    auto operator<(const Seven& other) -> bool;
    auto operator==(const Seven& other) -> bool;
};

```

### seven_constructors.cpp
```
#include <exception>
#include <string>
#include "seven.hpp"

Seven::Seven() {
    _value = nullptr;
    _size = 0;
}

Seven::Seven(const size_t& n, const unsigned char t) {
    if (t != 0 && (t < 48 || t > 54))
        throw std::invalid_argument("Digit char is out of range");

    _size = n;
    _value = new unsigned char[n];
    std::fill(_value, _value + _size, t);
}

Seven::Seven(const std::initializer_list<unsigned char>& t) {
    _size = t.size();
    _value = new unsigned char[_size];

    size_t pos = _size - 1;
    for (const unsigned char& digit : t) {
        if (digit < 48 || digit > 54)
            throw std::invalid_argument("Digit char is out of range");

        _value[pos--] = digit;
    }
}

Seven::Seven(const std::string& t) {
    _size = t.size();
    _value = new unsigned char(_size);

    size_t pos = _size - 1;
    for (const unsigned char& digit : t) {
        if (digit < 48 || digit > 54)
            throw std::invalid_argument("Digit char is out of range");

        _value[pos--] = digit;
    }
}

Seven::Seven(const Seven& other) {
    _size = other._size;
    _value = new unsigned char[_size];

    for (size_t i = 0; i != _size; ++i) {
        _value[i] = other._value[i];
    }
}

Seven::Seven(Seven&& other) noexcept {
    _size = other._size;
    _value = other._value;

    other._value = nullptr;
    other._size = 0;
}

Seven::~Seven() noexcept {
    delete[] _value;
    _size = 0;
    _value = nullptr;
}
```

### seven_arithmetic_operators.cpp
```
#include "seven.hpp"

auto Seven::operator+(const Seven& other) -> Seven {
    bool longer = _size >= other._size;
    size_t maxSize, minSize;

    if (longer) {
        maxSize = _size;
        minSize = other._size;
    } else {
        maxSize = other._size;
        minSize = _size;
    }

    Seven result = Seven(maxSize);

    int transfer = 0, remainder, num1, num2, sum;
    for (size_t i = 0; i < minSize; ++i) {
        num1 = _value[i] - 48;
        num2 = other._value[i] - 48;
        sum = num1 + num2 + transfer;
        transfer = sum / 7;
        remainder = sum % 7;
        result._value[i] = remainder + 48;
    }

    for (size_t i = minSize; i < maxSize; ++i) {
        num1 = longer ? _value[i] - 48 : other._value[i] - 48;
        sum = num1 + transfer;
        transfer = sum / 7;
        remainder = sum % 7;
        result._value[i] = remainder + 48;
    }

    if (transfer != 0) {
        ++result._size;
        result._resize();
        result._value[maxSize] = transfer + 48;
    }

    return result;
}

auto Seven::operator-(const Seven& other) -> Seven {
    if (other._size > _size)
        throw std::invalid_argument("The result of subtraction would be negative");

    Seven result = Seven(*this);

    for (size_t i = other._size - 1; i < other._size; --i) {
        result._value[i] = _value[i] - other._value[i] + '0';

        if (result._value[i] < '0') {
            result._value[i] += 7;
            size_t pos = i + 1;
            while (pos != result._size && result._value[pos] == '0') {
                result._value[pos] = '6';
                pos += 1;
            }

            if (pos == result._size)
                throw std::invalid_argument("The result of subtraction would be negative");

            --result._value[pos];
            if (pos + 1 == result._size && result._value[pos] == '0') {
                --result._size;
                result._resize();
            }
        }
    }

    return result;
}

auto Seven::operator=(const Seven& other) -> Seven& {
    _size = other._size;
    _value = new unsigned char[_size];

    for (size_t i = 0; i != _size; ++i) {
        _value[i] = other._value[i];
    }

    return *this;
}
```

### seven_comparison_operators.cpp
```
#include "seven.hpp"

auto Seven::operator>(const Seven& other) -> bool {
    if (_size > other._size)
        return true;

    if (other._size > _size)
        return false;

    for (size_t i = _size - 1; i < _size; --i) {
        if (_value[i] > other._value[i])
            return true;
        if (other._value[i] > _value[i])
            return false;
    }

    return false;
}

auto Seven::operator<(const Seven& other) -> bool {
    if (_size < other._size)
        return true;

    if (other._size < _size)
        return false;

    for (size_t i = _size - 1; i < _size; --i) {
        if (_value[i] < other._value[i])
            return true;
        if (other._value[i] < _value[i])
            return false;
    }

    return false;
}

auto Seven::operator==(const Seven& other) -> bool {
    if (_size != other._size)
        return false;

    for (size_t i = 0; i < _size; ++i) {
        if (_value[i] != other._value[i])
            return false;
    }

    return true;
}

```

### seven_getters.cpp
```
#include "seven.hpp"

auto Seven::get_value() -> unsigned char* {
    return _value;
}

auto Seven::get_stringified() -> std::string {
    std::string out = "";

    for (size_t i = _size - 1; i < _size; --i) {
        out += _value[i];
    }

    return out;
}

auto Seven::get_size() -> size_t {
    return _size;
}

```

### seven_private.cpp
```
#include "seven.hpp"

auto Seven::_resize() -> void {
    unsigned char* resized = new unsigned char[_size]{};

    for (size_t i = 0; i < _size; ++i) {
        resized[i] = _value[i];
    }

    delete[] _value;
    _value = resized;
}

```

### tests.cpp
```
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

```