#include "seven.hpp"

auto Seven::resize(const size_t& n) -> void {
    if (n < _size)
        throw std::invalid_argument("The new size can't be smaller than number length");

    unsigned char* resized = new unsigned char[n]{};

    for (size_t i = 0; i < _size; ++i) {
        resized[i] = _value[i];
    }

    delete _value;
    _value = resized;
}