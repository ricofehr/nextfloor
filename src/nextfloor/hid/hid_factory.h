/**
 *  @file factory.h
 *  @brief Abstract Factory Class Implementation for hids
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_HID_HIDFACTORY_H_
#define NEXTFLOOR_HID_HIDFACTORY_H_

#include "nextfloor/gameplay/hid.h"
#include "nextfloor/gameplay/input_handler.h"

namespace nextfloor {

namespace hid {

/**
 *  @class HidFactory
 *  @brief Abstract Factory for hids (human interface devices)
 */
class HidFactory {

public:
    virtual ~HidFactory() = default;

    virtual std::unique_ptr<nextfloor::gameplay::HID> MakeHid() const = 0;
    virtual std::unique_ptr<nextfloor::gameplay::InputHandler> MakeInputHandler() const = 0;
};

}  // namespace hid

}  // namespace nextfloor

#endif  // NEXTFLOOR_HID_HIDFACTORY_H_