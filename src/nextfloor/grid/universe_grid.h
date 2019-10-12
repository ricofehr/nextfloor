/**
 *  @file universe_grid.h
 *  @brief UniverseGrid class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_GRID_UNIVERSEGRID_H_
#define NEXTFLOOR_GRID_UNIVERSEGRID_H_

#include "nextfloor/grid/wired_grid.h"

#include "nextfloor/objects/mesh.h"
#include "nextfloor/grid/mesh_grid_factory.h"

namespace nextfloor {

namespace grid {

/**
 *  @class UniverseGrid
 *  @brief Abstract class who defines grid for Rooms
 */
class UniverseGrid : public WiredGrid {

public:
    /*
     *  WiredGrid Constants For Romm Setting
     */
    static constexpr int kWIDTH_BOXES_COUNT = 8;
    static constexpr int kHEIGHT_BOXES_COUNT = 4;
    static constexpr int kDEPTH_BOXES_COUNT = 8;
    static constexpr float kBOX_WIDTH = 16.0f;
    static constexpr float kBOX_HEIGHT = 12.0f;
    static constexpr float kBOX_DEPTH = 16.0f;

    UniverseGrid(const glm::vec3& location, std::unique_ptr<nextfloor::objects::GridBox>*** boxes);
    ~UniverseGrid() noexcept final;
};

}  // namespace grid

}  // namespace nextfloor

#endif  // NEXTFLOOR_GRID_UNIVERSEGRID_H_
