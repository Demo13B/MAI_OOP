#include <iostream>
#include <map>
#include "allocator.hpp"
#include "stack.hpp"

auto main() -> int {
    mai::Stack<int> s;
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    std::cout << v[0] << " " << v[1] << std::endl;
    v[1] = 0;
    std::cout << v[0] << " " << v[1] << std::endl;
    s.push(125);
    s.push(15);
    std::cout << s << std::endl;
    std::cout << s << std::endl;
}