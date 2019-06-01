/**
 *  @file random_universe_factory.h
 *  @brief Random World Factory Class for universe objects
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_UNIVERSE_RANDOMUNIVERSEFACTORY_H_
#define NEXTFLOOR_UNIVERSE_RANDOMUNIVERSEFACTORY_H_

#include <memory>
#include <glm/glm.hpp>

#include "nextfloor/universe/factory/universe_factory.h"

namespace nextfloor {

namespace universe {

namespace factory {

/**
 *  @class RandomUniverseFactory
 *  @brief Implements the abstract UniverseFactory, generate Objects For Universe in Random manner
 */
class RandomUniverseFactory : public UniverseFactory {

public:

    RandomUniverseFactory() = default;

    RandomUniverseFactory(RandomUniverseFactory&&) = default;

    RandomUniverseFactory& operator=(RandomUniverseFactory&&) = default;

    RandomUniverseFactory(const RandomUniverseFactory&) = default;

    RandomUniverseFactory& operator=(const RandomUniverseFactory&) = default;

    virtual ~RandomUniverseFactory() override = default;

    virtual std::unique_ptr<nextfloor::universe::Universe> GenerateUniverse() const override final;

    virtual nextfloor::universe::Room* GenerateRoom(nextfloor::universe::Universe* universe) const override final;

    virtual void GenerateWalls(nextfloor::universe::Room* room) const override final;

    virtual void GenerateBrick(nextfloor::universe::Room* room) const override final;

    virtual std::unique_ptr<nextfloor::universe::dynamic::Camera> GenerateCamera(glm::vec4 location) const override final;

    virtual void GenerateBuffers() const override final;

private:

    void GenerateWallXFixed(nextfloor::universe::Room* room, int side) const;
    void GenerateWallYFixed(nextfloor::universe::Room* room, int side) const;
    void GenerateWallZFixed(nextfloor::universe::Room* room, int side) const;

};

} // namespace factory

} // namespace universe

} // namespace nextfloor

#endif // NEXTFLOOR_UNIVERSE_RANDOMUNIVERSEFACTORY_H_
