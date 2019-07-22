#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/Stone.hpp>

namespace SmashStone::Games
{
Physics::Physics(const float& friction, const float& elasticity)
    : friction(friction), elasticity(elasticity)
{
    stones.emplace(std::piecewise_construct, std::make_tuple(StoneColor::BLACK), std::make_tuple());
    stones.emplace(std::piecewise_construct, std::make_tuple(StoneColor::WHITE), std::make_tuple());
}

void Physics::Update(const float& dt)
{
    //change velocity functions
    AffectFriction(dt);

    //change position functions
    UpdatePosition(dt);

    //check crash functions
    CheckCrash();
}

void Physics::AffectFriction(const float& dt)
{
    std::vector<Models::Stone>& blackStones = stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = stones.at(StoneColor::WHITE);

    for (Models::Stone& bs : blackStones)
    {
        bs.velocity -= friction * bs.velocity.Normalized() * dt;
    }

    for (Models::Stone& ws : whiteStones)
    {
        ws.velocity -= friction * ws.velocity.Normalized() * dt;
    }
}

void Physics::UpdatePosition(const float& dt)
{
    std::vector<Models::Stone>& blackStones = stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = stones.at(StoneColor::WHITE);

    for (Models::Stone& bs : blackStones)
    {
        bs.position += bs.velocity * dt;
    }

    for (Models::Stone& ws : whiteStones)
    {
        ws.position += ws.velocity * dt;
    }
}

const int Physics::AddStone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity)
{
    std::vector<Models::Stone>& blackStones = stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = stones.at(StoneColor::WHITE);

    std::vector<Models::Stone>& sameColorStones = stones.at(color);
    sameColorStones.emplace_back(color, mass, radius, position, velocity);

    Models::Stone& stone = sameColorStones.back();

    for (Models::Stone& bs : blackStones)
    {
        manifolds.emplace_back(stone, bs);
    }

    for (Models::Stone& ws : whiteStones)
    {
        manifolds.emplace_back(stone, ws);
    }
    return sameColorStones.size() - 1;
}

void Physics::CheckCrash(void)
{
    for (Manifold& manifold : manifolds)
    {
        if (UpdateManifold(manifold))
        {
            DoCrash(manifold);
        }
    }
}

const bool Physics::UpdateManifold(Manifold& manifold) const
{
    Models::Stone& source = manifold.source;
    Models::Stone& target = manifold.target;

    Utils::Vector2D<float> dir = target.position - source.position;

    const float d = dir.Norm(2);
    const float r = source.radius + target.radius;

    if (r < d)
    {
        return false;
    }

    if (d != 0)
    {
        manifold.penetration = r - d;
        manifold.normal = dir / d;
        
        return true;
    }
    else
    {
        manifold.penetration = source.radius;
        manifold.normal = Utils::Vector2D<float>(1.0f, 0.0f);
        return true;
    }
}

void Physics::DoCrash(Manifold& manifold) const
{
    Utils::Vector2D<float> rv = manifold.target.velocity - manifold.source.velocity;

    const float vn = rv.Dot(manifold.normal);
    if (vn > 0)
    {
        return;
    }

    const float j = -1 * (1 + elasticity) * vn / (manifold.source.invMass + manifold.target.invMass);

    const Utils::Vector2D<float> impulse = j * manifold.normal;

    manifold.source.velocity -= manifold.source.invMass * impulse;
    manifold.target.velocity += manifold.target.invMass * impulse;
}
}