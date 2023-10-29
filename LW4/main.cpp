#include <iostream>
#include "figure.hpp"
#include "functions.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

int main() {
    std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    std::vector<std::pair<double, double>> v2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    std::vector<std::pair<double, double>> v3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
    Octagon<double> o = Octagon<double>(v1);
    Pentagon<double> p = Pentagon<double>(v2);
    Hexagon<double> h = Hexagon<double>(v3);

    Pentagon<double> p2 = Pentagon<double>(v2);

    if (p == p2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    p2 = p;
    p2 = Pentagon<double>(v1);

    std::cout << o << std::endl;
    std::cout << p << std::endl;
    std::cout << h << std::endl;

    // std::vector<std::pair<int, int> > v = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    // Octagon<int> o = Octagon<int>(v);
    // std::cout << o.points[3].first << ' ' << o.points[3].second << std::endl;

    // std::pair<int, int> p = getMidPoint<Octagon<int>, int>(o);
    // std::cout << p.first << " " << p.second << std::endl;
}