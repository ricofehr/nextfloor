/**
 *  @file game_level.h
 *  @brief Game Level class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_GAMEPLAY_GAMELEVEL_H_
#define NEXTFLOOR_GAMEPLAY_GAMELEVEL_H_

#include "nextfloor/gameplay/level.h"

#include <memory>
#include <list>

#include "nextfloor/gameplay/renderer_factory.h"
#include "nextfloor/physic/collision_engine.h"
#include "nextfloor/element/element.h"
#include "nextfloor/playground/ground.h"
#include "nextfloor/scenery/scenery.h"
#include "nextfloor/element/camera.h"


namespace nextfloor {

namespace gameplay {

/**
 *  @class GameLevel
 *  @brief Define a determinitic demo level
 */
class GameLevel : public Level {

public:
    GameLevel(std::unique_ptr<nextfloor::playground::Ground> universe,
              std::unique_ptr<nextfloor::element::Element> player,
              std::unique_ptr<nextfloor::physic::CollisionEngine> collision_engine,
              RendererFactory* renderer_factory);
    ~GameLevel() final = default;

    GameLevel(GameLevel&&) = default;
    GameLevel& operator=(GameLevel&&) = default;
    GameLevel(const GameLevel&) = delete;
    GameLevel& operator=(const GameLevel&) = delete;

    void UpdateCameraOrientation(HIDPointer angles) final;
    void ExecutePlayerAction(Action* command) final;
    void UpdateElementStates(double elapsed_time) final;
    void Move() final;
    void Draw(float window_size_ratio) final;

private:
    void SetActiveCamera(nextfloor::element::Camera* active_camera);

    void DetectCollision(std::vector<nextfloor::mesh::Mesh*> moving_objects);
    void PivotCollisonOnObject(nextfloor::mesh::Mesh* pivot);
    void MoveObjects(std::vector<nextfloor::mesh::Mesh*> moving_objects);

    void PrepareDraw(float window_size_ratio);
    void Renderer(const nextfloor::mesh::Mesh& mesh);
    void RendererCubeMap(float window_size_ratio);

    std::unique_ptr<nextfloor::playground::Ground> universe_{nullptr};
    nextfloor::element::Element* player_{nullptr};
    std::list<nextfloor::element::Camera*> game_cameras_;
    std::unique_ptr<nextfloor::physic::CollisionEngine> collision_engine_{nullptr};
    RendererFactory* renderer_factory_{nullptr};
};

}  // namespace gameplay

}  // namespace nextfloor

#endif  // NEXTFLOOR_GAMEPLAY_GAMELEVEL_H_
