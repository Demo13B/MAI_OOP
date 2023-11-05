#include <iostream>
#include "array.hpp"
#include "figure.hpp"
#include "functions.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

int main() {
    char option;
    std::cout << "Which figures do you want to create? (p - pentagon, h - hexagon, o - octagon): ";
    std::cin >> option;

    size_t count;
    std::cout << "How many figures do you want to create?: ";
    std::cin >> count;

    if (option == 'p') {
        Array<Pentagon<double>> a(count);

        Pentagon<double> p;

        for (size_t i = 0; i != count; ++i) {
            std::cout << "Please, enter the pentagon point coordinates: " << std::endl;
            std::cin >> p;
            a[i] = p;
        }

        for (size_t i = 0; i != count; ++i) {
            std::pair<double, double> center = fig::getMidPoint<Pentagon<double>, double>(a[i]);
            double surface = fig::surface<Pentagon<double>, double>(a[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;
        }

        std::cout << "Total surface: " << a.common_surface() << std::endl;

        size_t to_delete;
        std::cout << "How many figures do you want to delete?: ";
        std::cin >> to_delete;

        if (to_delete > count) {
            std::cerr << "You want to delete more elements than threre are";
            return 1;
        }

        size_t index;
        Pentagon<double> pent;
        for (size_t i = 0; i != to_delete; ++i) {
            std::cout << "What figure do you want to delete (index)?: ";
            std::cin >> index;
            a[index] = pent;
        }

        for (size_t i = 0; i != count; ++i) {
            std::cout << a[i] << std::endl;
        }

    } else if (option == 'h') {
        Array<Hexagon<double>> a(count);

        Hexagon<double> h;

        for (size_t i = 0; i != count; ++i) {
            std::cout << "Please, enter the hexagon point coordinates: " << std::endl;
            std::cin >> h;
            a[i] = h;
        }

        for (size_t i = 0; i != count; ++i) {
            std::pair<double, double> center = fig::getMidPoint<Hexagon<double>, double>(a[i]);
            double surface = fig::surface<Hexagon<double>, double>(a[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;
        }

        std::cout << "Total surface: " << a.common_surface() << std::endl;

        size_t to_delete;
        std::cout << "How many figures do you want to delete?: ";
        std::cin >> to_delete;

        if (to_delete > count) {
            std::cerr << "You want to delete more elements than threre are";
            return 1;
        }

        size_t index;
        Hexagon<double> hex;
        for (size_t i = 0; i != to_delete; ++i) {
            std::cout << "What figure do you want to delete (index)?: ";
            std::cin >> index;
            a[index] = hex;
        }

        for (size_t i = 0; i != count; ++i) {
            std::cout << a[i] << std::endl;
        }

    } else if (option == 'o') {
        Array<Octagon<double>> a(count);

        Octagon<double> o;

        for (size_t i = 0; i != count; ++i) {
            std::cout << "Please, enter the octagon point coordinates: " << std::endl;
            std::cin >> o;
            a[i] = o;
        }

        for (size_t i = 0; i != count; ++i) {
            std::pair<double, double> center = fig::getMidPoint<Octagon<double>, double>(a[i]);
            double surface = fig::surface<Octagon<double>, double>(a[i]);

            std::cout << "Figure " << i + 1 << ": Mid point = (" << center.first << ", " << center.second
                      << "); Surface = " << surface << std::endl;
        }

        std::cout << "Total surface: " << a.common_surface() << std::endl;

        size_t to_delete;
        std::cout << "How many figures do you want to delete?: ";
        std::cin >> to_delete;

        if (to_delete > count) {
            std::cerr << "You want to delete more elements than threre are";
            return 1;
        }

        size_t index;
        Octagon<double> oct;
        for (size_t i = 0; i != to_delete; ++i) {
            std::cout << "What figure do you want to delete (index)?: ";
            std::cin >> index;
            a[index] = oct;
        }

        for (size_t i = 0; i != count; ++i) {
            std::cout << a[i] << std::endl;
        }

    } else {
        std::cout << "Wrong option";
        return 1;
    }
}