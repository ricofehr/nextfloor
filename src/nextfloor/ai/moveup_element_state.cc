/**
 *  @file moveup_element_state.cc
 *  @brief MoveUpElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/moveup_element_state.h"

#include <iostream>

namespace nextfloor {

namespace ai {

void MoveUpElementState::Enter(nextfloor::element::Element* actor)
{
    is_finished_ = false;
}

void MoveUpElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    assert(actor != nullptr);

    glm::vec3 movement = actor->movement();
    if (actor->IsCamera()) {
        auto camera = actor->camera();
        movement = camera->owner_movement() * kMoveFactor;
        if (!actor->is_flying()) {
            movement.y = 0.0f;
        }
        movement *= elapsed_time;
    }

    actor->set_movement(movement);
    is_finished_ = true;
}

void MoveUpElementState::Exit(nextfloor::element::Element* actor)
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
