#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>
#include "NPC.hpp"
#include "dragon.hpp"
#include "elf.hpp"
#include "factory.hpp"
#include "wandering_knight.hpp"

TEST(Constructors, Dragon) {
    Dragon s(0, 0, "Belthromar");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Dragon Belthromar {0, 0}");
}

TEST(Constructors, Wandering_Knight) {
    Wandering_Knight t(1, 1, "Emilia");
    std::stringstream out;
    t.print(out);
    ASSERT_EQ(out.str(), "Wandering Knight Emilia {1, 1}");
}

TEST(Constructors, Elf) {
    Elf e(2, 2, "Dobby");
    std::stringstream out;
    e.print(out);
    ASSERT_EQ(out.str(), "Elf Dobby {2, 2}");
}

TEST(Factory, basic) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Dragon", "Belthromar", 0, 0));
    persons.push_back(factory("Wandering_Knight", "Emilia", 1, 1));
    persons.push_back(factory("Elf", "Dobby", 2, 2));

    std::stringstream out;

    for (auto& elem : persons) {
        elem->print(out);
    }

    ASSERT_EQ(out.str(), "Dragon Belthromar {0, 0}Wandering Knight Emilia {1, 1}Elf Dobby {2, 2}");
}

TEST(Fighting, everybody_dies) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Dragon", "Belthromar", 0, 0));
    persons.push_back(factory("Wandering_Knight", "Emilia", 1, 1));
    persons.push_back(factory("Elf", "Dobby", 2, 2));

    for (auto& defender : persons) {
        for (auto& attacker : persons) {
            defender->accept(attacker.get(), 4);
        }
    }

    for (auto& elem : persons) {
        ASSERT_FALSE(elem->is_alive());
    }
}

TEST(Fighting, Dragon_survives) {
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Dragon", "Belthromar", 100, 100));
    persons.push_back(factory("Wandering_Knight", "Emilia", 1, 1));
    persons.push_back(factory("Elf", "Dobby", 2, 2));

    for (auto& defender : persons) {
        for (auto& attacker : persons) {
            defender->accept(attacker.get(), 4);
        }
    }

    for (size_t i = 0; i != persons.size(); ++i) {
        if (i != 1) {
            EXPECT_TRUE(persons[i]->is_alive());
        } else {
            EXPECT_FALSE(persons[i]->is_alive());
        }
    }
}