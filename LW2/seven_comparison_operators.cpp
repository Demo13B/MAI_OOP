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
