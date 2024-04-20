/**
 *  @file moveup_action.h
 *  @brief MoveUp Action Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_ACTION_MOVEUPACTION_H_
#define NEXTFLOOR_ACTION_MOVEUPACTION_H_

#include "nextfloor/gameplay/action.h"

namespace nextfloor {

namespace action {

/**
 *  @class MoveUpAction
 *  @brief Implements Action (Command Pattern), generate Move Up action for any element
 */
class MoveUpAction : public nextfloor::gameplay::Action {

public:
    void execute(nextfloor::element::Element* actor) final;
};

}  // namespace action

}  // namespace nextfloor

#endif  // NEXTFLOOR_ACTION_MOVEUPACTION_H_
