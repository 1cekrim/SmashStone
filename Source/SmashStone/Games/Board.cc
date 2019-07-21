#include <SmashStone/Games/Board.hpp>

namespace SmashStone::Games
{
Board::Board(const float& height, const float& width) : height(height), width(width)
{
    // pass
}
void Board::CheckOutBoundStone(void)
{
    // pass
}
const int Board::GetStoneCount(const StoneColor& color) const
{
    // pass
}
std::vector<Models::Stone> Board::GetStones(const StoneColor& color) const
{
    //pass
}
}