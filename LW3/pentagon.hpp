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
    auto operator=(const Pentagon& other) const -> Pentagon&;

    explicit operator double() const;
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
    double x, y;
    std::pair<double, double> coordinates;
    for (size_t i = 0; i != 5; ++i) {
        is >> coordinates.first >> coordinates.second;
        p._points[i] = coordinates;
        p._mid_point.first += coordinates.first;
        p._mid_point.second += coordinates.second;
    }

    p._mid_point.first /= 5;
    p._mid_point.second /= 5;

    double side = std::sqrt(std::pow(p._points[0].first - p._points[1].first, 2) + std::pow(p._points[0].second - p._points[1].second, 2));
    double perimeter = 5 * side;
    double apotheme = side / (2 * std::tan(36));
    p._surface = perimeter * apotheme / 2;

    return is;
}