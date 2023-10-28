#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Octagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T> > points;

    Octagon<T>()
        : size(8),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Octagon<T>(std::vector<std::pair<T, T> >& v)
        : size(8),
          points(v) {}

    ~Octagon() {
        size = 0;
    }
};