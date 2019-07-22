#include <SmashStone/Games/Board.hpp>
#include <memory>
#include <iostream>
namespace SmashStone::Games
{
Board::Board(const float& height, const float& width) : height(height), width(width)
{
    // Do nothing
}

Board::Board() : Board(0.45f, 0.42f)
{
    // Do nothing
}

void Board::InitBoard(const float& friction, const float& elasticity)
{
    physics = std::make_unique<Physics>(friction, elasticity);
}

bool Board::PutStones(StoneColor color, std::vector<Utils::Vector2D<float>> positions)
{
    for (auto pos : positions)
    {
        if (!CanPutHere(pos))
        {
            return false;
        }
        physics.get()->AddStone(color, 0.041, 0.011, pos, Utils::Vector2D<float>(0, 0));
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
void Board::SetPlayer(const int& playerNumber)
{
    switch (playerNumber)
    {
        case 1:
            player1 = std::make_unique<T>();
            player1.get()->GetMyStones = std::bind(GetStones, StoneColor::BLACK);
            player1.get()->GetOpStones = std::bind(GetStones, StoneColor::WHITE);
            player1.get()->PutStones = std::bind(PutStones, StoneColor::BLACK, std::placeholders::_1);
            break;
        case 2:
            player2 = std::make_unique<T>();
            player2.get()->GetMyStones = std::bind(GetStones, StoneColor::WHITE);
            player2.get()->GetOpStones = std::bind(GetStones, StoneColor::BLACK);
            player2.get()->PutStones = std::bind(PutStones, StoneColor::WHITE, std::placeholders::_1);
            break;
        default:
            break;
    }
}

void Board::PlayerReady(const int& playerNumber)
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

void Board::PlayerDoAction(const int& playerNumber)
{
    switch (playerNumber)
    {
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}

void Board::DoActionAndWait(const int& playerNumber, Models::Action action)
{

}

void Board::DestroyOutBoundStone(void)
{

}

bool Board::CheckGameEnd(void)
{

}

std::vector<Models::Stone> Board::GetStones(StoneColor color) const
{
    
}
}