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

Octagon::operator double() const {
    return surface();
}
