#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        size_t i = 10;
        Seven num = Seven("125");
        num.resize(4);
        std::cout << num.get_value() << std::endl;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    int a;
}
