#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Hexagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Hexagon()
        : size(6),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Hexagon(std::vector<std::pair<T, T>>& v)
        : size(6),
          points(v) {}

    ~Hexagon() {
        size = 0;
    }

    auto operator=(const Hexagon<T>& other) -> Hexagon<T>&;
    auto operator=(Hexagon<T>&& other) -> Hexagon<T>&;

    operator double() const override;
};

template <typename T>
inline auto operator<<(std::ostream& os, const Hexagon<T>& hex) -> std::ostream& {
    for (size_t i = 0; i != hex.size; ++i) {
        os << 'x' << i << " = " << hex.points[i].first << ", "
           << 'y' << i << " = " << hex.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Hexagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}

template <typename T>
inline auto operator==(const Hexagon<T>& left, const Hexagon<T>& right) -> bool {
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
inline auto Hexagon<T>::operator=(const Hexagon<T>& other) -> Hexagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Hexagon<T>::operator=(Hexagon<T>&& other) -> Hexagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Hexagon<T>::operator double() const {
    return (double)fig::surface<Hexagon<T>, T>(*this);
}
