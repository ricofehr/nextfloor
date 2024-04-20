/**
 *  @file element_fsm_factory.h
 *  @brief ElementFSMFactory Header file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_AI_CHARACTERFSMFACTORY_H_
#define NEXTFLOOR_AI_CHARACTERFSMFACTORY_H_

#include "nextfloor/element/fsm_factory.h"


namespace nextfloor {

namespace ai {

/**
 *  @class ElementFSMFactory
 *  @brief Concrete Factory for FSM element related objects
 */
class ElementFSMFactory : public nextfloor::element::FSMFactory {

public:
    std::unique_ptr<nextfloor::element::FSM> MakeElementFSM() override;
    std::unique_ptr<nextfloor::element::State> MakeGravityElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeIdleElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeJumpUpElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeJumpDownElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeMoveDownElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeMoveLeftElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeMoveRightElementState(nextfloor::element::FSM* owner) const override;
    std::unique_ptr<nextfloor::element::State> MakeMoveUpElementState(nextfloor::element::FSM* owner) const override;
};

}  // namespace ai

}  // namespace nextfloor

#endif  // NEXTFLOOR_AI_CHARACTERFSMFACTORY_H_
