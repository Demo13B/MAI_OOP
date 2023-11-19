#include <iostream>
#include <map>
#include "stack.hpp"

auto main() -> int {
    mai::Stack<int> s;
    s.push(125);
    s.push(15);
    std::cout << s << std::endl;
    std::cout << s << std::endl;
}