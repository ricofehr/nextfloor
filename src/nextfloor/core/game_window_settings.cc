/**
 *  @file game_window_settings.cc
 *  @brief GameWindowSettings class
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/core/game_window_settings.h"

namespace nextfloor {

namespace core {

GameWindowSettings::GameWindowSettings(nextfloor::renderer::SceneWindow* window)
{
    game_window_ = window;
}

float GameWindowSettings::getWidth()
{
    return game_window_->getWidth();
}

float GameWindowSettings::getHeight()
{
    return game_window_->getHeight();
}

float GameWindowSettings::getFpsFixMoveFactor()
{
    return game_window_->getFpsFixMoveFactor();
}

unsigned int GameWindowSettings::getMatrixId()
{
    return game_window_->getMatrixId();
}

unsigned int GameWindowSettings::getProgramId()
{
    return game_window_->getProgramId();
}

}  // namespace core

}  // namespace nextfloor
