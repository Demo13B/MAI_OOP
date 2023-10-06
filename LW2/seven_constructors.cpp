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
    _size = 0;
    delete _value;
    _value = nullptr;
}
