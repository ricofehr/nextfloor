/**
 *  @file scenery_factory.h
 *  @brief SceneryFactory Class for universe objects
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_THING_THINGFACTORY_H_
#define NEXTFLOOR_THING_THINGFACTORY_H_

#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "nextfloor/scenery/scenery.h"

namespace nextfloor {

namespace scenery {

/**
 *  @class SceneryFactory
 *  @brief Concret factory for Universe Objects
 */
class SceneryFactory {

public:
    virtual ~SceneryFactory() = default;

    virtual std::unique_ptr<Scenery> MakeRock(const glm::vec3& location, const glm::vec3& movement) const = 0;
    virtual std::unique_ptr<Scenery> MakeLittleRock(const glm::vec3& location, const glm::vec3& movement) const = 0;
    virtual std::unique_ptr<Scenery> MakeTinyRock(const glm::vec3& location, const glm::vec3& movement) const = 0;

    virtual std::vector<std::unique_ptr<Scenery>> GenerateWallBricks(glm::vec3 firstpoint,
                                                                   glm::vec3 lastpoint,
                                                                   const glm::vec3& brick_dimension,
                                                                   const std::string& texture) const = 0;
};

}  // namespace scenery

}  // namespace nextfloor

#endif  // NEXTFLOOR_THING_THINGFACTORY_H_
