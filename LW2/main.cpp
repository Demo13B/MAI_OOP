#include <iostream>
#include "seven.hpp"

auto main() -> int {
    try {
        size_t i = 10;
        Seven num = Seven(i);
        std::cout << num.get_size() << std::endl;
    } catch (const std::invalid_argument& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    int a;
}
