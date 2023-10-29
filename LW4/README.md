# Лабораторная работа 3. Классы
## Автор: Салихов Тимур, группа М8О-212Б-22, вариант 22

Разработать шаблоны классов согласно варианту задания. Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. Для хранения координат фигур необходимо использовать шаблон std::pair (или реализовать свой шаблон template <class T> Point в качестве параметра шаблона должен быть тип для переменных координат)

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
1. Вычисление геометрического центра фигуры вращения;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры;
3. Вычисление площади фигуры;
Создать программу, которая позволяет:
- Запрещается использовать сырые указатели
- Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
- Сохранять созданные фигуры в динамический массив (переиспользовать от предыдущей лабораторной работы) умных указатели на фигуру (std::smart_ptr<Figure*>)
- Динамический массив должен быть сделан в виде шаблона (параметр шаблона – класс для хранения в массиве template <class T> Array {...})
- Фигуры должны иметь переопределенные операции копирования, сравнения и приведение к типу double (вычисление площади)
- Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве.
- Удалять из массива фигуру по индексу;

Вариант 22: 5-угольник, 6-угольник, 8-угольник.

## Программы

### main.cpp
```cpp
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
```

### figure.hpp
```cpp
#pragma once

class Figure {
   public:
    Figure() = default;
    virtual ~Figure() = default;

    virtual explicit operator double() const = 0;
};
```

### pentagon.hpp
```cpp
#pragma once
#include <utility>
#include <vector>
#include "figure.hpp"
#include "functions.hpp"

template <typename T>
class Pentagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Pentagon()
        : size(5),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Pentagon(std::vector<std::pair<T, T>>& v)
        : size(5),
          points(v) {}

    ~Pentagon() {
        size = 0;
    }

    auto operator=(const Pentagon<T>& other) -> Pentagon<T>&;
    auto operator=(Pentagon<T>&& other) -> Pentagon<T>&;

    operator double() const override;
};

template <typename T>
inline auto operator<<(std::ostream& os, const Pentagon<T>& pent) -> std::ostream& {
    for (size_t i = 0; i != pent.size; ++i) {
        os << 'x' << i << " = " << pent.points[i].first << ", "
           << 'y' << i << " = " << pent.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Pentagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}

template <typename T>
inline auto operator==(const Pentagon<T>& left, const Pentagon<T>& right) -> bool {
    for (size_t i = 0; i != 5; ++i) {
        for (size_t j = 0; j != 5; ++j) {
            if (left.points[i] == right.points[j])
                break;

            if (j == 4)
                return false;
        }
    }

    return true;
}

template <typename T>
inline auto Pentagon<T>::operator=(const Pentagon<T>& other) -> Pentagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Pentagon<T>::operator=(Pentagon<T>&& other) -> Pentagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Pentagon<T>::operator double() const {
    return (double)fig::surface<Pentagon<T>, T>(*this);
}
```

### hexagon.hpp
```cpp
#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Hexagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Hexagon()
        : size(6),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Hexagon(std::vector<std::pair<T, T>>& v)
        : size(6),
          points(v) {}

    ~Hexagon() {
        size = 0;
    }

    auto operator=(const Hexagon<T>& other) -> Hexagon<T>&;
    auto operator=(Hexagon<T>&& other) -> Hexagon<T>&;

    operator double() const override;
};

template <typename T>
inline auto operator<<(std::ostream& os, const Hexagon<T>& hex) -> std::ostream& {
    for (size_t i = 0; i != hex.size; ++i) {
        os << 'x' << i << " = " << hex.points[i].first << ", "
           << 'y' << i << " = " << hex.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Hexagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}

template <typename T>
inline auto operator==(const Hexagon<T>& left, const Hexagon<T>& right) -> bool {
    for (size_t i = 0; i != 5; ++i) {
        for (size_t j = 0; j != 5; ++j) {
            if (left.points[i] == right.points[j])
                break;

            if (j == 4)
                return false;
        }
    }

    return true;
}

template <typename T>
inline auto Hexagon<T>::operator=(const Hexagon<T>& other) -> Hexagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Hexagon<T>::operator=(Hexagon<T>&& other) -> Hexagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Hexagon<T>::operator double() const {
    return (double)fig::surface<Hexagon<T>, T>(*this);
}
```

### octagon.hpp
```cpp
#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "figure.hpp"

template <typename T>
class Octagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T>> points;

    Octagon<T>()
        : size(8),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Octagon<T>(std::vector<std::pair<T, T>>& v)
        : size(8),
          points(v) {}

    ~Octagon() {
        size = 0;
    }

    auto operator=(const Octagon<T>& other) -> Octagon<T>&;
    auto operator=(Octagon<T>&& other) -> Octagon<T>&;

    operator double() const override;
};

template <typename T>
inline auto operator<<(std::ostream& os, const Octagon<T>& oct) -> std::ostream& {
    for (size_t i = 0; i != oct.size; ++i) {
        os << 'x' << i << " = " << oct.points[i].first << ", "
           << 'y' << i << " = " << oct.points[i].second << "; ";
    }

    return os;
}

template <typename T>
inline auto operator>>(std::istream& is, Octagon<T>& fig) -> std::istream& {
    for (size_t i = 0; i != fig.size; ++i) {
        is >> fig.points[i].first >> fig.points[i].second;
    }

    return is;
}

template <typename T>
inline auto operator==(const Octagon<T>& left, const Octagon<T>& right) -> bool {
    for (size_t i = 0; i != 5; ++i) {
        for (size_t j = 0; j != 5; ++j) {
            if (left.points[i] == right.points[j])
                break;

            if (j == 4)
                return false;
        }
    }

    return true;
}

template <typename T>
inline auto Octagon<T>::operator=(const Octagon<T>& other) -> Octagon<T>& {
    size = other.size;
    points = other.points;

    return *this;
}

template <typename T>
inline auto Octagon<T>::operator=(Octagon<T>&& other) -> Octagon<T>& {
    size = other.size;
    points = std::move(other.points);

    return *this;
}

template <typename T>
inline Octagon<T>::operator double() const {
    return (double)fig::surface<Octagon<T>, T>(*this);
}
```

### functions.hpp
```cpp
#pragma once
#include <cmath>
#include <utility>

namespace fig {

template <class C, typename T>
auto getMidPoint(C& figure) -> std::pair<T, T> {
    size_t size = figure.size;
    std::pair<T, T> p = {0, 0};

    for (std::pair<T, T> point : figure.points) {
        p.first += point.first;
        p.second += point.second;
    }

    p.first /= size;
    p.second /= size;
    return p;
}

template <class C, typename T>
auto surface(const C& figure) -> T {
    T side = std::sqrt(std::pow(figure.points[0].first - figure.points[1].first, 2) + std::pow(figure.points[0].second - figure.points[1].second, 2));
    T perimeter = 5 * side;
    double angle = 180 / figure.size * 57.3;
    T apotheme = side / (2 * std::tan(angle));
    return perimeter * apotheme / 2;
}

}
```

### array.hpp
```cpp
#pragma once
#include <memory>
#include "figure.hpp"
#include "functions.hpp"

template <class T>
class Array {
   private:
    size_t _size;
    std::unique_ptr<T*> _arr;

   public:
    Array();
    Array(size_t size);
    ~Array();

    auto operator[](size_t index) -> T*;

    auto delete_figure(size_t index) -> void;
    auto update_figure(size_t index, T* f) -> void;
    auto common_surface() -> double;
};

template <class T>
inline Array<T>::Array() {
    _size = 100;
    _arr.reset(new T*[_size]);

    for (size_t i = 0; i != _size; ++i)
        _arr.get()[i] = nullptr;
}

template <class T>
inline Array<T>::Array(size_t size) {
    _size = size;
    _arr.reset(new T*[_size]);

    for (size_t i = 0; i != _size; ++i)
        _arr.get()[i] = nullptr;
}

template <class T>
inline Array<T>::~Array() {
    for (size_t i = 0; i != _size; ++i) {
        if (_arr.get()[i] != nullptr)
            delete _arr.get()[i];
    }
    _arr = nullptr;
    _size = 0;
}

template <class T>
inline auto Array<T>::operator[](size_t index) -> T* {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    return _arr.get()[index];
}

template <class T>
inline auto Array<T>::delete_figure(size_t index) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    delete _arr.get()[index];
    _arr.get()[index] = nullptr;
}

template <class T>
inline auto Array<T>::update_figure(size_t index, T* f) -> void {
    if (index >= _size)
        throw std::invalid_argument("The array index is out of range");

    _arr.get()[index] = f;
}

template <class T>
inline auto Array<T>::common_surface() -> double {
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        if (_arr.get()[i] != nullptr)
            res += (double)*_arr.get()[i];
    }

    return res;
}
```

### tests.cpp
```cpp
#include "array.hpp"
#include "figure.hpp"
#include "functions.hpp"
#include "gtest/gtest.h"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

// Pentagon double tests

std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
std::vector<std::pair<double, double>> v2 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

TEST(Pentagon_double, empty_constructor) {
    Pentagon<double> p;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::getMidPoint<Pentagon<double>, double>(p);
    double surf = fig::surface<Pentagon<double>, double>(p);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Pentagon_double, vector_constructor) {
    Pentagon<double> p(v1);
    std::pair<double, double> center{3, 3};
    std::pair<double, double> res = fig::getMidPoint<Pentagon<double>, double>(p);
    EXPECT_EQ(p.points, v1);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_double, equality) {
    Pentagon<double> p1(v1);
    Pentagon<double> p2(v1);
    Pentagon<double> p3(v2);
    EXPECT_EQ(p1, p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Pentagon_double, copy) {
    Pentagon<double> p1;
    Pentagon<double> p2(v1);
    Pentagon<double> p3(v2);
    p1 = p2;
    EXPECT_EQ(p1, p2);
    Pentagon<double> p4;
    p4 = p1;
    p2 = p3;
    EXPECT_EQ(p1, p4);
}

TEST(Pentagon_double, assignment) {
    Pentagon<double> p;
    p = Pentagon<double>(v1);
    std::pair<double, double> center{3, 3};
    std::pair<double, double> res = fig::getMidPoint<Pentagon<double>, double>(p);
    EXPECT_EQ(p.points, v1);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_double, double_cast) {
    Pentagon<double> p(v1);
    double a = (double)p;
    double surf = fig::surface<Pentagon<double>, double>(p);
    EXPECT_EQ(a, surf);
}

// Pentagon float tests

std::vector<std::pair<float, float>> v3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
std::vector<std::pair<float, float>> v4 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

TEST(Pentagon_float, empty_constructor) {
    Pentagon<float> p;
    std::pair<float, float> center{0, 0};
    std::pair<float, float> res = fig::getMidPoint<Pentagon<float>, float>(p);
    float surf = fig::surface<Pentagon<float>, float>(p);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Pentagon_float, vector_constructor) {
    Pentagon<float> p(v3);
    std::pair<float, float> center{3, 3};
    std::pair<float, float> res = fig::getMidPoint<Pentagon<float>, float>(p);
    EXPECT_EQ(p.points, v3);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_float, equality) {
    Pentagon<float> p1(v3);
    Pentagon<float> p2(v3);
    Pentagon<float> p3(v4);
    EXPECT_EQ(p1, p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Pentagon_float, copy) {
    Pentagon<float> p1;
    Pentagon<float> p2(v3);
    Pentagon<float> p3(v4);
    p1 = p2;
    EXPECT_EQ(p1, p2);
    Pentagon<float> p4;
    p4 = p1;
    p2 = p3;
    EXPECT_EQ(p1, p4);
}

TEST(Pentagon_float, assignment) {
    Pentagon<float> p;
    p = Pentagon<float>(v3);
    std::pair<float, float> center{3, 3};
    std::pair<float, float> res = fig::getMidPoint<Pentagon<float>, float>(p);
    EXPECT_EQ(p.points, v3);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_float, double_cast) {
    Pentagon<float> p(v3);
    float a = (float)p;
    float surf = fig::surface<Pentagon<float>, float>(p);
    EXPECT_EQ(a, surf);
}

// Pentagon int tests

std::vector<std::pair<int, int>> v5 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
std::vector<std::pair<int, int>> v6 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

TEST(Pentagon_int, empty_constructor) {
    Pentagon<int> p;
    std::pair<int, int> center{0, 0};
    std::pair<int, int> res = fig::getMidPoint<Pentagon<int>, int>(p);
    int surf = fig::surface<Pentagon<int>, int>(p);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Pentagon_int, vector_constructor) {
    Pentagon<int> p(v5);
    std::pair<int, int> center{3, 3};
    std::pair<int, int> res = fig::getMidPoint<Pentagon<int>, int>(p);
    EXPECT_EQ(p.points, v5);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_int, equality) {
    Pentagon<int> p1(v5);
    Pentagon<int> p2(v5);
    Pentagon<int> p3(v6);
    EXPECT_EQ(p1, p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Pentagon_int, copy) {
    Pentagon<int> p1;
    Pentagon<int> p2(v5);
    Pentagon<int> p3(v6);
    p1 = p2;
    EXPECT_EQ(p1, p2);
    Pentagon<int> p4;
    p4 = p1;
    p2 = p3;
    EXPECT_EQ(p1, p4);
}

TEST(Pentagon_int, assignment) {
    Pentagon<int> p;
    p = Pentagon<int>(v5);
    std::pair<int, int> center{3, 3};
    std::pair<int, int> res = fig::getMidPoint<Pentagon<int>, int>(p);
    EXPECT_EQ(p.points, v5);
    EXPECT_EQ(res, center);
}

TEST(Pentagon_int, double_cast) {
    Pentagon<int> p(v5);
    int a = (int)p;
    int surf = fig::surface<Pentagon<int>, int>(p);
    EXPECT_EQ(a, surf);
}

// Hexagon double tests

std::vector<std::pair<double, double>> v7 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::vector<std::pair<double, double>> v8 = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon_double, empty_constructor) {
    Hexagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::getMidPoint<Hexagon<double>, double>(h);
    double surf = fig::surface<Hexagon<double>, double>(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Hexagon_double, vector_constructor) {
    Hexagon<double> h(v7);
    std::pair<double, double> center{3.5, 3.5};
    std::pair<double, double> res = fig::getMidPoint<Hexagon<double>, double>(h);
    EXPECT_EQ(h.points, v7);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_double, equality) {
    Hexagon<double> h1(v7);
    Hexagon<double> h2(v7);
    Hexagon<double> h3(v8);
    EXPECT_EQ(h1, h2);
    EXPECT_FALSE(h1 == h3);
}

TEST(Hexagon_double, copy) {
    Hexagon<double> h1;
    Hexagon<double> h2(v7);
    Hexagon<double> h3(v8);
    h1 = h2;
    EXPECT_EQ(h1, h2);
    Hexagon<double> h4;
    h4 = h1;
    h2 = h3;
    EXPECT_EQ(h1, h4);
}

TEST(Hexagon_double, assignment) {
    Hexagon<double> h;
    h = Hexagon<double>(v7);
    std::pair<double, double> center{3.5, 3.5};
    std::pair<double, double> res = fig::getMidPoint<Hexagon<double>, double>(h);
    EXPECT_EQ(h.points, v7);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_double, double_cast) {
    Hexagon<double> h(v7);
    double a = (double)h;
    double surf = fig::surface<Hexagon<double>, double>(h);
    EXPECT_EQ(a, surf);
}

// Hexagon float tests

std::vector<std::pair<float, float>> v9 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::vector<std::pair<float, float>> v10 = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon_float, empty_constructor) {
    Hexagon<float> h;
    std::pair<float, float> center{0, 0};
    std::pair<float, float> res = fig::getMidPoint<Hexagon<float>, float>(h);
    float surf = fig::surface<Hexagon<float>, float>(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Hexagon_float, vector_constructor) {
    Hexagon<float> h(v9);
    std::pair<float, float> center{3.5, 3.5};
    std::pair<float, float> res = fig::getMidPoint<Hexagon<float>, float>(h);
    EXPECT_EQ(h.points, v9);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_float, equality) {
    Hexagon<float> h1(v9);
    Hexagon<float> h2(v9);
    Hexagon<float> h3(v10);
    EXPECT_EQ(h1, h2);
    EXPECT_FALSE(h1 == h3);
}

TEST(Hexagon_float, copy) {
    Hexagon<float> h1;
    Hexagon<float> h2(v9);
    Hexagon<float> h3(v10);
    h1 = h2;
    EXPECT_EQ(h1, h2);
    Hexagon<float> h4;
    h4 = h1;
    h2 = h3;
    EXPECT_EQ(h1, h4);
}

TEST(Hexagon_float, assignment) {
    Hexagon<float> h;
    h = Hexagon<float>(v9);
    std::pair<float, float> center{3.5, 3.5};
    std::pair<float, float> res = fig::getMidPoint<Hexagon<float>, float>(h);
    EXPECT_EQ(h.points, v9);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_float, double_cast) {
    Hexagon<float> h(v9);
    float a = (float)h;
    float surf = fig::surface<Hexagon<float>, float>(h);
    EXPECT_EQ(a, surf);
}

// Hexagon int tests

std::vector<std::pair<int, int>> v11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::vector<std::pair<int, int>> v12 = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon_int, empty_constructor) {
    Hexagon<int> h;
    std::pair<int, int> center{0, 0};
    std::pair<int, int> res = fig::getMidPoint<Hexagon<int>, int>(h);
    int surf = fig::surface<Hexagon<int>, int>(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Hexagon_int, vector_constructor) {
    Hexagon<int> h(v11);
    std::pair<int, int> center{3, 3};
    std::pair<int, int> res = fig::getMidPoint<Hexagon<int>, int>(h);
    EXPECT_EQ(h.points, v11);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_int, equality) {
    Hexagon<int> h1(v11);
    Hexagon<int> h2(v11);
    Hexagon<int> h3(v12);
    EXPECT_EQ(h1, h2);
    EXPECT_FALSE(h1 == h3);
}

TEST(Hexagon_int, copy) {
    Hexagon<int> h1;
    Hexagon<int> h2(v11);
    Hexagon<int> h3(v12);
    h1 = h2;
    EXPECT_EQ(h1, h2);
    Hexagon<int> h4;
    h4 = h1;
    h2 = h3;
    EXPECT_EQ(h1, h4);
}

TEST(Hexagon_int, assignment) {
    Hexagon<int> h;
    h = Hexagon<int>(v11);
    std::pair<int, int> center{3, 3};
    std::pair<int, int> res = fig::getMidPoint<Hexagon<int>, int>(h);
    EXPECT_EQ(h.points, v11);
    EXPECT_EQ(res, center);
}

TEST(Hexagon_int, double_cast) {
    Hexagon<int> h(v11);
    int a = (int)h;
    int surf = fig::surface<Hexagon<int>, int>(h);
    EXPECT_EQ(a, surf);
}

// Octagon double tests

std::vector<std::pair<double, double>> v13 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::vector<std::pair<double, double>> v14 = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon_double, empty_constructor) {
    Octagon<double> o;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::getMidPoint<Octagon<double>, double>(o);
    double surf = fig::surface<Octagon<double>, double>(o);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Octagon_double, vector_constructor) {
    Octagon<double> o(v13);
    std::pair<double, double> center{4.5, 4.5};
    std::pair<double, double> res = fig::getMidPoint<Octagon<double>, double>(o);
    EXPECT_EQ(o.points, v13);
    EXPECT_EQ(res, center);
}

TEST(Octagon_double, equality) {
    Octagon<double> o1(v13);
    Octagon<double> o2(v13);
    Octagon<double> o3(v14);
    EXPECT_EQ(o1, o2);
    EXPECT_FALSE(o1 == o3);
}

TEST(Octagon_double, copy) {
    Octagon<double> o1;
    Octagon<double> o2(v13);
    Octagon<double> o3(v14);
    o1 = o2;
    EXPECT_EQ(o1, o2);
    Octagon<double> o4;
    o4 = o1;
    o2 = o3;
    EXPECT_EQ(o1, o4);
}

TEST(Octagon_double, assignment) {
    Octagon<double> o;
    o = Octagon<double>(v13);
    std::pair<double, double> center{4.5, 4.5};
    std::pair<double, double> res = fig::getMidPoint<Octagon<double>, double>(o);
    EXPECT_EQ(o.points, v13);
    EXPECT_EQ(res, center);
}

TEST(Octagon_double, double_cast) {
    Octagon<double> o(v13);
    double a = (double)o;
    double surf = fig::surface<Octagon<double>, double>(o);
    EXPECT_EQ(a, surf);
}

// Octagon float tests

std::vector<std::pair<float, float>> v15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::vector<std::pair<float, float>> v16 = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon_float, empty_constructor) {
    Octagon<float> o;
    std::pair<float, float> center{0, 0};
    std::pair<float, float> res = fig::getMidPoint<Octagon<float>, float>(o);
    float surf = fig::surface<Octagon<float>, float>(o);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Octagon_float, vector_constructor) {
    Octagon<float> o(v15);
    std::pair<float, float> center{4.5, 4.5};
    std::pair<float, float> res = fig::getMidPoint<Octagon<float>, float>(o);
    EXPECT_EQ(o.points, v15);
    EXPECT_EQ(res, center);
}

TEST(Octagon_float, equality) {
    Octagon<float> o1(v15);
    Octagon<float> o2(v15);
    Octagon<float> o3(v16);
    EXPECT_EQ(o1, o2);
    EXPECT_FALSE(o1 == o3);
}

TEST(Octagon_float, copy) {
    Octagon<float> o1;
    Octagon<float> o2(v15);
    Octagon<float> o3(v16);
    o1 = o2;
    EXPECT_EQ(o1, o2);
    Octagon<float> o4;
    o4 = o1;
    o2 = o3;
    EXPECT_EQ(o1, o4);
}

TEST(Octagon_float, assignment) {
    Octagon<float> o;
    o = Octagon<float>(v15);
    std::pair<float, float> center{4.5, 4.5};
    std::pair<float, float> res = fig::getMidPoint<Octagon<float>, float>(o);
    EXPECT_EQ(o.points, v15);
    EXPECT_EQ(res, center);
}

TEST(Octagon_float, double_cast) {
    Octagon<float> o(v15);
    float a = (float)o;
    float surf = fig::surface<Octagon<float>, float>(o);
    EXPECT_EQ(a, surf);
}

// Octagon int tests

std::vector<std::pair<int, int>> v17 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::vector<std::pair<int, int>> v18 = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon_int, empty_constructor) {
    Octagon<int> o;
    std::pair<int, int> center{0, 0};
    std::pair<int, int> res = fig::getMidPoint<Octagon<int>, int>(o);
    int surf = fig::surface<Octagon<int>, int>(o);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Octagon_int, vector_constructor) {
    Octagon<int> o(v17);
    std::pair<int, int> center{4, 4};
    std::pair<int, int> res = fig::getMidPoint<Octagon<int>, int>(o);
    EXPECT_EQ(o.points, v17);
    EXPECT_EQ(res, center);
}

TEST(Octagon_int, equality) {
    Octagon<int> o1(v17);
    Octagon<int> o2(v17);
    Octagon<int> o3(v18);
    EXPECT_EQ(o1, o2);
    EXPECT_FALSE(o1 == o3);
}

TEST(Octagon_int, copy) {
    Octagon<int> o1;
    Octagon<int> o2(v17);
    Octagon<int> o3(v18);
    o1 = o2;
    EXPECT_EQ(o1, o2);
    Octagon<int> o4;
    o4 = o1;
    o2 = o3;
    EXPECT_EQ(o1, o4);
}

TEST(Octagon_int, assignment) {
    Octagon<int> p;
    p = Octagon<int>(v17);
    std::pair<int, int> center{4, 4};
    std::pair<int, int> res = fig::getMidPoint<Octagon<int>, int>(p);
    EXPECT_EQ(p.points, v17);
    EXPECT_EQ(res, center);
}

TEST(Octagon_int, double_cast) {
    Octagon<int> o(v17);
    int a = (int)o;
    int surf = fig::surface<Octagon<int>, int>(o);
    EXPECT_EQ(a, surf);
}

// Array tests

TEST(Array, basic_constructor) {
    Array<Figure> a;

    for (size_t i = 0; i != 100; ++i)
        EXPECT_EQ(a[i], nullptr);
}

TEST(Array, size_conrtuctor) {
    Array<Figure> a(10);

    for (size_t i = 0; i != 10; ++i)
        EXPECT_EQ(a[i], nullptr);
}

TEST(Array, update_element) {
    Array<Figure> a(10);
    Pentagon<double>* p = new Pentagon<double>();
    a.update_figure(1, p);
    EXPECT_EQ(a[1], p);
    EXPECT_EQ(a[2], nullptr);
    EXPECT_EQ(a[0], nullptr);
}

TEST(Array, delete_element) {
    Array<Figure> a(10);
    Pentagon<double>* p = new Pentagon<double>();
    a.update_figure(1, p);
    EXPECT_EQ(a[1], p);
    a.delete_figure(1);
    EXPECT_EQ(a[1], nullptr);
}

TEST(Array, common_surface) {
    Array<Figure> a(2);
    Pentagon<double>* p1 = new Pentagon<double>();
    Pentagon<double>* p2 = new Pentagon<double>();
    a.update_figure(0, p1);
    a.update_figure(1, p2);
    EXPECT_EQ(a.common_surface(), 0.0);
}
```

### CMakeLists.txt
```cpp
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(Templates)

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

add_executable(main main.cpp)
add_executable(tests tests.cpp)
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
```