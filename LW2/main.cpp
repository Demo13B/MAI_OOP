#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        Seven num = Seven();
        Seven num2 = Seven(num);
        std::cout << num.get_value() << std::endl;
        std::cout << num2.get_value() << std::endl;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    int a;
}
