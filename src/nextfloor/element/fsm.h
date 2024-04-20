/**
 *  @file fsm.h
 *  @brief FSM class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_FSM_H_
#define NEXTFLOOR_CHARACTER_FSM_H_

#include "nextfloor/element/state.h"

#include <memory>

namespace nextfloor {

namespace element {

class Element;

/**
 *  @class FSM
 *  @brief Abstract class who defines Finite State Machine Pattern
 */
class FSM {

public:
    virtual ~FSM() = default;

    virtual void JumpUp() = 0;
    virtual void JumpDown() = 0;
    virtual void ApplyGravity() = 0;
    virtual void EndGravity() = 0;
    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual void Idle() = 0;
    virtual void Update(double elapsed_time) = 0;

    virtual void set_owner(Element* element) = 0;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_FSM_H_
