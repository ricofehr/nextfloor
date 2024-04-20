/**
 *  @file idle_element_state.cc
 *  @brief IdleElementState class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/idle_element_state.h"


namespace nextfloor {

namespace ai {

void IdleElementState::Enter(nextfloor::element::Element* actor)
{
    //actor->reset_movement();
    is_finished_ = false;
}

void IdleElementState::Execute(nextfloor::element::Element* actor, double elapsed_time)
{
    actor->reset_movement();
    is_finished_ = true;
}

void IdleElementState::Exit(nextfloor::element::Element* actor)
{
    owner_->Idle();
}

}  // namespace ai

}  // namespace nextfloor