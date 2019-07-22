#ifndef SMASHSTONE_GAMES_BOARDS_HPP
#define SMASHSTONE_GAMES_BOARDS_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/IPlayer.hpp>

#include <vector>

namespace SmashStone::Games
{
class Board
{
public:
    Board();
    Board(const float& height, const float& width);
    ~Board();

    void InitBoard(const float& friction, const float& elasticity);

    bool PutStones(StoneColor color, std::vector<Utils::Vector2D<float>> positions);

    bool CanPutHere(Utils::Vector2D<float> pos);

    std::vector<Utils::Vector2D<float>> GetStones(StoneColor color) const;
    template<class T>
    void SetPlayer(const int playerNumber);

    void PlayerReady(const int playerNumber);
    void PlayerDoAction(const int playerNumber);
    bool ProcessPhysics(const float dt);
    void DestroyOutBoundStone(void);
    bool CheckGameEnd(const int playerNumber);
    
    const float height, width;
    std::unique_ptr<Physics> physics;
    std::unique_ptr<Models::IPlayer> player1;
    std::unique_ptr<Models::IPlayer> player2;
};
}  // namespace SmashStone::Games
#endif  // SMASHSTONE_GAMES_BOARDS_HPP