/**
 *  @file wall_brick.h
 *  @brief WallBrick class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_THING_WALLBRICK_H_
#define NEXTFLOOR_THING_WALLBRICK_H_

#include "nextfloor/scenery/scenery.h"

#include <memory>
#include <vector>

#include "nextfloor/mesh/border.h"
#include "nextfloor/mesh/polygon.h"

namespace nextfloor {

namespace scenery {

/**
 *  @class WallBrick
 *  @brief WallBrick model, inherits Model abstract class
 */
class WallBrick : public Scenery {

public:
    WallBrick(std::unique_ptr<nextfloor::mesh::Border> border,
              std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> bricks);
    ~WallBrick() final = default;
};

}  // namespace scenery

}  // namespace nextfloor

#endif  // NEXTFLOOR_THING_WALLBRICK_H_