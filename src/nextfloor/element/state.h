/**
 *  @file state.h
 *  @brief State class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_STATE_H_
#define NEXTFLOOR_CHARACTER_STATE_H_

namespace nextfloor {

namespace element {

class Element;

/**
 *  @class State
 *  @brief Abstract class who defines State node in a State Pattern
 */
class State {


public:
    virtual ~State() = default;

    /**
     * First step of the state
     */
    virtual void Enter(Element* actor) = 0;

    /**
     * Execute Action on each update step
     */
    virtual void Execute(Element* actor, double elapsed_time) = 0;

    /**
     * Last step of the state
     */
    virtual void Exit(Element* actor) = 0;

    virtual bool IsInterruptible() = 0;

    virtual bool IsFinished() = 0;

    /**
     * Return the contant type of the state
     */
    virtual int type() = 0;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_STATE_H_
