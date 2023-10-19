# Лабораторная работа 2. Классы
## Автор: Салихов Тимур, группа М8О-212Б-22, вариант 22

Разработать программу на языке C++ согласно варианту задания. Программа на C++ должна собираться с помощью системы сборки CMake. Программа должна получать данные из стандартного ввода (std::cin) и выводить данные в стандартный вывод (std::cout).
Необходимо зарегистрироваться на GitHub и создать репозитарий для задания лабораторных работ.
Преподавателю необходимо предъявить ссылку на публичный репозиторий на Github. Необходимо реализовать функцию согласно варианту задания. Функция должна быть помещена в отдельный файл.

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения.
Все классы должны поддерживать набор общих методов:
1. Вычисление геометрического центра фигуры вращения;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры через перегрузку оператора << для std::ostream;
3. Чтение из стандартного потока данных фигур через перегрузку оператора >> для std::istream
4. Вычисление площади фигуры через перегрузку оператора приведения к типу double;

Создать программу, которая позволяет:
- Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
- Сохранять созданные фигуры в динамический массив (по аналогии с предыдущей лабораторной работой Array) указатели на фигуру (Figure*)
- Фигуры должны иметь переопределенные операции копирования (=), перемещения (=) и сравнения (==)
- Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве. •Удалять из массива фигуру по индексу;

Вариант 22: 5-угольник, 6-угольник, 8-угольник.

## Программы

### main.cpp
```
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

    size_t to_delete;
    std::cout << "How many figures do you want to delete?: ";
    std::cin >> to_delete;

    if (to_delete > count) {
        std::cerr << "You want to delete more elements than threre are";
        return 1;
    }

    for (size_t i = 0; i != to_delete; ++i) {
        size_t index;
        std::cout << "What figure do you want to delete (index)?: ";
        std::cin >> index;

        if (index > count) {
            std::cout << "No such figure" << std::endl;
            return 1;
        }

        delete figures[index];
        figures[index] = nullptr;
    }

    Pentagon p;
    Hexagon h;
    Octagon o;
    for (size_t i = 0; i != count; ++i) {
        if (figures[i] == nullptr) {
            std::cout << "The figure has been deleted" << std::endl;
        } else if (typeid(p) == typeid(*figures[i])) {
            std::cout << *(Pentagon*)figures[i];
        } else if (typeid(h) == typeid(*figures[i])) {
            std::cout << *(Hexagon*)figures[i];
        } else if (typeid(o) == typeid(*figures[i])) {
            std::cout << *(Octagon*)figures[i];
        }
    }
}
```

### figure.hpp
```
#pragma once
#include <iostream>
#include <utility>

class Figure {
   public:
    Figure() = default;
    virtual ~Figure() = default;

    virtual auto mid_point() const -> std::pair<double, double> = 0;
    virtual auto surface() const -> double = 0;

    virtual explicit operator double() const = 0;
};
```

### pentagon.hpp
```
#pragma once
#include <cmath>
#include <vector>
#include "figure.hpp"

class Pentagon : public Figure {
   private:
    std::vector<std::pair<double, double>> _points;
    std::pair<double, double> _mid_point;
    double _surface;

   public:
    Pentagon();
    Pentagon(std::vector<std::pair<double, double>>& points);
    ~Pentagon();

    auto get_points() const -> std::vector<std::pair<double, double>>;
    auto mid_point() const -> std::pair<double, double> override;
    auto surface() const -> double override;

    friend auto operator<<(std::ostream& os, const Pentagon& p) -> std::ostream&;
    friend auto operator>>(std::istream& is, Pentagon& p) -> std::istream&;

    auto operator==(const Pentagon& other) const -> bool;
    auto operator=(const Pentagon& other) -> Pentagon&;
    auto operator=(Pentagon&& other) -> Pentagon&;

    explicit operator double() const override;
};

inline auto operator<<(std::ostream& os, const Pentagon& p) -> std::ostream& {
    os << "Points: ";

    std::vector<std::pair<double, double>> points = p.get_points();

    for (size_t i = 0; i != 5; ++i) {
        os << "x" << i + 1 << " = " << points[i].first << ", "
           << "y" << i + 1 << " = " << points[i].second << "; ";
    }

    os << std::endl;

    return os;
}

inline auto operator>>(std::istream& is, Pentagon& p) -> std::istream& {
    std::vector<std::pair<double, double>> v(5);

    for (size_t i = 0; i != 5; ++i) {
        is >> v[i].first >> v[i].second;
    }

    p = Pentagon(v);

    return is;
}
```

### pentagon.cpp
```
#include "pentagon.hpp"
#include <cmath>
#include <exception>

Pentagon::Pentagon() {
    _points.resize(5);
    _mid_point.first = 0;
    _mid_point.second = 0;
    _surface = 0;
}

Pentagon::Pentagon(std::vector<std::pair<double, double>>& points) {
    if (points.size() != 5)
        throw std::invalid_argument("Point count is wrong");

    for (std::pair<double, double> point : points) {
        _points.push_back(point);
        _mid_point.first += point.first;
        _mid_point.second += point.second;
    }

    _mid_point.first /= 5;
    _mid_point.second /= 5;

    double side = std::sqrt(std::pow(_points[0].first - _points[1].first, 2) + std::pow(_points[0].second - _points[1].second, 2));
    double perimeter = 5 * side;
    double apotheme = side / (2 * std::tan(36));
    _surface = perimeter * apotheme / 2;
}

Pentagon::~Pentagon() {
    _surface = 0;
}

auto Pentagon::get_points() const -> std::vector<std::pair<double, double>> {
    return _points;
}

auto Pentagon::mid_point() const -> std::pair<double, double> {
    return _mid_point;
}

auto Pentagon::surface() const -> double {
    return _surface;
}

auto Pentagon::operator==(const Pentagon& other) const -> bool {
    std::vector<std::pair<double, double>> points = other.get_points();
    for (size_t i = 0; i != 5; ++i) {
        for (size_t j = 0; j != 5; ++j) {
            if (_points[i] == points[j])
                break;

            if (j == 4)
                return false;
        }
    }

    return true;
}

auto Pentagon::operator=(const Pentagon& other) -> Pentagon& {
    _points = other.get_points();
    _mid_point = other.mid_point();
    _surface = other.surface();

    return *this;
}

auto Pentagon::operator=(Pentagon&& other) -> Pentagon& {
    _points = std::move(other._points);
    _mid_point = std::move(other._mid_point);
    _surface = std::move(other._surface);

    return *this;
}

Pentagon::operator double() const {
    return surface();
}
```

### hexagon.hpp
```
#pragma once
#include <cmath>
#include <vector>
#include "figure.hpp"

class Hexagon : public Figure {
   private:
    std::vector<std::pair<double, double>> _points;
    std::pair<double, double> _mid_point;
    double _surface;

   public:
    Hexagon();
    Hexagon(std::vector<std::pair<double, double>>& points);
    ~Hexagon();

    auto get_points() const -> std::vector<std::pair<double, double>>;
    auto mid_point() const -> std::pair<double, double> override;
    auto surface() const -> double override;

    friend auto operator<<(std::ostream& os, const Hexagon& p) -> std::ostream&;
    friend auto operator>>(std::istream& is, Hexagon& p) -> std::istream&;

    auto operator==(const Hexagon& other) const -> bool;
    auto operator=(const Hexagon& other) -> Hexagon&;
    auto operator=(Hexagon&& other) -> Hexagon&;

    explicit operator double() const override;
};

inline auto operator<<(std::ostream& os, const Hexagon& p) -> std::ostream& {
    os << "Points: ";

    std::vector<std::pair<double, double>> points = p.get_points();

    for (size_t i = 0; i != 6; ++i) {
        os << "x" << i + 1 << " = " << points[i].first << ", "
           << "y" << i + 1 << " = " << points[i].second << "; ";
    }

    os << std::endl;

    return os;
}

inline auto operator>>(std::istream& is, Hexagon& p) -> std::istream& {
    std::vector<std::pair<double, double>> v(6);

    for (size_t i = 0; i != 6; ++i) {
        is >> v[i].first >> v[i].second;
    }

    p = Hexagon(v);

    return is;
}
```

### hexagon.cpp
```
#include "hexagon.hpp"
#include <cmath>
#include <exception>

Hexagon::Hexagon() {
    _points.resize(6);
    _mid_point.first = 0;
    _mid_point.second = 0;
    _surface = 0;
}

Hexagon::Hexagon(std::vector<std::pair<double, double>>& points) {
    if (points.size() != 6)
        throw std::invalid_argument("Point count is wrong");

    for (std::pair<double, double> point : points) {
        _points.push_back(point);
        _mid_point.first += point.first;
        _mid_point.second += point.second;
    }

    _mid_point.first /= 6;
    _mid_point.second /= 6;

    double side = std::sqrt(std::pow(_points[0].first - _points[1].first, 2) + std::pow(_points[0].second - _points[1].second, 2));
    double perimeter = 6 * side;
    double apotheme = side / (2 * std::tan(30));
    _surface = perimeter * apotheme / 2;
}

Hexagon::~Hexagon() {
    _surface = 0;
}

auto Hexagon::get_points() const -> std::vector<std::pair<double, double>> {
    return _points;
}

auto Hexagon::mid_point() const -> std::pair<double, double> {
    return _mid_point;
}

auto Hexagon::surface() const -> double {
    return _surface;
}

auto Hexagon::operator==(const Hexagon& other) const -> bool {
    std::vector<std::pair<double, double>> points = other.get_points();
    for (size_t i = 0; i != 6; ++i) {
        for (size_t j = 0; j != 6; ++j) {
            if (_points[i] == points[j])
                break;

            if (j == 5)
                return false;
        }
    }

    return true;
}

auto Hexagon::operator=(const Hexagon& other) -> Hexagon& {
    _points = other.get_points();
    _mid_point = other.mid_point();
    _surface = other.surface();

    return *this;
}

auto Hexagon::operator=(Hexagon&& other) -> Hexagon& {
    _points = std::move(other._points);
    _mid_point = std::move(other._mid_point);
    _surface = std::move(other._surface);

    return *this;
}

Hexagon::operator double() const {
    return surface();
}
```

### octagon.hpp
```
#pragma once
#include <cmath>
#include <vector>
#include "figure.hpp"

class Octagon : public Figure {
   private:
    std::vector<std::pair<double, double>> _points;
    std::pair<double, double> _mid_point;
    double _surface;

   public:
    Octagon();
    Octagon(std::vector<std::pair<double, double>>& points);
    ~Octagon();

    auto get_points() const -> std::vector<std::pair<double, double>>;
    auto mid_point() const -> std::pair<double, double> override;
    auto surface() const -> double override;

    friend auto operator<<(std::ostream& os, const Octagon& p) -> std::ostream&;
    friend auto operator>>(std::istream& is, Octagon& p) -> std::istream&;

    auto operator==(const Octagon& other) const -> bool;
    auto operator=(const Octagon& other) -> Octagon&;
    auto operator=(Octagon&& other) -> Octagon&;

    explicit operator double() const override;
};

inline auto operator<<(std::ostream& os, const Octagon& p) -> std::ostream& {
    os << "Points: ";

    std::vector<std::pair<double, double>> points = p.get_points();

    for (size_t i = 0; i != 8; ++i) {
        os << "x" << i + 1 << " = " << points[i].first << ", "
           << "y" << i + 1 << " = " << points[i].second << "; ";
    }

    os << std::endl;

    return os;
}

inline auto operator>>(std::istream& is, Octagon& p) -> std::istream& {
    std::vector<std::pair<double, double>> v(8);

    for (size_t i = 0; i != 8; ++i) {
        is >> v[i].first >> v[i].second;
    }

    p = Octagon(v);

    return is;
}
```

### octagon.cpp
```
#include "octagon.hpp"
#include <cmath>
#include <exception>

Octagon::Octagon() {
    _points.resize(8);
    _mid_point.first = 0;
    _mid_point.second = 0;
    _surface = 0;
}

Octagon::Octagon(std::vector<std::pair<double, double>>& points) {
    if (points.size() != 8)
        throw std::invalid_argument("Point count is wrong");

    for (std::pair<double, double> point : points) {
        _points.push_back(point);
        _mid_point.first += point.first;
        _mid_point.second += point.second;
    }

    _mid_point.first /= 8;
    _mid_point.second /= 8;

    double side = std::sqrt(std::pow(_points[0].first - _points[1].first, 2) + std::pow(_points[0].second - _points[1].second, 2));
    double perimeter = 8 * side;
    double apotheme = side / (2 * std::tan(22.5));
    _surface = perimeter * apotheme / 2;
}

Octagon::~Octagon() {
    _surface = 0;
}

auto Octagon::get_points() const -> std::vector<std::pair<double, double>> {
    return _points;
}

auto Octagon::mid_point() const -> std::pair<double, double> {
    return _mid_point;
}

auto Octagon::surface() const -> double {
    return _surface;
}

auto Octagon::operator==(const Octagon& other) const -> bool {
    std::vector<std::pair<double, double>> points = other.get_points();
    for (size_t i = 0; i != 8; ++i) {
        for (size_t j = 0; j != 8; ++j) {
            if (_points[i] == points[j])
                break;

            if (j == 7)
                return false;
        }
    }

    return true;
}

auto Octagon::operator=(const Octagon& other) -> Octagon& {
    _points = other.get_points();
    _mid_point = other.mid_point();
    _surface = other.surface();

    return *this;
}

auto Octagon::operator=(Octagon&& other) -> Octagon& {
    _points = std::move(other._points);
    _mid_point = std::move(other._mid_point);
    _surface = std::move(other._surface);

    return *this;
}

Octagon::operator double() const {
    return surface();
}
```

### tests.cpp
```
#include <gtest/gtest.h>
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
std::vector<std::pair<double, double>> v2 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

TEST(Pentagon, empty_constructor) {
    Pentagon p;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(p.mid_point(), center);
    EXPECT_EQ(p.surface(), 0);
}

TEST(Pentagon, vector_constructor) {
    Pentagon p(v1);
    std::pair<double, double> center{3, 3};
    EXPECT_EQ(p.get_points(), v1);
    EXPECT_EQ(p.mid_point(), center);
}

TEST(Pentagon, equality) {
    Pentagon p1(v1);
    Pentagon p2(v1);
    Pentagon p3(v2);
    EXPECT_EQ(p1, p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Pentagon, copy) {
    Pentagon p1;
    Pentagon p2(v1);
    Pentagon p3(v2);
    p1 = p2;
    EXPECT_EQ(p1, p2);
    Pentagon p4;
    p4 = p1;
    p2 = p3;
    EXPECT_EQ(p1, p4);
}

TEST(Pentagon, assignment) {
    Pentagon p;
    p = Pentagon(v1);
    std::pair<double, double> center{3, 3};
    EXPECT_EQ(p.get_points(), v1);
    EXPECT_EQ(p.mid_point(), center);
}

TEST(Pentagon, double_cast) {
    Pentagon p(v1);
    double a = (double)p;
    EXPECT_EQ(a, p.surface());
}

std::vector<std::pair<double, double>> v3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::vector<std::pair<double, double>> v4 = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon, empty_constructor) {
    Hexagon h;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(h.mid_point(), center);
    EXPECT_EQ(h.surface(), 0);
}

TEST(Hexagon, vector_constructor) {
    Hexagon h(v3);
    std::pair<double, double> center{3.5, 3.5};
    EXPECT_EQ(h.get_points(), v3);
    EXPECT_EQ(h.mid_point(), center);
}

TEST(Hexagon, equality) {
    Hexagon h1(v3);
    Hexagon h2(v3);
    Hexagon h3(v4);
    EXPECT_EQ(h1, h2);
    EXPECT_FALSE(h1 == h3);
}

TEST(Hexagon, copy) {
    Hexagon h1;
    Hexagon h2(v3);
    Hexagon h3(v4);
    h1 = h2;
    EXPECT_EQ(h1, h2);
    Hexagon h4;
    h4 = h1;
    h2 = h3;
    EXPECT_EQ(h1, h4);
}

TEST(Hexagon, assignment) {
    Hexagon h;
    h = Hexagon(v3);
    std::pair<double, double> center{3.5, 3.5};
    EXPECT_EQ(h.get_points(), v3);
    EXPECT_EQ(h.mid_point(), center);
}

TEST(Hexagon, double_cast) {
    Hexagon h(v3);
    double a = (double)h;
    EXPECT_EQ(a, h.surface());
}

std::vector<std::pair<double, double>> v5 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::vector<std::pair<double, double>> v6 = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon, empty_constructor) {
    Octagon o;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(o.mid_point(), center);
    EXPECT_EQ(o.surface(), 0);
}

TEST(Octagon, vector_constructor) {
    Octagon o(v5);
    std::pair<double, double> center{4.5, 4.5};
    EXPECT_EQ(o.get_points(), v5);
    EXPECT_EQ(o.mid_point(), center);
}

TEST(Octagon, equality) {
    Octagon o1(v5);
    Octagon o2(v5);
    Octagon o3(v6);
    EXPECT_EQ(o1, o2);
    EXPECT_FALSE(o1 == o3);
}

TEST(Octagon, copy) {
    Octagon o1;
    Octagon o2(v5);
    Octagon o3(v6);
    o1 = o2;
    EXPECT_EQ(o1, o2);
    Octagon o4;
    o4 = o1;
    o2 = o3;
    EXPECT_EQ(o1, o4);
}

TEST(Octagon, assignment) {
    Octagon o;
    o = Octagon(v5);
    std::pair<double, double> center{4.5, 4.5};
    EXPECT_EQ(o.get_points(), v5);
    EXPECT_EQ(o.mid_point(), center);
}

TEST(Octagon, double_cast) {
    Octagon o(v5);
    double a = (double)o;
    EXPECT_EQ(a, o.surface());
}
```

### CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)
project(Inherited_classes)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    main 
    main.cpp
    pentagon.cpp
    hexagon.cpp
    octagon.cpp
)

add_executable(
    tests
    tests.cpp
    pentagon.cpp
    hexagon.cpp
    octagon.cpp
)

target_link_libraries(tests GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(tests)
```
