#include <iostream>
#include "array.hpp"
#include "figure.hpp"
#include "functions.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

int main() {
    size_t count;
    std::cout << "How many figures do you want to create?: ";
    std::cin >> count;

    Array<Figure> f = Array<Figure>(count);

    for (size_t i = 0; i != count; ++i) {
        char option;
        std::cout << "Which figure do you want to create? (p - pentagon, h - hexagon, o - octagon): ";
        std::cin >> option;

        Pentagon<double>* p;
        Hexagon<double>* h;
        Octagon<double>* o;

        switch (option) {
            case 'p':
                p = new Pentagon<double>;
                std::cout << "Please, enter the pentagon point coordinates: " << std::endl;
                std::cin >> *p;
                f.update_figure(i, p);
                break;

            case 'h':
                h = new Hexagon<double>;
                std::cout << "Please, enter the hexagon point coordinates: " << std::endl;
                std::cin >> *h;
                f.update_figure(i, h);
                break;

            case 'o':
                o = new Octagon<double>;
                std::cout << "Please, enter the octagon point coordinates: " << std::endl;
                std::cin >> *o;
                f.update_figure(i, o);
                break;
        }
    }

    for (size_t i = 0; i != count; ++i) {
        const Figure* fig = f[i];

        if (f[i] == nullptr) {
            std::cout << "The figure has been deleted" << std::endl;

        } else if (typeid(Pentagon<double>) == typeid(*fig)) {
            std::pair<double, double> center = fig::getMidPoint<Pentagon<double>, double>(*(Pentagon<double>*)f[i]);
            double surface = fig::surface<Pentagon<double>, double>(*(Pentagon<double>*)f[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;

        } else if (typeid(Hexagon<double>) == typeid(*fig)) {
            std::pair<double, double> center = fig::getMidPoint<Hexagon<double>, double>(*(Hexagon<double>*)f[i]);
            double surface = fig::surface<Hexagon<double>, double>(*(Hexagon<double>*)f[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;

        } else if (typeid(Octagon<double>) == typeid(*fig)) {
            std::pair<double, double> center = fig::getMidPoint<Octagon<double>, double>(*(Octagon<double>*)f[i]);
            double surface = fig::surface<Octagon<double>, double>(*(Octagon<double>*)f[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;
        }
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

        f.delete_figure(i);
    }

    for (size_t i = 0; i != count; ++i) {
        const Figure* fig = f[i];
        if (f[i] == nullptr) {
            std::cout << "The figure has been deleted" << std::endl;
        } else if (typeid(Pentagon<double>) == typeid(*fig)) {
            std::cout << *(Pentagon<double>*)f[i];
        } else if (typeid(Hexagon<double>) == typeid(*fig)) {
            std::cout << *(Hexagon<double>*)f[i];
        } else if (typeid(Octagon<double>) == typeid(*fig)) {
            std::cout << *(Octagon<double>*)f[i];
        }
        std::cout << std::endl;
    }
}