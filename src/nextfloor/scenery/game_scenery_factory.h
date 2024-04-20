/**
 *  @file game_scenery_factory.h
 *  @brief GmaeSceneryFactory Class for universe objects
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_THING_GAMETHINGFACTORY_H_
#define NEXTFLOOR_THING_GAMETHINGFACTORY_H_

#include "nextfloor/scenery/scenery_factory.h"

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "nextfloor/scenery/scenery.h"

#include "nextfloor/mesh/border_factory.h"
#include "nextfloor/mesh/polygon_factory.h"

namespace nextfloor {

namespace scenery {

/**
 *  @class GameSceneryFactory
 *  @brief Concrete factory for Scenery Objects
 */
class GameSceneryFactory : public SceneryFactory {

public:
    GameSceneryFactory(nextfloor::mesh::PolygonFactory* polygon_factory, nextfloor::mesh::BorderFactory* border_factory);
    ~GameSceneryFactory() final = default;

    std::unique_ptr<Scenery> MakeRock(const glm::vec3& location, const glm::vec3& movement) const final;
    std::unique_ptr<Scenery> MakeLittleRock(const glm::vec3& location, const glm::vec3& movement) const final;
    std::unique_ptr<Scenery> MakeTinyRock(const glm::vec3& location, const glm::vec3& movement) const final;

    std::vector<std::unique_ptr<Scenery>> GenerateWallBricks(glm::vec3 firstpoint,
                                                           glm::vec3 lastpoint,
                                                           const glm::vec3& brick_dimension,
                                                           const std::string& texture) const final;


private:
    static constexpr float kBrickFactorPadding = 0.5f;
    static constexpr float kBrickFactorScaling = 0.5f;

    std::unique_ptr<Scenery> MakeWallBrick(const glm::vec3& location,
                                         const glm::vec3& scale,
                                         const std::string& texture) const;

    nextfloor::mesh::PolygonFactory* polygon_factory_;
    nextfloor::mesh::BorderFactory* border_factory_;
};

}  // namespace scenery

}  // namespace nextfloor

#endif  // NEXTFLOOR_THING_GAMETHINGFACTORY_H_
