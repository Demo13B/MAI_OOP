#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        Seven num = Seven("0211");
        Seven num2 = Seven("0201");
        bool res = num > num;
        std::cout << res;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument exception caught: " << ex.what() << std::endl;
    }
    int a;
}
