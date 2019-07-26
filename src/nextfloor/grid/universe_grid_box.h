/**
 *  @file universe_grid_box.h
 *  @brief UniverseGridBox class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_GRID_UNIVERSEGRIDBOX_H_
#define NEXTFLOOR_GRID_UNIVERSEGRIDBOX_H_

#include "nextfloor/grid/wired_grid_box.h"

namespace nextfloor {

namespace grid {

/**
 *  @class UniverseGridBox
 *  @brief Abstract class who defines universe grid object
 */
class UniverseGridBox : public WiredGridBox {

public:

    UniverseGridBox(glm::vec3 coords, nextfloor::objects::Grid* owner);
    UniverseGridBox(UniverseGridBox&&) = default;
    UniverseGridBox& operator=(UniverseGridBox&&) = default;
    UniverseGridBox(const UniverseGridBox&) = default;
    UniverseGridBox& operator=(const UniverseGridBox&) = default;
    virtual ~UniverseGridBox() = default;
};

} // namespace grid

} // namespace nextfloor

#endif // NEXTFLOOR_GRID_UNIVERSEGRIDBOX_H_
