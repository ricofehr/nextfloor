/**
 *  @file moveright_element_state.cc
 *  @brief MoveRightElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/moveright_element_state.h"


namespace nextfloor {

namespace ai {

void MoveRightElementState::Enter(nextfloor::element::Element* actor)
{
    is_finished_ = false;
}

void MoveRightElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    glm::vec3 movement = actor->movement();
    auto head = movement;
    if (actor->IsCamera()) {
        auto camera = actor->camera();
        movement = camera->direction() * kMoveFactor;
        if (!actor->is_flying()) {
            movement.y = 0.0f;
        }
        movement *= elapsed_time;
        head = camera->head();
    }

    /* Right vector: perpendicular to both direction and head vector */
    glm::vec3 right_movement = glm::cross(movement, head);
    actor->set_movement(right_movement);
    is_finished_ = true;
}

void MoveRightElementState::Exit(nextfloor::element::Element* actor)
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
