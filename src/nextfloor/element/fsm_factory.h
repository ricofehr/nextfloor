/**
 *  @file fsm_factory.h
 *  @brief FSMFactory Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_FSMFACTORY_H_
#define NEXTFLOOR_CHARACTER_FSMFACTORY_H_

#include <memory>

#include "nextfloor/element/fsm.h"

namespace nextfloor {

namespace element {

/**
 *  @class FSMFactory
 *  @brief Abstract Factory Pattern for FSMs
 */
class FSMFactory {

public:
    virtual ~FSMFactory() = default;

    virtual std::unique_ptr<FSM> MakeElementFSM() = 0;
    virtual std::unique_ptr<State> MakeGravityElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeIdleElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeJumpUpElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeJumpDownElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeMoveDownElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeMoveLeftElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeMoveRightElementState(FSM* owner) const = 0;
    virtual std::unique_ptr<State> MakeMoveUpElementState(FSM* owner) const = 0;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_FSMFACTORY_H_
