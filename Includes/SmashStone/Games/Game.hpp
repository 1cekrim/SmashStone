#ifndef SMASHSTONE_GAMES_GAME_HPP
#define SMASHSTONE_GAMES_GAME_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Models/Stone.hpp>
#include <SmashStone/Games/Board.hpp>
#include <SmashStone/Games/Physics.hpp>

#include <vector>

namespace SmashStone::Games
{
class Game
{   
public:
    Game() = delete;

    Game(const float& height, const float& width, const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones);

    template <class T, class U>
    void PlayGame(void);

    Board board;
    bool useGui = false;
    float friction, elasticity, treatStopVelocity;
    int maxStones;
};
}  // namespace SmashStone::Games
#include <SmashStone/Games/Game-impl.hpp>
#endif  // SMASHSTONE_GAMES_GAME_HPP