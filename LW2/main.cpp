#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        Seven num = Seven("12");
        Seven num2 = Seven("12");
        Seven res = num + num2;
        std::cout << res.get_value();
    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument exception caught: " << ex.what() << std::endl;
    }
    int a;
}
