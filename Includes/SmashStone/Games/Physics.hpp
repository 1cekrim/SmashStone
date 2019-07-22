#ifndef SMASHSTONE_GAMES_PHYSICS_HPP
#define SMASHSTONE_GAMES_PHYSICS_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Models/Stone.hpp>

#include <vector>
#include <map>

namespace SmashStone::Games
{
struct Manifold
{
    Models::Stone& source;
    Models::Stone& target;
    float penetration;
    Utils::Vector2D<float> normal;

    Manifold(Models::Stone& source, Models::Stone& target) : source(source), target(target), penetration(0.0f), normal(0.0f, 0.0f)
    {
        // Do nothing
    }
};

class Physics
{   
public:
    Physics() = delete;
    Physics(const float& friction, const float& elasticity);

    void Update(const float& dt);
    void AffectFriction(const float& dt);
    void UpdatePosition(const float& dt);
    void CheckCrash(void);
    const bool UpdateManifold(Manifold& manifold) const;

    void DoCrash(Manifold& manifold) const;

    void DeleteStone(const int& id);
    const int AddStone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity);

    float friction, elasticity;
    std::vector<Manifold> manifolds;
    std::map<StoneColor, std::vector<Models::Stone>> stones;
};
}  // namespace SmashStone::Games
#endif  // SMASHSTONE_GAMES_PHYSICS_HPP