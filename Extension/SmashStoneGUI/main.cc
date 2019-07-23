#include <SFML/Graphics.hpp>
#include <SmashStone/SmashStone.hpp>
#include <effolkronium/random.hpp>
#include <iostream>
#include "Constsants.hpp"

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
                stones.emplace_back(Random::get<float>(0.0f, 42.0f),
                                    Random::get<float>(0.0f, 45.0f));
            }
        } while (!PutStones(stones));
    }

    Action GetAction(void)
    {
        Action action;

        std::vector<Vector2D<float>> myList = GetMyStones();
        std::vector<Vector2D<float>> opList = GetOpStones();

        const int selected = Random::get<int>(0, myList.size() - 1);

        Vector2D dir = (opList.at(Random::get<int>(0, opList.size() - 1)) -
                        myList.at(selected))
                           .Normalized();

        const float speed = Random::get<float>(50.0f, 70.0f);

        return Action(selected, dir * speed);
    }

    void TurnEnd(bool isMyTurn, TurnResult result)
    {
        if (result == TurnResult::WIN)
        {
            if (isMyTurn)
            {
                std::cout << "Win! I'm smart!" << std::endl;
            }
            else
            {
                std::cout << "Win! You're stupid!" << std::endl;
			}
        }
        else if (result == TurnResult::LOSE)
        {
            if (isMyTurn)
            {
                std::cout << "Lose... I'm stupid..." << std::endl;
            }
            else
            {
                std::cout << "Lose... You're smart..." << std::endl;
            }
        }
        else if (result == TurnResult::DRAW)
        {
            std::cout << "Draw..?" << std::endl;
        }
    }
};

int main(void)
{
    Game game(45.f, 42.f, 35.f, 0.5f, 0.0001f, 100);
    game.useGui = true;
    game.PlayGame<AttackPlayer, AttackPlayer>();
    return 0;
}
