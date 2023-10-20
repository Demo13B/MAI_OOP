#include <iostream>
#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

auto main() -> int {
    size_t count;
    std::cout << "How many figures do you want to create?: ";
    std::cin >> count;

    Array f = Array(count);

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
                f[i] = p;
                break;

            case 'h':
                h = new Hexagon;
                std::cout << "Please, enter the hexagon point coordinates: " << std::endl;
                std::cin >> *h;
                f[i] = h;
                break;

            case 'o':
                o = new Octagon;
                std::cout << "Please, enter the octagon point coordinates: " << std::endl;
                std::cin >> *o;
                f[i] = o;
                break;
        }
    }

    for (size_t i = 0; i != count; ++i) {
        std::pair<double, double> center = f[i]->mid_point();
        double surface = f[i]->surface();

        std::cout
            << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
            << "); Surface = " << surface << std::endl;
    }

    std::cout << "Total surface: " << f.common_surface() << std::endl;

    size_t to_delete;
    std::cout << "How many figures do you want to delete?: ";
    std::cin >> to_delete;

    if (to_delete > count) {
        std::cerr << "You want to delete more elements than threre are";
        return 1;
    }

    size_t index;
    for (size_t i = 0; i != to_delete; ++i) {
        std::cout << "What figure do you want to delete (index)?: ";
        std::cin >> index;

        if (index > count) {
            std::cout << "No such figure" << std::endl;
            return 1;
        }

        f.delete_figure(i);
    }

    Pentagon p;
    Hexagon h;
    Octagon o;
    for (size_t i = 0; i != count; ++i) {
        if (f[i] == nullptr) {
            std::cout << "The figure has been deleted" << std::endl;
        } else if (typeid(p) == typeid(*f[i])) {
            std::cout << *(Pentagon*)f[i];
        } else if (typeid(h) == typeid(*f[i])) {
            std::cout << *(Hexagon*)f[i];
        } else if (typeid(o) == typeid(*f[i])) {
            std::cout << *(Octagon*)f[i];
        }
    }
}
