#include "seven.hpp"
#include <string>

Seven::Seven(const std::string& t) {
    this->size = 0;
    for (const unsigned char& digit : t) {
        this->value[size] = digit;
        ++size;
    }
}