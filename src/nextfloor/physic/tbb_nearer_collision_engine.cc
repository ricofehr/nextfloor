/**
 *  @file tbb_collision.cc
 *  @brief Tbb version for CollisionEngine
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/physic/tbb_nearer_collision_engine.h"

#include <tbb/tbb.h>

namespace nextfloor {

namespace physic {

TbbNearerCollisionEngine::TbbNearerCollisionEngine(int granularity) : NearerCollisionEngine(granularity) {}

float TbbNearerCollisionEngine::ComputeCollision(nextfloor::mesh::Mesh* target, nextfloor::mesh::Mesh* obstacle)
{
    float distance(1.0f);
    auto target_border = target->border();
    auto obstacle_border = obstacle->border();
    tbb::mutex distance_mutex;

    tbb::parallel_for(1, (granularity_ + 1), 1, [&](int fact) {
        float parted_move = static_cast<float>(fact) / granularity_;
        if (target_border->IsObstacleInCollisionAfterPartedMove(*obstacle_border, parted_move)) {
            float test_collision = static_cast<float>(fact - 1) / granularity_;

            tbb::mutex::scoped_lock lock_map(distance_mutex);
            if (test_collision < distance) {
                distance = test_collision;
            }
        }
    });

    return distance;
}

}  // namespace physic

}  // namespace nextfloor
