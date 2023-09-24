#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        Seven num = Seven("0211");
        Seven num2 = Seven("0");
        Seven res = num - num2;
        std::cout << num.get_value() << std::endl;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument exception caught: " << ex.what() << std::endl;
    }
    int a;
}
