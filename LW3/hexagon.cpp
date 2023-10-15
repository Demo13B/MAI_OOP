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

Hexagon::operator double() const {
    return surface();
}
