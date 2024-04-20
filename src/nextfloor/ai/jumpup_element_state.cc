/**
 *  @file jumpup_element_state.cc
 *  @brief JumpUpElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/jumpup_element_state.h"

#include <glm/glm.hpp>
#include <iostream>

namespace nextfloor {

namespace ai {

void JumpUpElementState::Enter(nextfloor::element::Element* actor)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;
    start_y_stage_ = location_y;
    current_y_stage_ = location_y;
    is_interruptible_ = false;
}

void JumpUpElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;
    if (first_execution_ && (location_y <= current_y_stage_ || location_y >= start_y_stage_ + kDistance)) {
        is_finished_ = true;
        return;
    }
    current_y_stage_ = location_y;

    glm::vec3 movement = actor->movement();
    if (actor->IsCamera()) {
        auto camera = actor->camera();
        movement = camera->owner_movement();
    }

    movement.y = kDistance / kDuration;
    movement *= elapsed_time;
    if (location_y + movement.y > start_y_stage_ + kDistance) {
        movement.y = start_y_stage_ + kDistance - location_y;
    }

    actor->set_movement(movement);
    first_execution_ = true;
}

void JumpUpElementState::Exit(nextfloor::element::Element* actor)
{
    is_interruptible_ = true;
    owner_->JumpDown();
}

}  // namespace ai

}  // namespace nextfloor