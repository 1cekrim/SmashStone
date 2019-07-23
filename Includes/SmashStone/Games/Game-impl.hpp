#ifndef SMASHSTONE_GAMES_GAME_IMPL_HPP
#define SMASHSTONE_GAMES_GAME_IMPL_HPP

#include <chrono>
#include <iostream>

#include <SmashStone/Enums/StoneEnums.hpp>

#include "Constsants.hpp"
#include <SFML/Graphics.hpp>

namespace SmashStone::Games
{
Game::Game(const float& height, const float& width, const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones)
    : board(height, width), friction(friction), elasticity(elasticity), treatStopVelocity(treatStopVelocity), maxStones(maxStones)
{

}

void MoveStone(sf::CircleShape& circle, Utils::Vector2D<float>& position)
{
    static const float CM2PX = 37.795276f * RESCALE_FACTOR;
    circle.setPosition((position.x_ + 1.1f) * CM2PX, (position.y_ - 1.1f) * CM2PX);
}

template <class T, class U>
void Game::PlayGame(void)
{
    board.InitBoard(friction, elasticity, treatStopVelocity, maxStones);

    board.SetPlayer<T>(1);
    board.SetPlayer<U>(2);

    if (useGui)
    {
        sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "SmashStoneGUI",
            sf::Style::Titlebar | sf::Style::Close);

        std::chrono::steady_clock::time_point pre, now;

        // Board
        sf::Texture board_Tex;
        if (!board_Tex.loadFromFile("Resource/board.png"))
        {
        }
        
        sf::Sprite board_Sprite;
        board_Sprite.setTexture(board_Tex);
        auto rect = board_Sprite.getTextureRect();
        board_Sprite.scale(sf::Vector2f(static_cast<float>(WIDTH) / rect.width,
                                    static_cast<float>(HEIGHT) / rect.height));
        
        board.PlayerReady(1);
        board.PlayerReady(2);

        bool isEnd = false;
        int nowPlayerNumber = 1;
        float dt = 0.0005f;
        pre = std::chrono::high_resolution_clock::now();
        while (window.isOpen() && !isEnd)
        {
            board.PlayerDoAction(nowPlayerNumber);
            do
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                }

                board.DestroyOutBoundStone();

                window.clear();
                window.draw(board_Sprite);

                auto blackStones = board.GetStones(StoneColor::BLACK);
                auto whiteStones = board.GetStones(StoneColor::WHITE);

                for (auto& stonePos : blackStones)
                {
                    sf::CircleShape circle(41.574803f * RESCALE_FACTOR);
                    circle.setFillColor(sf::Color::Black);
                    MoveStone(circle, stonePos);
                    window.draw(circle);
                }

                for (auto& stonePos : whiteStones)
                {
                    sf::CircleShape circle(41.574803f * RESCALE_FACTOR);
                    circle.setFillColor(sf::Color::White);
                    MoveStone(circle, stonePos);
                    window.draw(circle);
                }

                window.display();
                
                now = std::chrono::high_resolution_clock::now();
                dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - pre).count() * 1e-9;
                pre = now;
            } while (!board.ProcessPhysics(dt));
           
            isEnd = board.CheckGameEnd(nowPlayerNumber);

            nowPlayerNumber = (nowPlayerNumber == 1) ? 2 : 1; 
        }
    }
    else
    {
        bool isEnd = false;
        int nowPlayerNumber = 1;
        float dt = 0.0001f;

        board.PlayerReady(1);
        board.PlayerReady(2);

        while (!isEnd)
        {
            board.PlayerDoAction(nowPlayerNumber);

            do
            {
                board.DestroyOutBoundStone();
            } while (!board.ProcessPhysics(dt));

            isEnd = board.CheckGameEnd(nowPlayerNumber);

            nowPlayerNumber = (nowPlayerNumber == 1) ? 2 : 1; 
        }
    }
}
}
#endif  // SMASHSTONE_GAMES_GAME_IMPL_HPP