#include "dragon.hpp"
#include "elf.hpp"
#include "wandering_knight.hpp"

Dragon::Dragon(int x, int y)
    : NPC(DragonType, x, y) {}
Dragon::Dragon(std::istream& is)
    : NPC(DragonType, is) {}

bool Dragon::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Dragon>(this, [](Dragon*) {}));
}

void Dragon::print() {
    std::cout << *this;
}

bool Dragon::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, true);
    return false;
}

bool Dragon::fight(std::shared_ptr<Wandering_Knight> other) {
    fight_notify(other, true);
    return false;
}

bool Dragon::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, true);
    return false;
}

void Dragon::save(std::ostream& os) {
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Dragon& dragon) {
    os << "dragon: " << *static_cast<NPC*>(&dragon) << std::endl;
    return os;
}