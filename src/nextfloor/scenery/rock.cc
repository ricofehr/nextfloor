/**
 *  @file rock.cc
 *  @brief Rock class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/scenery/rock.h"

#include <utility>

namespace nextfloor {

namespace scenery {

Rock::Rock(std::unique_ptr<nextfloor::mesh::Border> border,
           std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock,
           const glm::vec3& movement)
{
    polygons_ = std::move(rock);
    border_ = std::move(border);

    set_movement(movement);
}

}  // namespace scenery

}  // namespace nextfloor
