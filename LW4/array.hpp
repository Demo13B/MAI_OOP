#pragma once
#include <memory>
#include "figure.hpp"
#include "functions.hpp"

template <class T>
class Array {
   private:
    size_t _size;
    std::unique_ptr<T[]> _arr;

   public:
    Array();
    Array(size_t size);
    ~Array();

    auto operator[](size_t index) -> T&;

    auto common_surface() -> double;
};

template <class T>
inline Array<T>::Array() {
    _size = 0;
    _arr = nullptr;
}

template <class T>
inline Array<T>::Array(size_t size) {
    _size = size;
    _arr.reset(new T[_size]);
}

template <class T>
inline Array<T>::~Array() {
    if (_size > 0) {
        _size = 0;
        _arr = nullptr;
    }
}

template <class T>
inline auto Array<T>::operator[](size_t index) -> T& {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    return _arr.get()[index];
}

template <class T>
inline auto Array<T>::common_surface() -> double {
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        res += (double)_arr.get()[i];
    }

    return res;
}