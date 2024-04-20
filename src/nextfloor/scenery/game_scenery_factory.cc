/**
 *  @file game_scenery_factory.c
 *  @brief Factory Class for scenerys
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */


#include "nextfloor/scenery/game_scenery_factory.h"

#include <vector>
#include <utility>
#include <memory>
#include <glm/glm.hpp>

#include "nextfloor/mesh/border.h"
#include "nextfloor/mesh/polygon.h"
#include "nextfloor/scenery/scenery.h"

#include "nextfloor/scenery/wall_brick.h"
#include "nextfloor/scenery/rock.h"

namespace nextfloor {

namespace scenery {

GameSceneryFactory::GameSceneryFactory(nextfloor::mesh::PolygonFactory* polygon_factory,
                                   nextfloor::mesh::BorderFactory* border_factory)
{
    polygon_factory_ = polygon_factory;
    border_factory_ = border_factory;
}

std::unique_ptr<Scenery> GameSceneryFactory::MakeRock(const glm::vec3& location, const glm::vec3& movement) const
{
    std::unique_ptr<nextfloor::mesh::Border> border = border_factory_->MakeBorder(location, Rock::kBigScale);
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock;
    rock.push_back(polygon_factory_->MakeCube(location, Rock::kBigScale, Rock::kTexture));
    return std::make_unique<Rock>(std::move(border), std::move(rock), movement);
}

std::unique_ptr<Scenery> GameSceneryFactory::MakeLittleRock(const glm::vec3& location, const glm::vec3& movement) const
{
    std::unique_ptr<nextfloor::mesh::Border> border = border_factory_->MakeBorder(location, Rock::kSmallScale);
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock;
    rock.push_back(polygon_factory_->MakeCube(location, Rock::kSmallScale, Rock::kTexture));
    return std::make_unique<Rock>(std::move(border), std::move(rock), movement);
}

std::unique_ptr<Scenery> GameSceneryFactory::MakeTinyRock(const glm::vec3& location, const glm::vec3& movement) const
{
    std::unique_ptr<nextfloor::mesh::Border> border = border_factory_->MakeBorder(location, Rock::kTinyScale);
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock;
    rock.push_back(polygon_factory_->MakeCube(location, Rock::kTinyScale, Rock::kTexture));
    return std::make_unique<Rock>(std::move(border), std::move(rock), movement);
}

std::vector<std::unique_ptr<Scenery>> GameSceneryFactory::GenerateWallBricks(glm::vec3 firstpoint,
                                                                         glm::vec3 lastpoint,
                                                                         const glm::vec3& brick_dimension,
                                                                         const std::string& texture) const
{
    auto padding = brick_dimension * kBrickFactorPadding;
    auto scaling = brick_dimension * kBrickFactorScaling;
    std::vector<std::unique_ptr<Scenery>> bricks;
    firstpoint += padding;
    lastpoint -= padding;

    for (float x = firstpoint.x; x <= lastpoint.x; x += brick_dimension.x) {
        for (float y = firstpoint.y; y <= lastpoint.y; y += brick_dimension.y) {
            for (float z = firstpoint.z; z <= lastpoint.z; z += brick_dimension.z) {
                auto location = glm::vec3(x, y, z);
                bricks.push_back(MakeWallBrick(location, scaling, texture));
            }
        }
    }

    return bricks;
}

std::unique_ptr<Scenery> GameSceneryFactory::MakeWallBrick(const glm::vec3& location,
                                                       const glm::vec3& scale,
                                                       const std::string& texture) const
{
    std::unique_ptr<nextfloor::mesh::Border> border = border_factory_->MakeBorder(location, scale);
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> brick;
    brick.push_back(polygon_factory_->MakeCube(location, scale, texture));
    return std::make_unique<WallBrick>(std::move(border), std::move(brick));
}

}  // namespace scenery

}  // namespace nextfloor
