/**
 *  @file moveleft_element_state.h
 *  @brief MoveLeftElementState class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_MOVELEFTCHARACTERSTATE_H_
#define NEXTFLOOR_AI_MOVELEFTCHARACTERSTATE_H_

#include "nextfloor/ai/element_state.h"

#include "nextfloor/element/fsm.h"


namespace nextfloor {

namespace ai {

/**
 *  @class MoveLeftElementState
 *  @brief Concrete class for Move Movement State
 */
class MoveLeftElementState : public ElementState {

public:
    MoveLeftElementState(nextfloor::element::FSM* owner) : owner_(owner) {}

    void Enter(nextfloor::element::Element* actor) final;

    void Execute(nextfloor::element::Element* actor, double elapsed_time) final;

    void Exit(nextfloor::element::Element* actor) final;

    bool IsInterruptible() final { return true; }

    int type() final { return ElementState::kMoved; }

private:
    static constexpr float kMoveFactor = 2.0f;

    nextfloor::element::FSM* owner_{nullptr};
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_MOVELEFTCHARACTERSTATE_H_
