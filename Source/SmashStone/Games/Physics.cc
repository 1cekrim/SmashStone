#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/Stone.hpp>

namespace SmashStone::Games
{
Physics::Physics(const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones)
    : friction(friction), elasticity(elasticity), treatStopVelocity(treatStopVelocity)
{
    stones.emplace(std::piecewise_construct, std::make_tuple(StoneColor::BLACK), std::make_tuple());
    stones.emplace(std::piecewise_construct, std::make_tuple(StoneColor::WHITE), std::make_tuple());
    
    stones.at(StoneColor::BLACK).reserve(maxStones);
    stones.at(StoneColor::WHITE).reserve(maxStones);
}

bool Physics::Update(const float& dt)
{
    //change velocity functions
    AffectFriction(dt);

    //change position functions
    UpdatePosition(dt);

    //check crash functions
    CheckCrash();

    return CheckAllStop();
}

bool Physics::CheckAllStop(void)
{
    auto& blackStones = stones.at(StoneColor::BLACK);
    auto& whiteStones = stones.at(StoneColor::WHITE);

    int num = 0;

    for (auto& bs : blackStones)
    {
        if (bs->velocity.Norm(2) < treatStopVelocity)
        {
            bs->velocity.x_ = 0;
            bs->velocity.y_ = 0;
            ++num;
        }
    }

    for (auto& ws : whiteStones)
    {
        if (ws->velocity.Norm(2) < treatStopVelocity)
        {
            ws->velocity.x_ = 0;
            ws->velocity.y_ = 0;
            ++num;
        }
    }

    return num == (blackStones.size() + whiteStones.size());
}

void Physics::AffectFriction(const float& dt)
{
    auto& blackStones = stones.at(StoneColor::BLACK);
    auto& whiteStones = stones.at(StoneColor::WHITE);

    for (auto& bs : blackStones)
    {   
        if (bs->velocity.Norm(2) != 0)
        {
            if (bs->velocity.Norm(2) > friction * dt)
            {
                bs->velocity -= friction * bs->velocity.Normalized() * dt;
            }
            else
            {
                bs->velocity = Utils::Vector2D<float>(0.0f, 0.0f);
            }
        }
    }

    for (auto& ws : whiteStones)
    {
        if (ws->velocity.Norm(2) != 0)
        {
            if (ws->velocity.Norm(2) > friction * dt)
            {
                ws->velocity -= friction * ws->velocity.Normalized() * dt;
            }
            else
            {
                ws->velocity = Utils::Vector2D<float>(0.0f, 0.0f);
            }
        }
    }
}

void Physics::UpdatePosition(const float& dt)
{
    auto& blackStones = stones.at(StoneColor::BLACK);
    auto& whiteStones = stones.at(StoneColor::WHITE);

    for (auto& bs : blackStones)
    {
        bs->position += bs->velocity * dt;
    }

    for (auto& ws : whiteStones)
    {
        ws->position += ws->velocity * dt;
    }
}

Models::Stone& Physics::AddStone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity)
{
    auto& blackStones = stones.at(StoneColor::BLACK);
    auto& whiteStones = stones.at(StoneColor::WHITE);
    auto& sameColorStones = stones.at(color);

    std::shared_ptr<Models::Stone> stone = std::make_shared<Models::Stone>(color, mass, radius, position, velocity);

    sameColorStones.push_back(stone);

    stone->id = id++;

    for (auto& bs : blackStones)
    {
        if (bs->id != stone->id)
        {
            manifolds.emplace_back(stone, bs);
        }
    }
    
    for (auto& ws : whiteStones)
    {
        if (ws->id != stone->id)
        {
            manifolds.emplace_back(stone, ws);
        }
    }
    
    return *stone;
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

void Physics::PositionCorrection(Manifold& manifold)
{
    Utils::Vector2D<float> midpoint = (manifold.target->position + manifold.source->position) / 2;

    manifold.source->position = midpoint - manifold.normal * manifold.source->radius;
    manifold.target->position = midpoint + manifold.normal * manifold.target->radius;
}

const bool Physics::UpdateManifold(Manifold& manifold) const
{
    if (manifold.source->isDestroyed || manifold.target->isDestroyed)
    {
         return false;
    }

    auto& source = manifold.source;
    auto& target = manifold.target;

    Utils::Vector2D<float> dir = target->position - source->position;

    const float d = dir.Norm(2);
    const float r = source->radius + target->radius;

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
        manifold.penetration = source->radius;
        manifold.normal = Utils::Vector2D<float>(1.0f, 0.0f);
        return true;
    }
}

void Physics::DoCrash(Manifold& manifold)
{
    Utils::Vector2D<float> rv = manifold.target->velocity - manifold.source->velocity;

    const float vn = rv.Dot(manifold.normal);
    if (vn > 0)
    {
        return;
    }

    const float j = -1 * (1 + elasticity) * vn / (manifold.source->invMass + manifold.target->invMass);
    
    const Utils::Vector2D<float> impulse = j * manifold.normal;

    manifold.source->velocity -= manifold.source->invMass * impulse;
    manifold.target->velocity += manifold.target->invMass * impulse;
    
    PositionCorrection((manifold));
}
}