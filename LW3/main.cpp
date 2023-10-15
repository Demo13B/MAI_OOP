#include <iostream>
#include "pentagon.hpp"

auto main() -> int {
    std::vector<std::pair<double, double>> v = {{1, 2}, {1, 1}, {2, 3}, {3, 4}, {1, 2}};
    Pentagon p;
    std::cin >> p;
    std::cout << p;
}
