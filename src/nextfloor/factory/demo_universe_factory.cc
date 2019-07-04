/**
 *  @file demo_universe_factory.cc
 *  @brief DemoUniverseFactory class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/factory/demo_universe_factory.h"

#include <string>
#include <tbb/tbb.h>

#include "nextfloor/core/common_services.h"
#include "nextfloor/renderer/gl_cube_renderer.h"
#include "nextfloor/physics/border.h"
#include "nextfloor/grid/universe_grid.h"
#include "nextfloor/grid/room_grid.h"

namespace nextfloor {

namespace factory {

namespace {

glm::vec3 CalculateScaleWallXFixed(nextfloor::objects::EngineGrid* grid)
{
    auto box_counts = grid->box_counts();
    auto box_dimension = grid->box_dimension();
    return glm::vec3(box_dimension.x/4, (box_counts.y/6)*box_dimension.y, (box_counts.z/8)*box_dimension.z);
}

glm::vec3 CalculateScaleWallYFixed(nextfloor::objects::EngineGrid* grid)
{
    auto box_counts = grid->box_counts();
    auto box_dimension = grid->box_dimension();
    return glm::vec3((box_counts.x/8)*box_dimension.x, box_dimension.y/4, (box_counts.z/8)*box_dimension.z);
}

glm::vec3 CalculateScaleWallZFixed(nextfloor::objects::EngineGrid* grid)
{
    auto box_counts = grid->box_counts();
    auto box_dimension = grid->box_dimension();
    return glm::vec3((box_counts.x/8)*box_dimension.x, (box_counts.y/6)*box_dimension.y, box_dimension.z/4);
}

glm::vec4 CalculateLocationWallXFixed(nextfloor::objects::EngineGrid* grid, glm::ivec3 grid_coords)
{
    auto grid0 = grid->CalculateFirstPointInGrid();
    auto box_dimension = grid->box_dimension();
    auto scale_wall = CalculateScaleWallXFixed(grid);

    auto location_wall = glm::vec4(grid0, 0.0f) + glm::vec4(0.0f, scale_wall[1], scale_wall[2], 0.0f);
    location_wall += glm::vec4(grid_coords.x*box_dimension.x, grid_coords.y*box_dimension.y, grid_coords.z*box_dimension.z, 0.0f);

    /* padding */
    if (grid_coords.x == 0) {
        location_wall.x += box_dimension.x/4;
    } else {
        location_wall.x -= box_dimension.x/4;
    }

    return location_wall;
}

glm::vec4 CalculateLocationWallYFixed(nextfloor::objects::EngineGrid* grid, glm::ivec3 grid_coords)
{
    auto grid0 = grid->CalculateFirstPointInGrid();
    auto box_dimension = grid->box_dimension();
    auto scale_wall = CalculateScaleWallYFixed(grid);

    auto location_wall = glm::vec4(grid0, 0.0f) + glm::vec4(scale_wall[0], 0.0f, scale_wall[2], 0.0f);
    location_wall += glm::vec4(grid_coords.x*box_dimension.x, grid_coords.y*box_dimension.y, grid_coords.z*box_dimension.z, 0.0f);

    /* padding */
    if (grid_coords.y == 0) {
        location_wall.y += box_dimension.y/4;
    } else {
        location_wall.y -= box_dimension.y/4;
    }

    return location_wall;
}

glm::vec4 CalculateLocationWallZFixed(nextfloor::objects::EngineGrid* grid, glm::ivec3 grid_coords)
{
    auto grid0 = grid->CalculateFirstPointInGrid();
    auto box_dimension = grid->box_dimension();
    auto scale_wall = CalculateScaleWallZFixed(grid);

    auto location_wall = glm::vec4(grid0, 0.0f) + glm::vec4(scale_wall[0], scale_wall[1], 0.0f, 0.0f);
    location_wall += glm::vec4(grid_coords.x*box_dimension.x, grid_coords.y*box_dimension.y, grid_coords.z*box_dimension.z, 0.0f);

    /* padding */
    if (grid_coords.z == 0) {
        location_wall.z += box_dimension.z/4;
    } else {
        location_wall.z -= box_dimension.z/4;
    }

    return location_wall;
}

}

std::unique_ptr<nextfloor::objects::Universe> DemoUniverseFactory::GenerateUniverse() const
{
    using nextfloor::objects::Room;
    using nextfloor::grid::UniverseGrid;
    using nextfloor::physics::Border;
    using nextfloor::core::CommonServices;

    auto universe = std::make_unique<nextfloor::objects::Universe>();
    universe->InitGrid(std::make_unique<UniverseGrid>(universe.get()));
    universe->InitBorder(std::make_unique<Border>(universe->grid()->scale_vector(), glm::vec4(0.0f)));

    std::vector<Room*> rooms;
    rooms.push_back(GenerateRoom(universe.get()));
    universe->InitDoorsForRooms();

    for (auto &room : rooms) {
        GenerateWalls(room);
        GenerateBrick(room);
        room->grid()->DisplayGrid();
    }

    universe->grid()->DisplayGrid();
    return universe;
}

nextfloor::objects::Room* DemoUniverseFactory::GenerateRoom(nextfloor::objects::Universe* universe) const
{
    using nextfloor::objects::Room;
    using nextfloor::grid::RoomGrid;
    using nextfloor::physics::Border;

    auto location = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    auto room = std::make_unique<Room>(location);
    room->InitGrid(std::make_unique<RoomGrid>(room.get()));
    room->InitBorder(std::make_unique<Border>(room->grid()->scale_vector(), location));

    room->add_child(GenerateCamera(location));

    auto room_raw = dynamic_cast<Room*>(universe->add_child(std::move(room)));
    return room_raw;
}

void DemoUniverseFactory::GenerateWalls(nextfloor::objects::Room* room) const
{
    using nextfloor::objects::Room;

    GenerateWallYFixed(room, Room::kSIDE_FLOOR);
    GenerateWallYFixed(room, Room::kSIDE_ROOF);
    GenerateWallXFixed(room, Room::kSIDE_LEFT);
    GenerateWallXFixed(room, Room::kSIDE_RIGHT);
    GenerateWallZFixed(room, Room::kSIDE_FRONT);
    GenerateWallZFixed(room, Room::kSIDE_BACK);
}

void DemoUniverseFactory::GenerateWallYFixed(nextfloor::objects::Room* room, int side) const
{
    using nextfloor::objects::Wall;
    using nextfloor::objects::Room;
    using nextfloor::renderer::GlCubeRenderer;
    using nextfloor::physics::Border;

    auto grid = room->grid();
    auto box_counts = grid->box_counts();
    auto scale_wall = CalculateScaleWallYFixed(grid);

    tbb::parallel_for (0, box_counts.x, box_counts.x/4, [&](int j) {
        tbb::parallel_for (0, box_counts.z, box_counts.z/4, [&](int k) {
            auto i = (side == Room::kSIDE_ROOF) ? box_counts.y : 0;
            auto grid_coords = glm::ivec3(j,i,k);
            if (room->IsInsideWall(grid_coords)) {
                auto location_wall = CalculateLocationWallYFixed(grid, grid_coords);
                auto wall = std::make_unique<Wall>(scale_wall, location_wall);
                wall->InitRenderer(std::make_unique<GlCubeRenderer>((i == 0) ? Wall::kFLOOR_TEXTURE : Wall::kSKY_TEXTURE));
                wall->InitBorder(std::make_unique<Border>(scale_wall, location_wall));
                room->add_child(std::move(wall));
            }
        });
    });
}

void DemoUniverseFactory::GenerateWallXFixed(nextfloor::objects::Room* room, int side) const
{
    using nextfloor::objects::Wall;
    using nextfloor::objects::Room;
    using nextfloor::renderer::GlCubeRenderer;
    using nextfloor::physics::Border;

    auto grid = room->grid();
    auto box_counts = grid->box_counts();
    auto scale_wall = CalculateScaleWallXFixed(grid);

    tbb::parallel_for (0, box_counts.y, box_counts.y/3, [&](int j) {
        tbb::parallel_for (0, box_counts.z, box_counts.z/4, [&](int k) {
            auto i = (side == Room::kSIDE_RIGHT) ? box_counts.x : 0;
            auto grid_coords = glm::ivec3(i,j,k);
            if (room->IsInsideWall(grid_coords)) {
                auto location_wall = CalculateLocationWallXFixed(grid, grid_coords);
                auto wall = std::make_unique<Wall>(scale_wall, location_wall);
                wall->InitRenderer(std::make_unique<GlCubeRenderer>(Wall::kWALL_TEXTURE));
                wall->InitBorder(std::make_unique<Border>(scale_wall, location_wall));
                room->add_child(std::move(wall));
            }
        });
    });
}

void DemoUniverseFactory::GenerateWallZFixed(nextfloor::objects::Room* room, int side) const
{
    using nextfloor::objects::Wall;
    using nextfloor::objects::Room;
    using nextfloor::renderer::GlCubeRenderer;
    using nextfloor::physics::Border;

    auto grid = room->grid();
    auto box_counts = grid->box_counts();
    auto scale_wall = CalculateScaleWallZFixed(grid);

    tbb::parallel_for (0, box_counts.y, box_counts.y/3, [&](int j) {
        tbb::parallel_for (0, box_counts.x, box_counts.x/4, [&](int k) {
            auto i = (side == Room::kSIDE_BACK) ? box_counts.z : 0;
            auto grid_coords = glm::ivec3(k,j,i);
            if (room->IsInsideWall(grid_coords)) {
                auto location_wall = CalculateLocationWallZFixed(grid, grid_coords);
                auto wall = std::make_unique<Wall>(scale_wall, location_wall);
                wall->InitRenderer(std::make_unique<GlCubeRenderer>(Wall::kWALL_TEXTURE));
                wall->InitBorder(std::make_unique<Border>(scale_wall, location_wall));
                room->add_child(std::move(wall));
            }
        });
    });
}

void DemoUniverseFactory::GenerateBrick(nextfloor::objects::Room* room) const
{
    using nextfloor::renderer::GlCubeRenderer;
    using nextfloor::objects::Brick;
    using nextfloor::physics::Border;

    float scale = 1.0f;
    auto grid = room->grid();
    auto location_brick = grid->CalculateFirstPointInGrid() + glm::vec3(3.0f);

    auto brick = std::make_unique<Brick>(scale, glm::vec4(location_brick, 0.0f));
    brick->InitBorder(std::make_unique<Border>(scale, glm::vec4(location_brick, 0.0f)));
    brick->InitRenderer(std::make_unique<GlCubeRenderer>(Brick::kTEXTURE_FILE));
    room->add_child(std::move(brick));
}

std::unique_ptr<nextfloor::objects::Camera> DemoUniverseFactory::GenerateCamera(glm::vec3 location) const
{
    using nextfloor::objects::Camera;
    using nextfloor::physics::Border;
    auto location_camera = glm::vec4(location.x, location.y, location.z + 5.0f, 0.0f);
    auto camera = std::make_unique<Camera>(location_camera, 3.14f, 0.0f);
    camera->InitBorder(std::make_unique<Border>(1.0f, location_camera));
    return camera;
}

} // namespace factory

} // namespace nextfloor
