/**
 *  @file moveup_action.cc
 *  @brief MOveUp Action class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/action/moveup_action.h"

#include <cassert>
#include <glm/glm.hpp>

namespace nextfloor {

namespace action {

void MoveUpAction::execute(nextfloor::element::Element* actor)
{
    assert(actor != nullptr);
    actor->MoveUp();
}

}  // namespace action

}  // namespace nextfloor
