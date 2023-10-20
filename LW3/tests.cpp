#include <gtest/gtest.h>
#include "array.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"

std::vector<std::pair<double, double>> v1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
std::vector<std::pair<double, double>> v2 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

TEST(Pentagon, empty_constructor) {
    Pentagon p;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(p.mid_point(), center);
    EXPECT_EQ(p.surface(), 0);
}

TEST(Pentagon, vector_constructor) {
    Pentagon p(v1);
    std::pair<double, double> center{3, 3};
    EXPECT_EQ(p.get_points(), v1);
    EXPECT_EQ(p.mid_point(), center);
}

TEST(Pentagon, equality) {
    Pentagon p1(v1);
    Pentagon p2(v1);
    Pentagon p3(v2);
    EXPECT_EQ(p1, p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Pentagon, copy) {
    Pentagon p1;
    Pentagon p2(v1);
    Pentagon p3(v2);
    p1 = p2;
    EXPECT_EQ(p1, p2);
    Pentagon p4;
    p4 = p1;
    p2 = p3;
    EXPECT_EQ(p1, p4);
}

TEST(Pentagon, assignment) {
    Pentagon p;
    p = Pentagon(v1);
    std::pair<double, double> center{3, 3};
    EXPECT_EQ(p.get_points(), v1);
    EXPECT_EQ(p.mid_point(), center);
}

TEST(Pentagon, double_cast) {
    Pentagon p(v1);
    double a = (double)p;
    EXPECT_EQ(a, p.surface());
}

std::vector<std::pair<double, double>> v3 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::vector<std::pair<double, double>> v4 = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon, empty_constructor) {
    Hexagon h;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(h.mid_point(), center);
    EXPECT_EQ(h.surface(), 0);
}

TEST(Hexagon, vector_constructor) {
    Hexagon h(v3);
    std::pair<double, double> center{3.5, 3.5};
    EXPECT_EQ(h.get_points(), v3);
    EXPECT_EQ(h.mid_point(), center);
}

TEST(Hexagon, equality) {
    Hexagon h1(v3);
    Hexagon h2(v3);
    Hexagon h3(v4);
    EXPECT_EQ(h1, h2);
    EXPECT_FALSE(h1 == h3);
}

TEST(Hexagon, copy) {
    Hexagon h1;
    Hexagon h2(v3);
    Hexagon h3(v4);
    h1 = h2;
    EXPECT_EQ(h1, h2);
    Hexagon h4;
    h4 = h1;
    h2 = h3;
    EXPECT_EQ(h1, h4);
}

TEST(Hexagon, assignment) {
    Hexagon h;
    h = Hexagon(v3);
    std::pair<double, double> center{3.5, 3.5};
    EXPECT_EQ(h.get_points(), v3);
    EXPECT_EQ(h.mid_point(), center);
}

TEST(Hexagon, double_cast) {
    Hexagon h(v3);
    double a = (double)h;
    EXPECT_EQ(a, h.surface());
}

std::vector<std::pair<double, double>> v5 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::vector<std::pair<double, double>> v6 = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon, empty_constructor) {
    Octagon o;
    std::pair<double, double> center{0, 0};
    EXPECT_EQ(o.mid_point(), center);
    EXPECT_EQ(o.surface(), 0);
}

TEST(Octagon, vector_constructor) {
    Octagon o(v5);
    std::pair<double, double> center{4.5, 4.5};
    EXPECT_EQ(o.get_points(), v5);
    EXPECT_EQ(o.mid_point(), center);
}

TEST(Octagon, equality) {
    Octagon o1(v5);
    Octagon o2(v5);
    Octagon o3(v6);
    EXPECT_EQ(o1, o2);
    EXPECT_FALSE(o1 == o3);
}

TEST(Octagon, copy) {
    Octagon o1;
    Octagon o2(v5);
    Octagon o3(v6);
    o1 = o2;
    EXPECT_EQ(o1, o2);
    Octagon o4;
    o4 = o1;
    o2 = o3;
    EXPECT_EQ(o1, o4);
}

TEST(Octagon, assignment) {
    Octagon o;
    o = Octagon(v5);
    std::pair<double, double> center{4.5, 4.5};
    EXPECT_EQ(o.get_points(), v5);
    EXPECT_EQ(o.mid_point(), center);
}

TEST(Octagon, double_cast) {
    Octagon o(v5);
    double a = (double)o;
    EXPECT_EQ(a, o.surface());
}

TEST(Array, basic_constructor) {
    Array a;

    for (size_t i = 0; i != 100; ++i)
        EXPECT_EQ(a[i], nullptr);
}

TEST(Array, size_conrtuctor) {
    Array a(10);

    for (size_t i = 0; i != 10; ++i)
        EXPECT_EQ(a[i], nullptr);
}

TEST(Array, update_element) {
    Array a(10);
    Pentagon p;
    a.update_figure(1, &p);
    EXPECT_EQ(a[1], &p);
    EXPECT_EQ(a[2], nullptr);
    EXPECT_EQ(a[0], nullptr);
}

TEST(Array, delete_element) {
    Array a(10);
    Pentagon* p = new Pentagon();
    a.update_figure(1, p);
    EXPECT_EQ(a[1], p);
    a.delete_figure(1);
    EXPECT_EQ(a[1], nullptr);
}

TEST(Array, common_surface) {
    Array a(2);
    Pentagon* p1 = new Pentagon();
    Pentagon* p2 = new Pentagon();
    a.update_figure(0, p1);
    a.update_figure(1, p2);
    EXPECT_EQ(a.common_surface(), 0.0);
}