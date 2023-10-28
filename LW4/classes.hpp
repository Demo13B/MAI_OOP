#pragma once
#include <utility>
#include <vector>

class Figure {};

template <typename T>
class Pentagon : public Figure {
    size_t size;
    std::vector<std::pair<T, T> > points;

    Pentagon()
        : size(5),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Pentagon(std::vector<std::pair<T, T> >& v)
        : size(5),
          points(v) {}

    ~Pentagon() {
        size = 0;
    }
};

template <typename T>
class Hexagon : public Figure {
    size_t size;
    std::vector<std::pair<T, T> > points;

    Hexagon()
        : size(6),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Hexagon(std::vector<std::pair<T, T> >& v)
        : size(6),
          points(v) {}

    ~Hexagon() {
        size = 0;
    }
};

template <typename T>
class Octagon : public Figure {
   public:
    size_t size;
    std::vector<std::pair<T, T> > points;

    Octagon<T>()
        : size(8),
          points({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}) {}

    Octagon<T>(std::vector<std::pair<T, T> >& v)
        : size(8),
          points(v) {}

    ~Octagon() {
        size = 0;
    }
};
