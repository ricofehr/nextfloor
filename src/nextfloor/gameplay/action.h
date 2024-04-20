/**
 *  @file action.h
 *  @brief BaseClass Action Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_GAMEPLAY_ACTION_H_
#define NEXTFLOOR_GAMEPLAY_ACTION_H_

#include "nextfloor/element/element.h"

namespace nextfloor {

namespace gameplay {

/**
 *  @class Action
 *  @brief Action interface, base class for apply Command Pattern to any element (player and NPJs) actions
 */
class Action {

public:
    virtual ~Action() = default;

    /**
     * Execute Action on target object (actor)
     */
    virtual void execute(nextfloor::element::Element* actor) = 0;

protected:
    /* Default elapsed time : frame counts */
    static constexpr int kFrameElapsedTime = 0;
};

}  // namespace gameplay

}  // namespace nextfloor

#endif  // NEXTFLOOR_GAMEPLAY_ACTION_H_
