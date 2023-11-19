#include <iostream>
#include <map>
#include "stack.hpp"

auto main() -> int {
    mai::Stack<int> s;
    s.push(125);
    s.push(15);
    std::cout << s.size() << std::endl;
    s.pop();
    s.push(2);
    int n1 = s.pop();
    int n2 = s.pop();
    std::cout << n1 << "; " << n2 << std::endl;
}