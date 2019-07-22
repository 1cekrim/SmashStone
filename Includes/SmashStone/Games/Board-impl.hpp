#ifndef SMASHSTONE_GAMES_BOARD_IMPL_HPP
#define SMASHSTONE_GAMES_BOARD_IMPL_HPP

#include <SmashStone/Enums/GameEnums.hpp>
#include <memory>
#include <iostream>
namespace SmashStone::Games
{
Board::Board(const float& height, const float& width) : height(height), width(width)
{
    // Do nothing
}

Board::Board() : Board(45.0f, 42.0f)
{
    // Do nothing
}

void Board::InitBoard(const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones)
{
    physics = std::make_unique<Physics>(friction, elasticity, treatStopVelocity, maxStones);
}

bool Board::PutStones(StoneColor color, std::vector<Utils::Vector2D<float>> positions)
{
    std::cout << "putstones start" << std::endl;

    for (auto pos : positions)
    {
        if (!CanPutHere(pos))
        {
            return false;
        }
    }
    for (auto pos : positions)
    {
        std::cout << pos << std::endl; 
        physics.get()->AddStone(color, 0.041f, 1.1f, pos, Utils::Vector2D<float>(0, 0));
    }
    return true;
}

bool Board::CanPutHere(Utils::Vector2D<float> pos)
{
    if (pos.x_ < 0 || pos.y_ < 0 || pos.x_ > width || pos.y_ > height)
    {
        return false;
    }

    for (auto& stone : physics.get()->stones.at(StoneColor::BLACK))
    {
        const float r = stone.radius * 2;
        const float d = (pos - stone.position).Norm(2);

        if (d < r)
        {
            return false;
        }
    }

    for (auto& stone : physics.get()->stones.at(StoneColor::WHITE))
    {
        const float r = stone.radius * 2;
        const float d = (pos - stone.position).Norm(2);

        if (d < r)
        {
            return false;
        }
    }

    return true;
}
std::function<bool (std::vector<Utils::Vector2D<float>>)> PutStones;
template<class T>
void Board::SetPlayer(const int playerNumber)
{
    switch (playerNumber)
    {
        case 1:
            player1 = std::unique_ptr<Models::IPlayer>(new T());

            player1.get()->GetMyStones = [this]()->auto{
                return this->GetStones(StoneColor::BLACK);
            };

            player1.get()->GetOpStones = [this]()->auto{
                return this->GetStones(StoneColor::WHITE);
            };

            player1.get()->PutStones = [this](auto i)->auto{
                return this->PutStones(StoneColor::BLACK, i);
            };
            break;
        case 2:
            player2 = std::unique_ptr<Models::IPlayer>(new T());

            player2.get()->GetMyStones = [this]()->auto{
                return this->GetStones(StoneColor::WHITE);
            };

            player2.get()->GetOpStones = [this]()->auto{
                return this->GetStones(StoneColor::BLACK);
            };

            player2.get()->PutStones = [this](auto i)->auto{
                return this->PutStones(StoneColor::WHITE, i);
            };
            break;
        default:
            break;
    }
}

void Board::PlayerReady(const int playerNumber)
{
    switch (playerNumber)
    {
    case 1:
        player1.get()->Ready();
        break;
    case 2:
        player2.get()->Ready();
        break;
    default:
        break;
    }
}

void Board::PlayerDoAction(const int playerNumber)
{
    switch (playerNumber)
    {
    case 1:
    {
        auto action = player1.get()->GetAction();
        physics.get()->stones.at(StoneColor::BLACK).at(action.SelectedStoneIdx).velocity = action.velocity;
        std::cout << "player1 action: " << action.SelectedStoneIdx << " change speed " << action.velocity << std::endl;
        break;
    }
    case 2:
    {
        auto action = player2.get()->GetAction();
        physics.get()->stones.at(StoneColor::WHITE).at(action.SelectedStoneIdx).velocity = action.velocity;
        std::cout << "player2 action: " << action.SelectedStoneIdx << " change speed " << action.velocity << std::endl;
        break;
    }
    default:
        break;
    }
}

bool Board::ProcessPhysics(const float dt)
{
    //std::cout << "dist: " << (physics.get()->stones.at(StoneColor::BLACK).at(0).position - physics.get()->stones.at(StoneColor::WHITE).at(0).position).Norm(2) << std::endl;
    return physics.get()->Update(dt);
}

void Board::DestroyOutBoundStone(void)
{
    std::vector<Models::Stone>& blackStones = physics.get()->stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = physics.get()->stones.at(StoneColor::WHITE);

    for (auto stone = blackStones.begin(); stone != blackStones.end();)
    {
        const float x = stone->position.x_;
        const float y = stone->position.y_;

        if (x < 0 || y < 0 || x > width || y > height)
        {
            stone = blackStones.erase(stone);
            stone->isDestroyed = true;
        }
        else
        {
            ++stone;
        }
    }

    for (auto stone = whiteStones.begin(); stone != whiteStones.end();)
    {
        const float x = stone->position.x_;
        const float y = stone->position.y_;
        
        if (x < 0 || y < 0 || x > width || y > height)
        {
            stone = whiteStones.erase(stone);
            stone->isDestroyed = true;
        }
        else
        {
            ++stone;
        }
    }
}

bool Board::CheckGameEnd(const int playerNumber)
{
    const int blackCount = physics.get()->stones.at(StoneColor::BLACK).size();
    const int whiteCount = physics.get()->stones.at(StoneColor::WHITE).size();

    if (blackCount == 0 && whiteCount == 0)
    {
        player1.get()->TurnEnd(playerNumber == 1, TurnResult::DRAW);
        player2.get()->TurnEnd(playerNumber == 2, TurnResult::DRAW);

        return true;
    }

    if (blackCount == 0)
    {
        player1.get()->TurnEnd(playerNumber == 1, TurnResult::LOSE);
        player2.get()->TurnEnd(playerNumber == 2, TurnResult::WIN);
        
        return true;
    }

    if (whiteCount == 0)
    {
        player1.get()->TurnEnd(playerNumber == 1, TurnResult::WIN);
        player2.get()->TurnEnd(playerNumber == 2, TurnResult::LOSE);

        return true;
    }

    player1.get()->TurnEnd(playerNumber == 1, TurnResult::NOPE);
    player2.get()->TurnEnd(playerNumber == 2, TurnResult::NOPE);

    return false;
}

std::vector<Utils::Vector2D<float>> Board::GetStones(StoneColor color) const
{
    std::vector<Utils::Vector2D<float>> stones;
    stones.reserve(physics.get()->stones.at(color).size());

    for (Models::Stone& stone : physics.get()->stones.at(color))
    {
        stones.push_back(stone.position);
    }

    return stones;
}
}
#endif  // SMASHSTONE_GAMES_BOARD_IMPL_HPP