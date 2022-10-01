/**
 *  @file cl_nearer_collision_engine.h
 *  @brief ClNearerCollisionEngine class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_PHYSIC_CLNEARERCOLLISIONENGINE_H_
#define NEXTFLOOR_PHYSIC_CLNEARERCOLLISIONENGINE_H_

/* OpenCL 1.2 */
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120

#define CL_HPP_ENABLE_EXCEPTIONS

#include <vector>
#include <mutex>

#ifdef __APPLE__
#include <OpenCL/cl2.hpp>
#else
#include <CL/cl2.hpp>
#endif

#include "nextfloor/physic/nearer_collision_engine.h"

namespace nextfloor {

namespace physic {

/**
 *  @class ClNearerCollisionEngine
 *  @brief Implements opencl algorithm for collision computes
 */
class ClNearerCollisionEngine : public NearerCollisionEngine {

public:
    ClNearerCollisionEngine(int granularity);
    ~ClNearerCollisionEngine() final = default;

    ClNearerCollisionEngine(ClNearerCollisionEngine&&) = delete;
    ClNearerCollisionEngine& operator=(ClNearerCollisionEngine&&) = delete;
    ClNearerCollisionEngine(const ClNearerCollisionEngine&) = delete;
    ClNearerCollisionEngine& operator=(const ClNearerCollisionEngine&) = delete;

    PartialMove ComputeCollision(nextfloor::mesh::Mesh* target, nextfloor::mesh::Mesh* obstacle) final;

private:
    static constexpr int kBufferSize = 9;

    void InitCollisionEngine();

    /** Opencl Kernel Object */
    cl::Kernel cl_kernel_;

    /** Opencl Execution Queue  Object */
    cl::CommandQueue cl_queue_;

    /** Opencl Input Buffer */
    std::vector<cl::Buffer> bufferin_;

    /** Opencl Output Buffer */
    std::vector<cl::Buffer> bufferout_;

    /** Ensures thread safe execution */
    std::mutex collision_mutex_;

    /** Opencl Workgroup size */
    int wk_size_{32};
};

}  // namespace physic

}  // namespace nextfloor

#endif  // NEXTFLOOR_PHYSIC_CLNEARERCOLLISIONENGINE_H_
