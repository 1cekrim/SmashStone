#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/Stone.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include "gtest/gtest.h"

#include <iostream>

using namespace SmashStone;
using namespace Games;
using namespace Models;
using namespace Utils;

TEST(PhysicsTest, UpdatePosition)
{
    Physics physics(0.0f, 0.0f, 0.01f);

    physics.AddStone(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(0.0f, 0.0f),
                     Vector2D(1.0f, 2.0f));
    physics.AddStone(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(0.0f, 2.0f),
                     Vector2D(1.0f, 2.0f));

    physics.AddStone(StoneColor::WHITE, 1.0f, 1.0f, Vector2D(5.0f, 5.0f),
                     Vector2D(1.0f, 2.0f));
    physics.AddStone(StoneColor::WHITE, 1.0f, 1.0f, Vector2D(10.0f, 5.0f),
                     Vector2D(1.0f, 2.0f));

    Stone& black1 = physics.stones.at(StoneColor::BLACK).at(0);
    Stone& black2 = physics.stones.at(StoneColor::BLACK).at(1);
    Stone& white1 = physics.stones.at(StoneColor::WHITE).at(0);
    Stone& white2 = physics.stones.at(StoneColor::WHITE).at(1);

    physics.UpdatePosition(1);

    EXPECT_EQ(physics.stones.at(StoneColor::BLACK).size(), 2);
    EXPECT_EQ(physics.stones.at(StoneColor::WHITE).size(), 2);

    EXPECT_EQ(black1.position, Vector2D<float>(1.0f, 2.0f));
    EXPECT_EQ(black2.position, Vector2D<float>(1.0f, 4.0f));
    EXPECT_EQ(white1.position, Vector2D<float>(6.0f, 7.0f));
    EXPECT_EQ(white2.position, Vector2D<float>(11.0f, 7.0f));

    physics.UpdatePosition(0.5f);

    EXPECT_EQ(black1.position, Vector2D<float>(1.5f, 3.0f));
    EXPECT_EQ(black2.position, Vector2D<float>(1.5f, 5.0f));
    EXPECT_EQ(white1.position, Vector2D<float>(6.5f, 8.0f));
    EXPECT_EQ(white2.position, Vector2D<float>(11.5f, 8.0f));
}

TEST(PhysicsTest, AffectFriction)
{
    Physics physics(1.0f, 0.0f, 0.01f);

    physics.AddStone(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(0.0f, 0.0f),
                     Vector2D(1.0f, 0.0f));

    Stone& black1 = physics.stones.at(StoneColor::BLACK).at(0);

    for (int i = 0; i < 100; i++)
    {
        physics.AffectFriction(0.01f);
        physics.UpdatePosition(0.01f);
        std::cout << "black1 vel: " << black1.velocity << "    "
                  << "pos: " << black1.position << std::endl;
    }
}

TEST(PhysicTest, CheckCrash)
{
    Physics physics(0.0f, 0.0f, 0.01f);

    physics.AddStone(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(0.0f, 0.0f),
                     Vector2D(0.0f, 0.0f));
    physics.AddStone(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(1.0f, 2.2f),
                     Vector2D(0.0f, -1.0f));

	Stone& black1 = physics.stones.at(StoneColor::BLACK).at(0);
    Stone& black2 = physics.stones.at(StoneColor::BLACK).at(1);

	for (int i = 0; i < 100; i++)
    {
        physics.UpdatePosition(0.01f);
        physics.CheckCrash();
        std::cout << "black1 vel: " << black1.velocity << "    "
                  << "pos: " << black1.position << std::endl;
        std::cout << "black2 vel: " << black2.velocity << "    "
                  << "pos: " << black2.position << std::endl << std::endl;
    }
}