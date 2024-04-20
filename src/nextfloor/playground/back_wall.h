/**
 *  @file back_wall.h
 *  @brief BackWall class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_PLAYGROUND_BACKWALL_H_
#define NEXTFLOOR_PLAYGROUND_BACKWALL_H_

#include "nextfloor/playground/width_wall.h"

#include <memory>
#include <vector>

#include "nextfloor/scenery/scenery.h"

namespace nextfloor {

namespace playground {

/**
 *  @class BackWall
 *  @brief Back Wall Side in a Room
 */
class BackWall : public WidthWall {

public:
    BackWall(std::vector<std::unique_ptr<nextfloor::scenery::Scenery>> wall_bricks);
    ~BackWall() final = default;

    void PrepareDraw(const glm::mat4& view_projection_matrix) final;
};

}  // namespace playground

}  // namespace nextfloor

#endif  // NEXTFLOOR_PLAYGROUND_BACKWALL_H_
