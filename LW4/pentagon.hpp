#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"
#include "functions.hpp"

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

    auto operator=(const Pentagon<T>& other) -> Pentagon<T>&;
    auto operator=(Pentagon<T>&& other) -> Pentagon<T>&;

    operator double() const;
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

template <typename T>
inline auto operator==(const Pentagon<T>& left, const Pentagon<T>& right) -> bool {
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
inline auto Pentagon<T>::operator=(const Pentagon<T>& other) -> Pentagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Pentagon<T>::operator=(Pentagon<T>&& other) -> Pentagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Pentagon<T>::operator double() const {
    return (double)fig::surface<Pentagon<T>, T>(*this);
}