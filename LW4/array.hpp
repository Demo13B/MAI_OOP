#pragma once
#include <memory>
#include "figure.hpp"
#include "functions.hpp"

template <class T>
class Array {
   private:
    size_t _size;
    std::unique_ptr<T*> _arr;

   public:
    Array();
    Array(size_t size);
    ~Array();

    auto operator[](size_t index) -> T*;

    auto delete_figure(size_t index) -> void;
    auto update_figure(size_t index, T* f) -> void;
    auto common_surface() -> double;
};

template <class T>
inline Array<T>::Array() {
    _size = 100;
    _arr.reset(new T*[_size]);

    for (size_t i = 0; i != _size; ++i)
        _arr.get()[i] = nullptr;
}

template <class T>
inline Array<T>::Array(size_t size) {
    _size = size;
    _arr.reset(new T*[_size]);

    for (size_t i = 0; i != _size; ++i)
        _arr.get()[i] = nullptr;
}

template <class T>
inline Array<T>::~Array() {
    for (size_t i = 0; i != _size; ++i) {
        if (_arr.get()[i] != nullptr)
            delete _arr.get()[i];
    }
    _arr = nullptr;
    _size = 0;
}

template <class T>
inline auto Array<T>::operator[](size_t index) -> T* {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    return _arr.get()[index];
}

template <class T>
inline auto Array<T>::delete_figure(size_t index) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    delete _arr.get()[index];
    _arr.get()[index] = nullptr;
}

template <class T>
inline auto Array<T>::update_figure(size_t index, T* f) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    _arr.get()[index] = f;
}

template <class T>
inline auto Array<T>::common_surface() -> double {
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        if (_arr.get()[i] != nullptr)
            res += (double)*_arr.get()[i];
    }

    return res;
}