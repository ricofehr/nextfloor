/**
 *  @file jumpdown_element_state.cc
 *  @brief JumpDownElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/jumpdown_element_state.h"

#include <glm/glm.hpp>
#include <iostream>

namespace nextfloor {

namespace ai {

void JumpDownElementState::Enter(nextfloor::element::Element* actor)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;
    current_y_stage_ = location_y;

    is_interruptible_ = false;
}

void JumpDownElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    assert(actor != nullptr);

    float location_y = actor->location().y;

    /* On first execution, set movement to down, on second execution test if location has changed */
    if (first_execution_ && location_y >= current_y_stage_) {
        if (location_y > current_y_stage_) {
            std::cout << location_y - current_y_stage_ << std::endl;
        }
        is_finished_ = true;
        return;
    }

    current_y_stage_ = location_y;

    glm::vec3 movement = actor->movement();
    if (actor->IsCamera()) {
        auto camera = actor->camera();
        movement = camera->owner_movement();
    }

    movement.y = -kDistance / kDuration;

    movement *= elapsed_time;
    actor->set_movement(movement);
    first_execution_ = true;
}

void JumpDownElementState::Exit(nextfloor::element::Element* actor)
{
    is_interruptible_ = true;
    owner_->Idle();
}

}  // namespace ai

}  // namespace nextfloor