#include <gtest/gtest.h>
#include "Vec2.hpp"

TEST(Vec2Test, Addition)
{
    Math::Vec2<float> a(1.f, 2.f);
    Math::Vec2<float> b(3.f, 4.f);

    auto r = a + b;

    EXPECT_FLOAT_EQ(r.x(), 4.f);
    EXPECT_FLOAT_EQ(r.y(), 6.f);
}

TEST(Vec2Test, Normalization)
{
    Math::Vec2<float> v(3.f, 4.f);
    auto n = v.Normalized();

    EXPECT_NEAR(n.x(), 0.6f, 0.001f);
    EXPECT_NEAR(n.y(), 0.8f, 0.001f);
}