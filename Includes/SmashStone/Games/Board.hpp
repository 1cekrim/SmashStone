#ifndef SMASHSTONE_GAMES_BOARDS_HPP
#define SMASHSTONE_GAMES_BOARDS_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Games/Physics.hpp>

#include <vector>

namespace SmashStone::Games
{
class Board
{
public:
    Board() = delete;
    Board(const float& height, const float& width);

    void CheckOutBoundStone(void);

    const int GetStoneCount(const StoneColor& color) const;
    std::vector<Models::Stone> GetStones(const StoneColor& color) const;

    const float height, width;
    Physics* physics;
};
}  // namespace SmashStone::Games
#endif  // SMASHSTONE_GAMES_BOARDS_HPP