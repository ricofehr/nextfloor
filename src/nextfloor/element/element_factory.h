/**
 *  @file element_factory.h
 *  @brief ElementFactory Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_CHARACTERFACTORY_H_
#define NEXTFLOOR_CHARACTER_CHARACTERFACTORY_H_

#include <memory>
#include <glm/glm.hpp>

#include "nextfloor/element/element.h"

namespace nextfloor {

namespace element {

/**
 *  @class ElementFactory
 *  @brief Abstract Factory Pattern for Elements
 */
class ElementFactory {

public:
    virtual ~ElementFactory() = default;
    virtual std::unique_ptr<Element> MakePlayer(const glm::vec3& location) const = 0;
    virtual std::unique_ptr<Element> MakeMovingRock(const glm::vec3& location, const glm::vec3& movement) const = 0;
    virtual std::unique_ptr<Element> MakeMovingTinyRock(const glm::vec3& location, const glm::vec3& movement) const = 0;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_CHARACTERFACTORY_H_
