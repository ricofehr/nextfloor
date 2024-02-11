/**
 *  @file nearer_collision_engine.h
 *  @brief NearerCollisionEngine class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_PHYSIC_NEARERCOLLISIONENGINE_H_
#define NEXTFLOOR_PHYSIC_NEARERCOLLISIONENGINE_H_

#include "nextfloor/physic/collision_engine.h"

#include "nextfloor/mesh/mesh.h"

namespace nextfloor {

namespace physic {

/**
 *  @class NearerCollisionEngine
 *  @brief Abstract Class who manage collisition computes between 3d models\n
 *  Use Strategy / Template Method Patterns for this abstract class and subclasses,\n
 *  which proposes 2 differents Collision Algorithm: serial, tbb version
 */
class NearerCollisionEngine : public CollisionEngine {

public:
    static constexpr int kParallellSerial = 1;
    static constexpr int kParallellTbb = 2;

    ~NearerCollisionEngine() override = default;

    /* Template Method : Detect if a collision exists between target and obstacle. */
    void DetectCollision(nextfloor::mesh::Mesh* target, nextfloor::mesh::Mesh* obstacle) final;

protected:
    NearerCollisionEngine(int granularity) { granularity_ = granularity; }

    NearerCollisionEngine(NearerCollisionEngine&&) = default;
    NearerCollisionEngine& operator=(NearerCollisionEngine&&) = default;
    NearerCollisionEngine(const NearerCollisionEngine&) = delete;
    NearerCollisionEngine& operator=(const NearerCollisionEngine&) = delete;

    /* Accuracy (computes count) of NearerCollisionEngine detection */
    int granularity_{16};
};

}  // namespace physic

}  // namespace nextfloor

#endif  // NEXTFLOOR_PHYSIC_NEARERCOLLISIONENGINE_H_
