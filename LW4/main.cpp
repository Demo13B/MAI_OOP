#include <iostream>
#include "classes.hpp"
#include "functions.hpp"

int main() {
    std::vector<std::pair<double, double> > v = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    Octagon<double> o = Octagon<double>(v);
    std::cout << o.points[3].first << ' ' << o.points[3].second << std::endl;

    std::pair<double, double> p = getMidPoint(o);
    std::cout << p.first << " " << p.second << std::endl;
}