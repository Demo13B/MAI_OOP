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

    auto operator=(const Octagon<T>& other) -> Octagon<T>&;
    auto operator=(Octagon<T>&& other) -> Octagon<T>&;

    operator double() const override;
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

template <typename T>
inline auto operator==(const Octagon<T>& left, const Octagon<T>& right) -> bool {
    for (size_t i = 0; i != 5; ++i) {
        for (size_t j = 0; j != 5; ++j) {
            if (left.points[i] == right.points[j])
                break;

            if (j == 4)
                return false;
        }
    }

    return true;
}

template <typename T>
inline auto Octagon<T>::operator=(const Octagon<T>& other) -> Octagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Octagon<T>::operator=(Octagon<T>&& other) -> Octagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Octagon<T>::operator double() const {
    return (double)fig::surface<Octagon<T>, T>(*this);
}
