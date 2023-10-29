#include <iostream>
#include "array.hpp"
#include "figure.hpp"
#include "functions.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

int main() {
    std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
    std::vector<std::pair<double, double>> v2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    std::vector<std::pair<double, double>> v3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
    Octagon<double> o = Octagon<double>(v1);
    Pentagon<double> p = Pentagon<double>(v2);
    Hexagon<double> h = Hexagon<double>(v3);

    Pentagon<double> p2 = Pentagon<double>(v2);

    Array<Figure> Arr(2);
    Arr.delete_figure(0);
    Arr.update_figure(0, &p2);
    std::cout << Arr.common_surface() << std::endl;
    Arr.update_figure(0, &p);
    Arr.delete_figure(0);
    std::cout << Arr.common_surface() << std::endl;
}