#include "array.hpp"

Array::Array() {
    _size = 100;
    _figures = new Figure*[_size];

    for (size_t i = 0; i != _size; ++i)
        _figures[i] = nullptr;
}

Array::Array(size_t size) {
    _size = size;
    _figures = new Figure*[_size];

    for (size_t i = 0; i != _size; ++i)
        _figures[i] = nullptr;
}

Array::~Array() {
    for (size_t i = 0; i != _size; ++i) {
        if (_figures[i] != nullptr)
            delete _figures[i];
    }
    delete[] _figures;
    _figures = nullptr;
    _size = 0;
}

auto Array::operator[](size_t index) const -> Figure* {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    return _figures[index];
}

auto Array::delete_figure(size_t index) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    delete _figures[index];
    _figures[index] = nullptr;
}

auto Array::update_figure(size_t index, Figure* f) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    if (_figures[index] != nullptr)
        delete _figures[index];
    _figures[index] = f;
}

auto Array::common_surface() -> double {
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        if (_figures[i] != nullptr)
            res += (double)*_figures[i];
    }

    return res;
}