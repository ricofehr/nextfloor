/**
 *  @file game_element_factory.h
 *  @brief GameElementFactory Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_GAMECHARACTERFACTORY_H_
#define NEXTFLOOR_CHARACTER_GAMECHARACTERFACTORY_H_

#include "nextfloor/element/element_factory.h"

#include "nextfloor/element/fsm_factory.h"
#include "nextfloor/element/camera_factory.h"
#include "nextfloor/mesh/border_factory.h"
#include "nextfloor/mesh/polygon_factory.h"

namespace nextfloor {

namespace element {

/**
 *  @class GameElementFactory
 *  @brief Concrete Factory for game element related objects
 */
class GameElementFactory : public ElementFactory {

public:
    GameElementFactory(CameraFactory* camera_factory,
                         FSMFactory* fsm_factory,
                         nextfloor::mesh::BorderFactory* border_factory,
                         nextfloor::mesh::PolygonFactory* polygon_factory);
    ~GameElementFactory() final = default;

    std::unique_ptr<Element> MakePlayer(const glm::vec3& location) const override;
    std::unique_ptr<Element> MakeMovingRock(const glm::vec3& location, const glm::vec3& movement) const override;
    std::unique_ptr<Element> MakeMovingTinyRock(const glm::vec3& location, const glm::vec3& movement) const override;

private:
    CameraFactory* camera_factory_{nullptr};
    FSMFactory* fsm_factory_{nullptr};
    nextfloor::mesh::BorderFactory* border_factory_{nullptr};
    nextfloor::mesh::PolygonFactory* polygon_factory_{nullptr};
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_GAMECHARACERFACTORY_H_
