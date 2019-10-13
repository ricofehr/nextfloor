/**
 *  @file back_wall.h
 *  @brief BackWall class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_OBJECTS_BACKWALL_H_
#define NEXTFLOOR_OBJECTS_BACKWALL_H_

#include "nextfloor/objects/width_wall.h"

#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace nextfloor {

namespace objects {

/**
 *  @class BackWall
 *  @brief Back Wall Side in a Room
 */
class BackWall : public WidthWall {

public:
    BackWall(std::unique_ptr<Border> border, std::vector<std::unique_ptr<Mesh>> wall_bricks);
    ~BackWall() final = default;

    void PrepareDraw(const glm::mat4& view_projection_matrix) final;
};

}  // namespace objects

}  // namespace nextfloor

#endif  // NEXTFLOOR_UNIVERSE_OBJECTS_BACKWALL_H_
