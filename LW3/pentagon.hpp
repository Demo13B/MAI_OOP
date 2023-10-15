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

    // explicit operator double() const override;
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
    double x, y;
    for (size_t i = 0; i != 5; ++i) {
        is >> v[i].first >> v[i].second;
    }

    p = Pentagon(v);

    return is;
}