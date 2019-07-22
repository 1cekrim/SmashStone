#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Games/Physics.hpp>
#include <SmashStone/Models/Stone.hpp>
#include <iostream>
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
    std::vector<Models::Stone>& blackStones = stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = stones.at(StoneColor::WHITE);

    int num = 0;

    for (Models::Stone& bs : blackStones)
    {
        if (bs.velocity.Norm(2) < treatStopVelocity)
        {
            bs.velocity.x_ = 0;
            bs.velocity.y_ = 0;
            ++num;
        }
    }

    for (Models::Stone& ws : whiteStones)
    {
        if (ws.velocity.Norm(2) < treatStopVelocity)
        {
            ws.velocity.x_ = 0;
            ws.velocity.y_ = 0;
            ++num;
        }
    }
    if (num == (blackStones.size() + whiteStones.size()))
    {
        std::cout << "all stop" << std::endl;
        for (Manifold& mani : manifolds)
        {
            std::cout << "mani: " <<  mani.source.velocity << mani.target.velocity << std::endl;
        }
    }
    return num == (blackStones.size() + whiteStones.size());
}

void Physics::AffectFriction(const float& dt)
{
    std::vector<Models::Stone>& blackStones = stones.at(StoneColor::BLACK);
    std::vector<Models::Stone>& whiteStones = stones.at(StoneColor::WHITE);

    for (Models::Stone& bs : blackStones)
    {   
        if (bs.velocity.Norm(2) != 0)
        {
            if (bs.velocity.Norm(2) > friction * dt)
            {
                bs.velocity -= friction * bs.velocity.Normalized() * dt;
            }
            else
            {
                bs.velocity = Utils::Vector2D<float>(0.0f, 0.0f);
            }
        }
    }

    for (Models::Stone& ws : whiteStones)
    {
        if (ws.velocity.Norm(2) != 0)
        {
            if (ws.velocity.Norm(2) > friction * dt)
            {
                ws.velocity -= friction * ws.velocity.Normalized() * dt;
            }
            else
            {
                ws.velocity = Utils::Vector2D<float>(0.0f, 0.0f);
            }
            
        }
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

    stone.id = id++;

    for (Models::Stone& bs : blackStones)
    {
        if (bs.id != stone.id)
        {
            manifolds.emplace_back(stone, bs);
        }
    }
    
    for (Models::Stone& ws : whiteStones)
    {
        if (ws.id != stone.id)
        {
            manifolds.emplace_back(stone, ws);
        }
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

void Physics::PositionCorrection(Manifold& manifold)
{
    // const float percent = 0.2;
    // const float slop = 0.001;
    // const float c = (manifold.penetration > slop) ? (manifold.penetration - slop) : 0.0f;
    // std::cout << "Noncorrection: " << (manifold.source.position - manifold.target.position).Norm(2) << std::endl;
    // Utils::Vector2D<float> correction = c / (manifold.source.invMass + manifold.target.invMass) * percent * manifold.normal;

    // manifold.source.position -= manifold.source.invMass * correction;
    // manifold.target.position += manifold.target.invMass * correction;

    // std::cout << "correction: " << (manifold.source.position - manifold.target.position).Norm(2) << std::endl;
    Utils::Vector2D<float> midpoint = (manifold.target.position + manifold.source.position) / 2;

    std::cout << "before correction " << manifold.source.position << manifold.target.position << std::endl;

    manifold.source.position = midpoint - manifold.normal * manifold.source.radius;
    manifold.target.position = midpoint + manifold.normal * manifold.target.radius;

    std::cout << "after correction " << manifold.source.position << manifold.target.position << std::endl;
    std::cout << "after dist" << (manifold.source.position - manifold.target.position).Norm(2) << std::endl;
}

const bool Physics::UpdateManifold(Manifold& manifold) const
{
    if (manifold.source.isDestroyed || manifold.target.isDestroyed)
    {
        return false;
    }

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

void Physics::DoCrash(Manifold& manifold)
{
    Utils::Vector2D<float> rv = manifold.target.velocity - manifold.source.velocity;

    const float vn = rv.Dot(manifold.normal);
    if (vn > 0)
    {
        return;
    }
    std::cout << "crash, d: " << (manifold.source.position - manifold.target.position).Norm(2) << std::endl;
    const float j = -1 * (1 + elasticity) * vn / (manifold.source.invMass + manifold.target.invMass);
    
    const Utils::Vector2D<float> impulse = j * manifold.normal;

    std::cout << "bef source velo: " << manifold.source.velocity << "target velo: " << manifold.target.velocity << std::endl;

    manifold.source.velocity -= manifold.source.invMass * impulse;
    manifold.target.velocity += manifold.target.invMass * impulse;

    std::cout << "aft source velo: " << manifold.source.velocity << "target velo: " << manifold.target.velocity << std::endl;
    
    PositionCorrection((manifold));
}
}