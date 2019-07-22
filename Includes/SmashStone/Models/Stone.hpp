#ifndef SMASHSTONE_MODELS_STONE_HPP
#define SMASHSTONE_MODELS_STONE_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>

namespace SmashStone::Models
{
class Stone
{
public:
    Stone() = delete;
    Stone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity);
    StoneColor color;
    float mass, radius, invMass;
    Utils::Vector2D<float> position, velocity;
};
}  // namespace SmashStone::Models
#endif  // SMASHSTONE_MODELS_STONE_HPP