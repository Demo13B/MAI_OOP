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
