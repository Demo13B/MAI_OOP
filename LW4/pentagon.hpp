#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Pentagon : public Figure {
    size_t size;
    std::vector<std::pair<T, T> > points;

    Pentagon()
        : size(5),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Pentagon(std::vector<std::pair<T, T> >& v)
        : size(5),
          points(v) {}

    ~Pentagon() {
        size = 0;
    }
};