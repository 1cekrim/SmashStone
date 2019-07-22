#ifndef SMASHSTONE_GAMES_PHYSICS_HPP
#define SMASHSTONE_GAMES_PHYSICS_HPP

#include <SmashStone/Enums/StoneEnums.hpp>
#include <SmashStone/Utils/Vector2D.hpp>
#include <SmashStone/Models/Stone.hpp>

#include <vector>
#include <map>
#include <memory>

namespace SmashStone::Games
{
struct Manifold
{
    std::shared_ptr<Models::Stone> source;
    std::shared_ptr<Models::Stone> target;
    float penetration;
    Utils::Vector2D<float> normal;

    Manifold(std::shared_ptr<Models::Stone>& source, std::shared_ptr<Models::Stone>& target)
        : source(source), target(target), penetration(0.0f), normal(0.0f, 0.0f)
    {
        // Do nothing
    }
};

//!
//! \brief Physics class.
//!
//! This class is responsible for the physics inside the game.
//!
class Physics
{   
public:
    Physics() = delete;

    //! Constructor of Physics.
    //! \param friction The kinetic friction acceleration of stones.
    //! \param elasticity The modulus of elasticity of stones.
    //! \param treatStopVelocity The maximum speed to be treated as zero.
    Physics(const float& friction, const float& elasticity, const float& treatStopVelocity, const int& maxStones);

    bool Update(const float& dt);

    bool CheckAllStop();
    void AffectFriction(const float& dt);
    void UpdatePosition(const float& dt);
    void CheckCrash(void);
    const bool UpdateManifold(Manifold& manifold) const;
    void PositionCorrection(Manifold& manifold);

    void DoCrash(Manifold& manifold);

    void DeleteStone(const int& id);
    Models::Stone& AddStone(StoneColor color, float mass, float radius, Utils::Vector2D<float> position, Utils::Vector2D<float> velocity);

    float friction, elasticity, treatStopVelocity;
    int id = 0;
    std::vector<Manifold> manifolds;
    std::map<StoneColor, std::vector<std::shared_ptr<Models::Stone>>> stones;
};
}  // namespace SmashStone::Games
#endif  // SMASHSTONE_GAMES_PHYSICS_HPP