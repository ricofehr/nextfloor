/**
 *  @file fire_action.h
 *  @brief Fire action for an object in the world
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_ACTIONS_JUMPACTION_H_
#define NEXTFLOOR_ACTIONS_JUMPACTION_H_

#include "nextfloor/actions/action.h"

namespace nextfloor {

namespace actions {

/**
 *  @class JumpAction
 *  @brief Implements Action (Command Pattern), generate Jump action for any object
 */
class JumpAction : public Action {

public:
    JumpAction() = default;

    JumpAction(JumpAction&&) = default;
    JumpAction& operator=(JumpAction&&) = default;
    JumpAction(const JumpAction&) = default;
    JumpAction& operator=(const JumpAction&) = default;

    virtual ~JumpAction() override = default;

    void execute(nextfloor::objects::Mesh* actor) override final;
};

}  // namespace actions

}  // namespace nextfloor

#endif  // NEXTFLOOR_ACTIONS_JUMPACTION_H_