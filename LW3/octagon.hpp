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
