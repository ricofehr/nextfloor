/**
 *  @file gravity_element_state.cc
 *  @brief GravityElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/gravity_element_state.h"

#include <glm/glm.hpp>
#include <iostream>

namespace nextfloor {

namespace ai {

void GravityElementState::Enter(nextfloor::element::Element* actor)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;
    current_y_stage_ = location_y;

    is_interruptible_ = false;
}

void GravityElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;
    glm::vec3 movement = actor->movement();
    movement.y = -(kDistance / kDuration) * static_cast<float>(elapsed_time);
    if (!first_execution_) {
        if (location_y >= current_y_stage_) {
            is_finished_ = true;
            movement.y = 0.0f;
        } else {
            movement.y *= 1.5;
            movement.x /= 2;
            movement.z /= 2;
        }
    }
    actor->set_movement(movement);

    current_y_stage_ = location_y;
    first_execution_ = false;
}

void GravityElementState::Exit(nextfloor::element::Element* actor)
{
    is_interruptible_ = true;
    owner_->Idle();
}

}  // namespace ai

}  // namespace nextfloor