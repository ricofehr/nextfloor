/**
 *  @file front_wall.cc
 *  @brief FrontWall class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/playground/front_wall.h"

#include <utility>

namespace nextfloor {

namespace playground {

FrontWall::FrontWall(std::vector<std::unique_ptr<nextfloor::scenery::Scenery>> wall_bricks)
      : WidthWall(std::move(wall_bricks))
{}

void FrontWall::PrepareDraw(const glm::mat4& view_projection_matrix)
{
    if (parent_->IsFrontPositionFilled()) {
        AddDoor();
    }
    else {
        AddWindow();
    }

    WidthWall::PrepareDraw(view_projection_matrix);
}

}  // namespace playground

}  // namespace nextfloor
