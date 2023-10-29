#include <cmath>
#include <utility>

namespace fig {

template <class C, typename T>
auto getMidPoint(C& figure) -> std::pair<T, T> {
    size_t size = figure.size;
    std::pair<T, T> p = {0, 0};

    for (std::pair<T, T> point : figure.points) {
        p.first += point.first;
        p.second += point.second;
    }

    p.first /= size;
    p.second /= size;
    return p;
}

template <class C, typename T>
auto surface(C& figure) -> T {
    T side = std::sqrt(std::pow(figure.points[0].first - figure.points[1].first, 2) + std::pow(figure.points[0].second - figure.points[1].second, 2));
    T perimeter = 5 * side;
    T deriv = 2 * std::tan((double)180 / figure.size);
    T apotheme = side / (2 * std::tan(22.5));
    return perimeter * apotheme / 2;
}

}