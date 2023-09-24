#include "seven.hpp"

auto Seven::operator+(const Seven& other) -> Seven {
    size_t maxSize, minSize;

    if (_size >= other._size) {
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
    }

    return result;
}