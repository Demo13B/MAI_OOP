#include <iostream>
#include "classes.hpp"

int main() {
    std::vector<std::pair<int, int> > v = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    Octagon<int> o = Octagon<int>(v);
    std::cout << o.points[3].first << ' ' << o.points[3].second << std::endl;
}