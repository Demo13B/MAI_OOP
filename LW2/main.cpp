#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        size_t i = 10;
        Seven num = Seven("0211");
        Seven num2 = Seven("1");
        Seven res = num - num2;
        std::cout << res.get_value() << std::endl;
        std::cout << res.get_size() << std::endl;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    int a;
}
