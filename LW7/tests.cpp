#include <gtest/gtest.h>
#include <memory>
#include "dragon.hpp"
#include "elf.hpp"
#include "npc.hpp"
#include "wandering_knight.hpp"

TEST(elf_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(elf_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(elf_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);
    EXPECT_EQ(ElfType, a->get_type());
}

TEST(elf_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(elf_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Elf>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(elf_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Elf>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}

TEST(dragon_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(dragon_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(dragon_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);
    EXPECT_EQ(DragonType, a->get_type());
}

TEST(dragon_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(dragon_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Dragon>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(dragon_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Dragon>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}

TEST(knight_constructor, test1) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    EXPECT_EQ((a->position()).first, 100);
}

TEST(knight_constructor, test2) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    EXPECT_EQ((a->position()).second, 100);
}

TEST(knight_constructor, test3) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);
    EXPECT_EQ(KnightType, a->get_type());
}

TEST(knight_constructor, test4) {
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);
    EXPECT_TRUE(a->is_alive());
}

TEST(knight_constructor, test5) {
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Wandering_Knight>(x2, y2);
    EXPECT_TRUE(a->is_close(b, 100));
}

TEST(knight_constructor, test6) {
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Wandering_Knight>(x, y);

    a->move(50, 50, 100, 100);
    EXPECT_EQ((a->position()).first, 60);
}