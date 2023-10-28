#include <utility>
#include "classes.hpp"

template <class C>
auto getMidPoint(C& figures) -> std::pair<double, double> {
    size_t size = figures.size;
    std::pair<double, double> p = {0, 0};

    for (std::pair<double, double> point : figures.points) {
        p.first += point.first;
        p.second += point.second;
    }

    p.first /= size;
    p.second /= size;
    return p;
}