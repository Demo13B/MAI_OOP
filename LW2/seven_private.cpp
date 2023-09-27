#include "seven.hpp"

auto Seven::_resize() -> void {
    unsigned char* resized = new unsigned char[_size]{};

    for (size_t i = 0; i < _size; ++i) {
        resized[i] = _value[i];
    }

    delete _value;
    _value = resized;
}
