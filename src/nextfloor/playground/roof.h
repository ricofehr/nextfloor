/**
 *  @file roof.h
 *  @brief Roof class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_PLAYGROUND_ROOF_H_
#define NEXTFLOOR_PLAYGROUND_ROOF_H_

#include "nextfloor/playground/wall.h"

#include <memory>
#include <vector>

#include "nextfloor/scenery/scenery.h"

namespace nextfloor {

namespace playground {

/**
 *  @class Roof
 *  @brief Roof of a Room
 */
class Roof : public Wall {

public:
    static constexpr char kTexture[] = "assets/plank.jpg";

    static constexpr float kBrickWidth = 2.0f;
    static constexpr float kBrickHeight = 0.25f;
    static constexpr float kBrickDepth = 2.0f;

    Roof(std::vector<std::unique_ptr<nextfloor::scenery::Scenery>> wall_bricks);
    ~Roof() final = default;

    void AddDoor() final;
    void AddWindow() final;
    void PrepareDraw(const glm::mat4& view_projection_matrix) final;

private:
    static constexpr float kDoorDeltaZ = 3.0f;
    static constexpr float kDoorDeltaX = 3.0f;
};

}  // namespace playground

}  // namespace nextfloor

#endif  // NEXTFLOOR_PLAYGROUND_WALL_H_
