#include <iostream>
#include <map>
#include "allocator.hpp"
#include "stack.hpp"

auto main() -> int {
    mai::Stack<int> s;
    s.push(125);
    s.push(15);
    std::cout << s << std::endl;

    auto it = s.begin();
    ++it;

    std::cout << *it << std::endl;
}