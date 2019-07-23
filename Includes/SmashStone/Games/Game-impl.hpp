#ifndef SMASHSTONE_GAMES_GAME_IMPL_HPP
#define SMASHSTONE_GAMES_GAME_IMPL_HPP

#include <chrono>
#include <iostream>
namespace SmashStone::Games
{
Game::Game(const float& height, const float& width, const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones)
    : board(height, width), friction(friction), elasticity(elasticity), treatStopVelocity(treatStopVelocity), maxStones(maxStones)
{

}

template <class T, class U>
void Game::PlayGame(void)
{
    // std::chrono::steady_clock::time_point pre, now;

    board.InitBoard(friction, elasticity, treatStopVelocity, maxStones);

    board.SetPlayer<T>(1);
    board.SetPlayer<U>(2);

    board.PlayerReady(1);
    board.PlayerReady(2);

    // pre = std::chrono::high_resolution_clock::now();

    if (useGui)
    {
        // use GUI
    }
    else
    {
        bool isEnd = false;
        int nowPlayerNumber = 1;
        float dt = 0.0001f;

        while (!isEnd)
        {
            board.PlayerDoAction(nowPlayerNumber);

            do
            {
                // now = std::chrono::high_resolution_clock::now();
                // dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - pre).count() * 1e-9;
                // pre = now;
            } while (!board.ProcessPhysics(dt));

            board.DestroyOutBoundStone();
           
            isEnd = board.CheckGameEnd(nowPlayerNumber);

            nowPlayerNumber = (nowPlayerNumber == 1) ? 2 : 1; 
        }
    }
}
}
#endif  // SMASHSTONE_GAMES_GAME_IMPL_HPP