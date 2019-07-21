#include "gtest/gtest.h"
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/Stone.hpp>


using namespace SmashStone;
using namespace Games;
using namespace Models;
using namespace Utils;

TEST(PhysicsTest, UpdatePosition)
{
    Physics physics(0.0f, 0.0f);

    Stone black1(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(0.0f, 0.0f), Vector2D(0.0f, 0.0f));
    Stone black2(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(5.0f, 0.0f), Vector2D(0.0f, 0.0f));
    Stone black3(StoneColor::BLACK, 1.0f, 1.0f, Vector2D(10.0f, 0.0f), Vector2D(0.0f, 0.0f));

    Stone white1(StoneColor::WHITE, 1.0f, 1.0f, Vector2D(0.0f, 5.0f), Vector2D(0.0f, 0.0f));
    Stone white2(StoneColor::WHITE, 1.0f, 1.0f, Vector2D(5.0f, 5.0f), Vector2D(0.0f, 0.0f));
    Stone white3(StoneColor::WHITE, 1.0f, 1.0f, Vector2D(10.0f, 5.0f), Vector2D(0.0f, 0.0f));

    physics.AddStone(black1);
    physics.AddStone(black2);
    physics.AddStone(black3);
    physics.AddStone(white1);
    physics.AddStone(white2);
    physics.AddStone(white3);
}