/**
 *  @file idle_element_state.h
 *  @brief IdleElementState class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_IDLECHARACTERSTATE_H_
#define NEXTFLOOR_AI_IDLECHARACTERSTATE_H_

#include "nextfloor/ai/element_state.h"

#include "nextfloor/element/fsm.h"


namespace nextfloor {

namespace ai {

/**
 *  @class IdleElementState
 *  @brief Concrete class for Idle Movement State
 */
class IdleElementState : public ElementState {

public:
    IdleElementState(nextfloor::element::FSM* owner) : owner_(owner) {}

    void Enter(nextfloor::element::Element* actor) final;

    void Execute(nextfloor::element::Element* actor, double elapsed_time) final;

    void Exit(nextfloor::element::Element* actor) final;

    bool IsInterruptible() final { return true; }

    int type() final { return ElementState::kIdle; }

private:
    nextfloor::element::FSM* owner_{nullptr};
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_IDLECHARACTERSTATE_H_
