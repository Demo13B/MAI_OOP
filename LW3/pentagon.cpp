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
