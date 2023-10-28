#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Pentagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Pentagon()
        : size(5),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Pentagon(std::vector<std::pair<T, T>>& v)
        : size(5),
          points(v) {}

    ~Pentagon() {
        size = 0;
    }
};

template <typename T>
inline auto operator<<(std::ostream& os, const Pentagon<T>& pent) -> std::ostream& {
    for (size_t i = 0; i != pent.size; ++i) {
        os << 'x' << i << " = " << pent.points[i].first << ", "
           << 'y' << i << " = " << pent.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Pentagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}