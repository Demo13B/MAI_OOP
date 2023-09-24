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
        result.resize();
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
                result.resize();
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