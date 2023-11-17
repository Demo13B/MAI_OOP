#include <iostream>
#include <map>
#include "allocator.hpp"

auto main() -> int {
    std::map<int, int, std::less<int>, mai::Allocator<std::pair<const int, int>>> m;

    m[1] = 10;
    m[2] = 20;
    m[3] = 30;

    std::cout << "1: " << m[1] << " 2: " << m[2] << "3: " << m[3] << std::endl;
    return 0;
}