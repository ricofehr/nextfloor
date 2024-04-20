/**
 *  @file movedown_action.h
 *  @brief MoveDown Action Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_ACTION_MOVEDOWNACTION_H_
#define NEXTFLOOR_ACTION_MOVEDOWNACTION_H_

#include "nextfloor/gameplay/action.h"

namespace nextfloor {

namespace action {

/**
 *  @class MoveDownAction
 *  @brief Implements Action (Command Pattern), generate Move Down action for any element
 */
class MoveDownAction : public nextfloor::gameplay::Action {

public:
    void execute(nextfloor::element::Element* actor) final;
};

}  // namespace action

}  // namespace nextfloor

#endif  // NEXTFLOOR_ACTION_MOVEDOWNACTION_H_
