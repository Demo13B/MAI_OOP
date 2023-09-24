#include <exception>
#include <string>
#include "seven.hpp"

Seven::Seven() {
    _value = new unsigned char[100]{};
    _size = 0;
}

Seven::Seven(const size_t& n, const unsigned char t) {
    _size = n;
    _value = new unsigned char[n]{t};
}

Seven::Seven(const std::initializer_list<unsigned char>& t) {
    _value = new unsigned char(t.size());
    _size = 0;

    for (const unsigned char& digit : t) {
        if (digit < 48 || digit > 54)
            throw std::invalid_argument("Digit char is out of range");

        _value[_size] = digit;
        ++_size;
    }
}

Seven::Seven(const std::string& t) {
    _value = new unsigned char(t.size());
    _size = 0;

    for (const unsigned char& digit : t) {
        if (digit < 48 || digit > 54)
            throw std::invalid_argument("Digit char is out of range");

        _value[_size] = digit;
        ++_size;
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
    _value = new unsigned char[_size];

    for (size_t i = 0; i != _size; ++i) {
        _value[i] = other._value[i];
    }

    other._value = nullptr;
    other._size = 0;
}

Seven::~Seven() noexcept {
    _size = 0;
    delete _value;
}
