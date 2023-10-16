#include <iostream>
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

auto main() -> int {
    size_t count;
    std::cout << "How many figures do you want to create?: ";
    std::cin >> count;

    Figure** figures = new Figure*[count];

    for (size_t i = 0; i != count; ++i) {
        char option;
        std::cout << "Which figure do you want to create? (p - pentagon, h - hexagon, o - octagon): ";
        std::cin >> option;

        Pentagon* p;
        Hexagon* h;
        Octagon* o;

        switch (option) {
            case 'p':
                p = new Pentagon;
                std::cout << "Please, enter the pentagon point coordinates: " << std::endl;
                std::cin >> *p;
                figures[i] = p;
                break;

            case 'h':
                h = new Hexagon;
                std::cout << "Please, enter the hexagon point coordinates: " << std::endl;
                std::cin >> *h;
                figures[i] = h;
                break;

            case 'o':
                o = new Octagon;
                std::cout << "Please, enter the octagon point coordinates: " << std::endl;
                std::cin >> *o;
                figures[i] = o;
                break;
        }
    }

    double total_surface = 0.0;

    for (size_t i = 0; i != count; ++i) {
        std::pair<double, double> center = figures[i]->mid_point();
        double surface = figures[i]->surface();
        total_surface += surface;

        std::cout
            << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
            << "); Surface = " << surface << std::endl;
    }

    std::cout << "Total surface: " << total_surface << std::endl;

    size_t index;
    std::cout << "What figure do you want to delete (index)?: ";
    std::cin >> index;
    delete figures[index];
    figures[index] = nullptr;
}
