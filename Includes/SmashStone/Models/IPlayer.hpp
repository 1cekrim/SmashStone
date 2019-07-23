#ifndef SMASHSTONE_MODELS_IPLAYER_HPP
#define SMASHSTONE_MODELS_IPLAYER_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Enums/GameEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>

#include <functional>

namespace SmashStone::Models
{
struct Action
{
    int SelectedStoneIdx;
    Utils::Vector2D<float> velocity;

    Action() : SelectedStoneIdx(0), velocity(Utils::Vector2D<float>(0.0f, 0.0f))
    {
        // Do nothing
    }

    Action(int _SelectedStoneIdx, Utils::Vector2D<float> _velocity)
        : SelectedStoneIdx(_SelectedStoneIdx), velocity(_velocity)
    {
        // Do nothing
    }
};

class IPlayer
{
public:
    virtual void Ready(void) = 0; 
    virtual Action GetAction(void) = 0;
    virtual void TurnEnd(bool isMyTurn, TurnResult result) = 0;
    std::function<bool (std::vector<Utils::Vector2D<float>>)> PutStones;
    std::function<std::vector<Utils::Vector2D<float>> ()> GetMyStones;
    std::function<std::vector<Utils::Vector2D<float>> ()> GetOpStones;
    StoneColor color;
};
}  // namespace SmashStone::Models
#endif  // SMASHSTONE_MODELS_IPLAYER_HPP