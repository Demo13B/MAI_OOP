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