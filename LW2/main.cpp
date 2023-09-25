#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        Seven num = Seven({'1', '2', '0'});
        Seven num2 = Seven("1020");
        bool res = num == num2;
        std::cout << num2.get_value();
    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument exception caught: " << ex.what() << std::endl;
    }
    int a;
}
