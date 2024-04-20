/**
 *  @file depth_wall.h
 *  @brief DepthWall class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_PLAYGROUND_DEPTHWALL_H_
#define NEXTFLOOR_PLAYGROUND_DEPTHWALL_H_

#include "nextfloor/playground/wall.h"

#include <memory>
#include <vector>

#include "nextfloor/scenery/scenery.h"

namespace nextfloor {

namespace playground {

/**
 *  @class DepthWall
 *  @brief DepthWall is an Abstract class for left / right wall of a Room
 */
class DepthWall : public Wall {

public:
    static constexpr char kTexture[] = "assets/brick.jpg";
    static constexpr float kBrickWidth = 0.25;
    static constexpr float kBrickHeight = 2.0f;
    static constexpr float kBrickDepth = 2.0f;

    ~DepthWall() override = default;

    void AddDoor() final;
    void AddWindow() final;

protected:
    DepthWall(std::vector<std::unique_ptr<nextfloor::scenery::Scenery>> wall_bricks);

private:
    static constexpr float kDoorDeltaZ = 6.0f;
    static constexpr float kDoorDeltaY = 2.0f;

    static constexpr float kWindowDeltaZ = 3.0f;
    static constexpr float kWindowDeltaY = 3.0f;
};

}  // namespace playground

}  // namespace nextfloor

#endif  // NEXTFLOOR_PLAYGROUND_DEPTHWALL_H_
