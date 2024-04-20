/**
 *  @file game_element_factory.cc
 *  @brief GameElementFactory class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/element/game_element_factory.h"

#include <cassert>
#include <memory>
#include <utility>

#include "nextfloor/element/camera.h"
#include "nextfloor/mesh/border.h"

#include "nextfloor/element/player.h"
#include "nextfloor/element/moving_rock.h"

namespace nextfloor {

namespace element {

GameElementFactory::GameElementFactory(CameraFactory* camera_factory,
                                           FSMFactory* fsm_factory,
                                           nextfloor::mesh::BorderFactory* border_factory,
                                           nextfloor::mesh::PolygonFactory* polygon_factory)
{
    camera_factory_ = camera_factory;
    border_factory_ = border_factory;
    fsm_factory_ = fsm_factory;
    polygon_factory_ = polygon_factory;
}

std::unique_ptr<Element> GameElementFactory::MakePlayer(const glm::vec3& location) const
{
    assert(border_factory_ != nullptr);
    assert(camera_factory_ != nullptr);
    assert(fsm_factory_ != nullptr);

    using nextfloor::mesh::Border;
    std::unique_ptr<Border> border = border_factory_->MakeBorder(location, Player::kBorderScale);
    std::unique_ptr<Camera> camera = camera_factory_->MakeCamera();
    std::unique_ptr<FSM> fsm = fsm_factory_->MakeElementFSM();
    return std::make_unique<Player>(std::move(border), std::move(camera), std::move(fsm));
}

std::unique_ptr<Element> GameElementFactory::MakeMovingRock(const glm::vec3& location,
                                                                const glm::vec3& movement) const
{
    assert(border_factory_ != nullptr);
    assert(camera_factory_ != nullptr);
    assert(fsm_factory_ != nullptr);

    using nextfloor::mesh::Border;
    std::unique_ptr<Border> border = border_factory_->MakeBorder(location, MovingRock::kBorderScale);
    std::unique_ptr<FSM> fsm = fsm_factory_->MakeElementFSM();
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock;
    rock.push_back(polygon_factory_->MakeCube(location, MovingRock::kBorderScale, MovingRock::kTexture));

    return std::make_unique<MovingRock>(std::move(border), std::move(fsm), std::move(rock), movement);
}

std::unique_ptr<Element> GameElementFactory::MakeMovingTinyRock(const glm::vec3& location,
                                                                    const glm::vec3& movement) const
{
    assert(border_factory_ != nullptr);
    assert(camera_factory_ != nullptr);
    assert(fsm_factory_ != nullptr);

    using nextfloor::mesh::Border;
    std::unique_ptr<Border> border = border_factory_->MakeBorder(location, MovingRock::kTinyScale);
    std::unique_ptr<FSM> fsm = fsm_factory_->MakeElementFSM();
    std::vector<std::unique_ptr<nextfloor::mesh::Polygon>> rock;
    rock.push_back(polygon_factory_->MakeCube(location, MovingRock::kTinyScale, MovingRock::kTexture));

    return std::make_unique<MovingRock>(std::move(border), std::move(fsm), std::move(rock), movement);
}

}  // namespace element

}  // namespace nextfloor
