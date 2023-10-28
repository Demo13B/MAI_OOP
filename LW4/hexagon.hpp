#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Hexagon : public Figure {
    size_t size;
    std::vector<std::pair<T, T> > points;

    Hexagon()
        : size(6),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Hexagon(std::vector<std::pair<T, T> >& v)
        : size(6),
          points(v) {}

    ~Hexagon() {
        size = 0;
    }
};