/**
 *  @file moveright_element_state.h
 *  @brief MoveRightElementState class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_MOVERIGHTCHARACTERSTATE_H_
#define NEXTFLOOR_AI_MOVERIGHTCHARACTERSTATE_H_

#include "nextfloor/ai/element_state.h"

#include "nextfloor/element/fsm.h"


namespace nextfloor {

namespace ai {

/**
 *  @class MoveRightElementState
 *  @brief Concrete class for Right Move Movement State
 */
class MoveRightElementState : public ElementState {

public:
    MoveRightElementState(nextfloor::element::FSM* owner) : owner_(owner) {}

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

#endif  // NEXTFLOOR_AI_MOVERIGHTCHARACTERSTATE_H_
