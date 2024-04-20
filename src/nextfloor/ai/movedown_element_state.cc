/**
 *  @file movedown_element_state.cc
 *  @brief MoveDownElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/movedown_element_state.h"


namespace nextfloor {

namespace ai {

void MoveDownElementState::Enter(nextfloor::element::Element* actor)
{
    is_finished_ = false;
}

void MoveDownElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    glm::vec3 movement = actor->movement();
    if (actor->IsCamera()) {
        auto camera = actor->camera();
        movement = camera->direction() * kMoveFactor;
        if (!actor->is_flying()) {
            movement.y = 0.0f;
        }
        movement *= elapsed_time;
    }

    actor->set_movement(-movement);
    is_finished_ = true;
}

void MoveDownElementState::Exit(nextfloor::element::Element* actor)
{
    if (actor->is_flying()) {
        owner_->Idle();
    }
    else {
        owner_->ApplyGravity();
    }
}

}  // namespace ai

}  // namespace nextfloor