/**
 *  @file game_input_handler.h
 *  @brief GameInputHandler Header File
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_HID_GAMEINPUTHANDLER_H_
#define NEXTFLOOR_HID_GAMEINPUTHANDLER_H_

#include "nextfloor/gameplay/input_handler.h"

#include <memory>

namespace nextfloor {

namespace hid {

/**
 *  @class GameInputHandler
 *  @brief GameInputHandler maintains input commands from engine
 */
class GameInputHandler : public nextfloor::gameplay::InputHandler {

public:
    GameInputHandler(std::unique_ptr<nextfloor::gameplay::HID> hid);
    ~GameInputHandler() final = default;

    GameInputHandler(GameInputHandler&&) = default;
    GameInputHandler& operator=(GameInputHandler&&) = default;
    GameInputHandler(const GameInputHandler&) = delete;
    GameInputHandler& operator=(const GameInputHandler&) = delete;

    void InitCommands(const nextfloor::gameplay::ActionFactory& action_factory) final;

    /**
     *  Get Current State Input
     *  @return Command Object
     */
    nextfloor::gameplay::Action* HandlerInput() final;

    /**
     *  Get HID Pointer angles changes
     *  @return HIDPointer struct
     */
    nextfloor::gameplay::HIDPointer RecordHIDPointer(double elapsed_time) final;

    void PollEvents() final;
    void ResetPointer() final;
    bool IsOpenMenuEventOccurs() final;

private:
    /** The main hid */
    std::unique_ptr<nextfloor::gameplay::HID> hid_{nullptr};

    /** Element Commands */
    std::unique_ptr<nextfloor::gameplay::Action> move_up_command_{nullptr};
    std::unique_ptr<nextfloor::gameplay::Action> move_down_command_{nullptr};
    std::unique_ptr<nextfloor::gameplay::Action> move_left_command_{nullptr};
    std::unique_ptr<nextfloor::gameplay::Action> move_right_command_{nullptr};
    std::unique_ptr<nextfloor::gameplay::Action> jump_command_{nullptr};
};

}  // namespace hid

}  // namespace nextfloor

#endif  // NEXTFLOOR_HID_INPUTHANDLER_H_
