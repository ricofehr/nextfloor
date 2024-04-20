/**
 *  @file element_fsm_factory.cc
 *  @brief ElementFSMFactory class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/element_fsm_factory.h"

#include "nextfloor/ai/element_fsm.h"
#include "nextfloor/ai/gravity_element_state.h"
#include "nextfloor/ai/idle_element_state.h"
#include "nextfloor/ai/jumpup_element_state.h"
#include "nextfloor/ai/jumpdown_element_state.h"
#include "nextfloor/ai/movedown_element_state.h"
#include "nextfloor/ai/moveleft_element_state.h"
#include "nextfloor/ai/moveright_element_state.h"
#include "nextfloor/ai/moveup_element_state.h"

namespace nextfloor {

namespace ai {


std::unique_ptr<nextfloor::element::FSM> ElementFSMFactory::MakeElementFSM()
{
    return std::make_unique<ElementFSM>(this);
}

std::unique_ptr<nextfloor::element::State> ElementFSMFactory::MakeGravityElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<GravityElementState>(owner);
}

std::unique_ptr<nextfloor::element::State> ElementFSMFactory::MakeIdleElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<IdleElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeJumpUpElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<JumpUpElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeJumpDownElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<JumpDownElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeMoveDownElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<MoveDownElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeMoveLeftElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<MoveLeftElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeMoveRightElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<MoveRightElementState>(owner);
}

std::unique_ptr<nextfloor::element::State>
  ElementFSMFactory::MakeMoveUpElementState(nextfloor::element::FSM* owner) const
{
    return std::make_unique<MoveUpElementState>(owner);
}

}  // namespace ai

}  // namespace nextfloor
