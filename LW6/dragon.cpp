#include "dragon.hpp"
#include <algorithm>
#include "elf.hpp"
#include "wandering_knight.hpp"

Dragon::Dragon(const int& _x, const int& _y, const std::string& _name) {
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Dragon::print(std::ostream& out) {
    out << *this;
}

void Dragon::accept(NPC* attacker, const int& distance) {
    if (alive && (dynamic_cast<Wandering_Knight*>(attacker) || (dynamic_cast<Dragon*>(attacker) && attacker != this))) {
        bool win = is_close(*attacker, distance);
        if (win)
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Dragon& other) {
    return out << "Dragon " << other.name << " {" << other.x << ", " << other.y << '}';
}