/**
 *  @file game_factory.c
 *  @brief Factory Class for universe objects
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */


#include "nextfloor/factory/game_factory.h"

#include "nextfloor/factory/gl_renderer_factory.h"

#include "nextfloor/objects/universe.h"
#include "nextfloor/objects/room.h"
#include "nextfloor/objects/front_wall.h"
#include "nextfloor/objects/right_wall.h"
#include "nextfloor/objects/back_wall.h"
#include "nextfloor/objects/left_wall.h"
#include "nextfloor/objects/floor.h"
#include "nextfloor/objects/roof.h"
#include "nextfloor/objects/wall_brick.h"
#include "nextfloor/objects/player.h"
#include "nextfloor/objects/rock.h"
#include "nextfloor/objects/head_camera.h"

#include "nextfloor/grid/mesh_grid.h"
#include "nextfloor/grid/room_grid.h"
#include "nextfloor/grid/universe_grid.h"
#include "nextfloor/grid/room_grid_box.h"
#include "nextfloor/grid/universe_grid_box.h"
#include "nextfloor/grid/wired_grid_box.h"

#include "nextfloor/polygons/cube.h"

#include "nextfloor/physics/cube_border.h"
#include "nextfloor/physics/tbb_nearer_collision_engine.h"
#include "nextfloor/physics/serial_nearer_collision_engine.h"
#include "nextfloor/physics/cl_nearer_collision_engine.h"

#include "nextfloor/gameplay/demo_level.h"

#include "nextfloor/core/common_services.h"


namespace nextfloor {

namespace factory {

namespace {

static bool sInstanciated = false;

}

GameFactory::GameFactory()
{
    assert(!sInstanciated);
    sInstanciated = true;
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeUniverse()
{
    using nextfloor::objects::Universe;
    return std::make_unique<nextfloor::objects::Universe>();
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeRoom(glm::vec3 location)
{
    using nextfloor::objects::Room;
    return std::make_unique<nextfloor::objects::Room>(location);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeFrontWall(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::FrontWall;
    return std::make_unique<nextfloor::objects::FrontWall>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeRightWall(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::RightWall;
    return std::make_unique<nextfloor::objects::RightWall>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeBackWall(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::BackWall;
    return std::make_unique<nextfloor::objects::BackWall>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeLeftWall(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::LeftWall;
    return std::make_unique<nextfloor::objects::LeftWall>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeFloor(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::Floor;
    return std::make_unique<nextfloor::objects::Floor>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeRoof(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::objects::Roof;
    return std::make_unique<nextfloor::objects::Roof>(location, scale);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeWallBrick(glm::vec3 location,
                                                                     glm::vec3 scale,
                                                                     std::string texture)
{
    using nextfloor::objects::WallBrick;
    return std::make_unique<nextfloor::objects::WallBrick>(location, scale, texture);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakePlayer(glm::vec3 location)
{
    using nextfloor::objects::Player;
    return std::make_unique<nextfloor::objects::Player>(location);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeRock(glm::vec3 location)
{
    using nextfloor::objects::Rock;
    return std::make_unique<Rock>(location, 1.0f);
}

std::unique_ptr<nextfloor::objects::Mesh> GameFactory::MakeLittleRock(glm::vec3 location)
{
    using nextfloor::objects::Rock;
    return std::make_unique<Rock>(location, 0.5f);
}

std::unique_ptr<nextfloor::objects::Camera> GameFactory::MakeCamera(nextfloor::objects::Mesh* owner)
{
    using nextfloor::objects::HeadCamera;
    return std::make_unique<HeadCamera>(owner, 3.14f, 0.0f);
}

std::unique_ptr<nextfloor::objects::Polygon> GameFactory::MakeCube(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::polygons::Cube;
    return std::make_unique<Cube>(location, scale);
}

std::unique_ptr<nextfloor::objects::Border> GameFactory::MakeBorder(glm::vec3 location, glm::vec3 scale)
{
    using nextfloor::physics::CubeBorder;
    return std::make_unique<CubeBorder>(location, scale);
}

std::unique_ptr<nextfloor::objects::Grid> GameFactory::MakeUniverseGrid(nextfloor::objects::Mesh* universe)
{
    using nextfloor::grid::UniverseGrid;
    return std::make_unique<UniverseGrid>(universe);
}

std::unique_ptr<nextfloor::objects::Grid> GameFactory::MakeRoomGrid(nextfloor::objects::Mesh* room)
{
    using nextfloor::grid::RoomGrid;
    return std::make_unique<RoomGrid>(room);
}

std::unique_ptr<nextfloor::objects::Grid> GameFactory::MakeGrid(nextfloor::objects::Mesh* owner,
                                                                glm::ivec3 boxes_count,
                                                                glm::vec3 box_dimension)
{
    using nextfloor::grid::MeshGrid;
    return std::make_unique<MeshGrid>(owner, boxes_count, box_dimension);
}

std::unique_ptr<nextfloor::objects::GridBox> GameFactory::MakeRoomGridBox(glm::vec3 coords,
                                                                          nextfloor::objects::Grid* room_grid)
{
    using nextfloor::grid::RoomGridBox;
    return std::make_unique<RoomGridBox>(coords, room_grid);
}

std::unique_ptr<nextfloor::objects::GridBox> GameFactory::MakeUniverseGridBox(glm::vec3 coords,
                                                                              nextfloor::objects::Grid* universe_grid)
{
    using nextfloor::grid::UniverseGridBox;
    return std::make_unique<UniverseGridBox>(coords, universe_grid);
}

std::unique_ptr<nextfloor::objects::GridBox> GameFactory::MakeGridBox(glm::vec3 grid_coords,
                                                                      nextfloor::objects::Grid* grid)
{
    using nextfloor::grid::WiredGridBox;
    return std::make_unique<WiredGridBox>(grid_coords, grid);
}

nextfloor::objects::CollisionEngine* GameFactory::MakeCollisionEngine()
{
    using nextfloor::core::CommonServices;
    using nextfloor::objects::CollisionEngine;
    using nextfloor::physics::ClNearerCollisionEngine;
    using nextfloor::physics::NearerCollisionEngine;
    using nextfloor::physics::SerialNearerCollisionEngine;
    using nextfloor::physics::TbbNearerCollisionEngine;

    CollisionEngine* engine_collision{nullptr};

    /* Get parallell type from config */
    int type_parallell = CommonServices::getConfig()->getParallellAlgoType();

    switch (type_parallell) {  // clang-format off
        case NearerCollisionEngine::kPARALLELL_TBB:
            engine_collision = new TbbNearerCollisionEngine();
            break;
        case NearerCollisionEngine::kPARALLELL_CL:
            engine_collision = new ClNearerCollisionEngine();
            break;
        default:
            engine_collision = new SerialNearerCollisionEngine();
            break;
    }  // clang-format on

    assert(engine_collision != nullptr);

    return engine_collision;
}

std::unique_ptr<nextfloor::gameplay::Level> GameFactory::MakeLevel()
{
    using nextfloor::gameplay::DemoLevel;
    return std::make_unique<DemoLevel>();
}

GameFactory::~GameFactory()
{
    sInstanciated = false;
}

}  // namespace factory

}  // namespace nextfloor