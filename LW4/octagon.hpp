#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Octagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Octagon<T>()
        : size(8),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Octagon<T>(std::vector<std::pair<T, T>>& v)
        : size(8),
          points(v) {}

    ~Octagon() {
        size = 0;
    }
};

template <typename T>
inline auto operator<<(std::ostream& os, const Octagon<T>& oct) -> std::ostream& {
    for (size_t i = 0; i != oct.size; ++i) {
        os << 'x' << i << " = " << oct.points[i].first << ", "
           << 'y' << i << " = " << oct.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Octagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}