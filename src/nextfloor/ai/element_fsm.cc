/**
 *  @file element_fsm.cc
 *  @brief ElementFSM class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */
#include "nextfloor/ai/element_fsm.h"

#include <iostream>


namespace nextfloor {

namespace ai {

ElementFSM::ElementFSM(nextfloor::element::FSMFactory* fsm_factory)
{
    fsm_factory_ = fsm_factory;
    current_state_ = fsm_factory_->MakeIdleElementState(this);
    previous_state_ = fsm_factory_->MakeIdleElementState(this);
}

void ElementFSM::JumpUp()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeJumpUpElementState(this));
    }
}

void ElementFSM::JumpDown()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeJumpDownElementState(this));
    }
}

void ElementFSM::ApplyGravity()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeGravityElementState(this));
    }
}

void ElementFSM::MoveUp()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeMoveUpElementState(this));
    }
}

void ElementFSM::MoveDown()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeMoveDownElementState(this));
    }
}

void ElementFSM::MoveLeft()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeMoveLeftElementState(this));
    }
}

void ElementFSM::MoveRight()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        change_state(fsm_factory_->MakeMoveRightElementState(this));
    }
}

void ElementFSM::Idle()
{
    assert(fsm_factory_ != nullptr);
    assert(current_state_ != nullptr);

    if (IsInterruptible()) {
        if (current_state_->type() != ElementState::kIdle) {
            change_state(fsm_factory_->MakeIdleElementState(this));
        }
    }
}

void ElementFSM::EndGravity()
{
    assert(fsm_factory_ != nullptr);

    if (IsInterruptible()) {
        revert_to_previous_state();
    }
}


void ElementFSM::Update(double elapsed_time)
{
    assert(current_state_ != nullptr);
    assert(owner_ != nullptr);

    current_state_->Execute(owner_, elapsed_time);

    if (current_state_->IsFinished()) {
        current_state_->Exit(owner_);
    }
}

void ElementFSM::change_state(std::unique_ptr<nextfloor::element::State> new_state)
{
    assert(current_state_ != nullptr);
    assert(previous_state_ != nullptr);
    assert(owner_ != nullptr);

    if (IsInterruptible()) {
        previous_state_.swap(current_state_);
        current_state_.swap(new_state);
        current_state_->Enter(owner_);
        new_state.reset();
    }
}

void ElementFSM::revert_to_previous_state()
{
    assert(current_state_ != nullptr);
    assert(previous_state_ != nullptr);

    if (IsInterruptible()) {
        current_state_.swap(previous_state_);
        current_state_->Enter(owner_);
    }
}

bool ElementFSM::is_in_state(int state_type) const
{
    assert(current_state_ != nullptr);

    return (current_state_->type() == state_type);
}

bool ElementFSM::IsInterruptible() const
{
    assert(current_state_ != nullptr);
    assert(owner_ != nullptr);

    return current_state_->IsInterruptible();
}

}  // namespace ai

}  // namespace nextfloor