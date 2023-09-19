#include <iostream>
#include "crazyChecker.hpp"

auto main() -> int {
    std::string day;
    int number;

    std::cin >> day >> number;
    std::cout << isAfraid(day, number) << std::endl;
}
