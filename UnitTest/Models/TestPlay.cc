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
            stones.reserve(2);
            for (int i = 1; i <= 2; i++)
            {
                stones.emplace_back(5.0f, Random::get<float>(0.0f, 45.0f));
            }
        } while (!PutStones(stones));
    }

    Action GetAction(void)
    {
        std::vector<Vector2D<float>> myList = GetMyStones();
        std::vector<Vector2D<float>> opList = GetOpStones();
        Action action;

        Vector2D dir = (opList.at(0) - myList.at(0)).Normalized();
        const float speed = 20.0f;

        return Action(0, dir * speed);
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
            stones.reserve(2);
            for (int i = 1; i <= 2; i++)
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

TEST(TESTPLAY, TEST1)
{
    Board board;
    board.InitBoard(1.0f, 1.0f, 0.0001f, 100);

    board.SetPlayer<AttackPlayer>(1);
    board.SetPlayer<DoNothingPlayer>(2);

    board.PlayerReady(1);

    board.PlayerReady(2);

    bool isEnd = false;
    int now = 1;

    while (!isEnd)
    {
        board.PlayerDoAction(now);

        while (!board.ProcessPhysics(0.01f));

        board.DestroyOutBoundStone();

        isEnd = board.CheckGameEnd(now);

        now = (now == 1) ? 2 : 1;
    }

    EXPECT_TRUE((board.GetStones(StoneColor::WHITE).size() == 0 || board.GetStones(StoneColor::BLACK).size() == 0));
}