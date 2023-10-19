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
