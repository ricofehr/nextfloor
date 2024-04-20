/**
 *  @file jumpdown_element_state.h
 *  @brief JumpDownElementState class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_JUMPDOWNCHARACTERSTATE_H_
#define NEXTFLOOR_AI_JUMPDOWNCHARACTERSTATE_H_

#include "nextfloor/ai/element_state.h"

#include "nextfloor/element/fsm.h"


namespace nextfloor {

namespace ai {

/**
 *  @class JumpDownElementState
 *  @brief Concrete class for Jump Movement State
 */
class JumpDownElementState : public ElementState {

public:
    JumpDownElementState(nextfloor::element::FSM* owner) : owner_(owner) {}

    void Enter(nextfloor::element::Element* actor) final;

    void Execute(nextfloor::element::Element* actor, double elapsed_time) final;

    void Exit(nextfloor::element::Element* actor) final;

    bool IsInterruptible() final { return is_interruptible_; }

    int type() final { return ElementState::kJumpDown; }

private:
    static constexpr float kDistance = 1.5f;
    static constexpr float kDuration = 0.5f;

    float current_y_stage_{0.0f};
    bool first_execution_{false};

    bool is_interruptible_{false};
    nextfloor::element::FSM* owner_{nullptr};
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_JUMPCHARACTERSTATE_H_
