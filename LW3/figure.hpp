#pragma once
#include <iostream>

class Figure {
   public:
    Figure() = default;
    virtual ~Figure() = default;

    virtual auto mid_point() const -> double = 0;
    virtual auto surface() const -> double = 0;

    virtual auto operator<<(const std::ostream& os) const -> std::ostream& = 0;
    virtual auto operator>>(const std::ostream& is) const -> std::istream& = 0;

    virtual auto operator==(const Figure& other) -> bool = 0;
    virtual auto operator=(const Figure& other) -> Figure& = 0;

    virtual explicit operator double() const = 0;
};