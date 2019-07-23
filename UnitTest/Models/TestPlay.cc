#include <SmashStone/SmashStone.hpp>
#include <gtest/gtest.h>
#include <effolkronium/random.hpp>

using namespace SmashStone;
using namespace Utils;
using namespace Models;
using namespace Games;

using Random = effolkronium::random_static;

class AttackPlayer : public IPlayer
{
    void Ready(void)
    {
        std::vector<Vector2D<float>> stones;
        do
        {
            stones.clear();
            stones.reserve(8);
            for (int i = 1; i <= 8; i++)
            {
                stones.emplace_back(Random::get<float>(2.0f, 20.0f), Random::get<float>(0.0f, 45.0f));
            }
        } while (!PutStones(stones));
    }

    Action GetAction(void)
    {
        std::vector<Vector2D<float>> myList = GetMyStones();
        std::vector<Vector2D<float>> opList = GetOpStones();
        Action action;
        
        const int selected = Random::get<int>(0, myList.size() - 1);
        Vector2D dir = (opList.at(Random::get<int>(0, opList.size() - 1)) - myList.at(selected)).Normalized();
        
        const float speed = Random::get<float>(50.0f, 70.0f);

        return Action(selected, dir * speed);
    }

    void TurnEnd(bool isMyTurn, TurnResult result)
    {

    }
};

class AttackPlayer2 : public IPlayer
{
    void Ready(void)
    {
        std::vector<Vector2D<float>> stones;
        do
        {
            stones.clear();
            stones.reserve(8);
            for (int i = 1; i <= 8; i++)
            {
                stones.emplace_back(Random::get<float>(20.0f, 40.0f), Random::get<float>(0.0f, 45.0f));
            }
        } while (!PutStones(stones));
    }

    Action GetAction(void)
    {
        std::vector<Vector2D<float>> myList = GetMyStones();
        std::vector<Vector2D<float>> opList = GetOpStones();
        Action action;

        const int selected = Random::get<int>(0, myList.size() - 1);
        Vector2D dir = (opList.at(Random::get<int>(0, opList.size() - 1)) - myList.at(selected)).Normalized();

        const float speed = Random::get<float>(30.0f, 50.0f);

        return Action(selected, dir * speed);
    }

    void TurnEnd(bool isMyTurn, TurnResult result)
    {

    }
};

class DoNothingPlayer : public IPlayer
{
    void Ready(void)
    {
        std::vector<Vector2D<float>> stones;
        do
        {
            stones.clear();
            stones.reserve(8);
            for (int i = 1; i <= 8; i++)
            {
                stones.emplace_back(40.0f, Random::get<float>(0.0f, 45.0f));
            }
        } while (!PutStones(stones));
    }

    Action GetAction(void)
    {
        return Action(0, Vector2D<float>(0.0f, 0.0f));
    }

    void TurnEnd(bool isMyTurn, TurnResult result)
    {

    }
};

TEST(TESTPLAY, GUI_OFF)
{
    Game game(45.f, 42.f, 15.f, 0.5f, 0.0001f, 100);
    game.useGui = false;
    game.PlayGame<AttackPlayer, AttackPlayer2>();
}

TEST(TESTPLAY, GUI_ON)
{
    Game game(45.f, 42.f, 15.f, 0.5f, 0.0001f, 100);
    game.useGui = true;
    game.PlayGame<AttackPlayer, AttackPlayer2>();
}