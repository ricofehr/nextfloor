/**
 *  @file element_state.h
 *  @brief ElementState class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_CHARACTERSTATE_H_
#define NEXTFLOOR_AI_CHARACTERSTATE_H_

#include "nextfloor/element/state.h"

#include "nextfloor/element/element.h"

namespace nextfloor {

namespace ai {

/**
 *  @class ElementState
 *  @brief Abstract class who implement State node in a State Pattern
 */
class ElementState : public nextfloor::element::State {


public:
    static constexpr int kIdle = 0;
    static constexpr int kMoved = 1;

    static constexpr int kJumpUp = 2;
    static constexpr int kJumpDown = 3;

    static constexpr int kGravity = 4;

    ~ElementState() override = default;

    bool IsFinished() override { return is_finished_; }

protected:
    ElementState() = default;

    ElementState(ElementState&&) = delete;
    ElementState& operator=(ElementState&&) = delete;
    ElementState(const ElementState&) = delete;
    ElementState& operator=(const ElementState&) = delete;

    bool is_finished_ = false;
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_CHARACTERSTATE_H_
