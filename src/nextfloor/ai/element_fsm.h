/**
 *  @file element_fsm.h
 *  @brief ElementFSM class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_CHARACTERFSM_H_
#define NEXTFLOOR_AI_CHARACTERFSM_H_

#include "nextfloor/element/fsm.h"

#include <memory>

#include "nextfloor/ai/element_state.h"
#include "nextfloor/element/state.h"
#include "nextfloor/element/fsm_factory.h"

namespace nextfloor {

namespace ai {

/**
 *  @class ElementFSM
 *  @brief Abstract class who implement FSM Pattern
 */
class ElementFSM : public nextfloor::element::FSM {

public:
    ElementFSM(nextfloor::element::FSMFactory* fsm_factory);

    void JumpUp() override;
    void JumpDown() override;
    void ApplyGravity() override;
    void EndGravity() override;
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;
    void Idle() override;
    void Update(double elapsed_time) override;

    void set_owner(nextfloor::element::Element* owner) override { owner_ = owner; }

protected:
    void change_state(std::unique_ptr<nextfloor::element::State> new_state);
    void revert_to_previous_state();
    bool is_in_state(int state_type) const;
    bool IsInterruptible() const;

    nextfloor::element::Element* owner_{nullptr};
    std::unique_ptr<nextfloor::element::State> current_state_{nullptr};
    std::unique_ptr<nextfloor::element::State> previous_state_{nullptr};
    nextfloor::element::FSMFactory* fsm_factory_{nullptr};
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_CHARACTERFSM_H_
