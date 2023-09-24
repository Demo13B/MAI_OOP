#include "seven.hpp"

auto Seven::get_size() -> size_t {
    return _size;
}

auto Seven::get_value() -> unsigned char* {
    return _value;
}