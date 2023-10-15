#include <iostream>
#include "pentagon.hpp"

auto main() -> int {
    // std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    // std::vector<std::pair<double, double>> v2 = {{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 0}};
    // Pentagon p1 = Pentagon(v1);
    // Pentagon p2 = Pentagon(v2);
    Pentagon p1;
    std::cin >> p1;
    double b = p1.surface();
    std::cout << b << std::endl;
    double a = (double)p1;
    std::cout << a;
}
