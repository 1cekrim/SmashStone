#include <SmashStone/Models/Stone.hpp>

namespace SmashStone::Models
{
Stone::Stone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity)
: color(color), mass(mass), invMass(1 / mass), radius(radius), position(position), velocity(velocity)
{
    // Do nothing
}
}  // namespace SmashStone::Models