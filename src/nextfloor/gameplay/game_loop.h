/**
 *  @file game_loop.h
 *  @brief GameLoop class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CONTROLLER_GAMELOOP_H_
#define NEXTFLOOR_CONTROLLER_GAMELOOP_H_

#include "nextfloor/gameplay/loop.h"

#include <memory>

#include "nextfloor/gameplay/scene_window.h"
#include "nextfloor/gameplay/input_handler.h"
#include "nextfloor/gameplay/frame_timer.h"
#include "nextfloor/gameplay/level.h"
#include "nextfloor/gameplay/menu.h"

namespace nextfloor {

namespace gameplay {

/**
 *  @class GameLoop
 *  @brief  GameLoop manages the lifetime of the opengl scene
 */
class GameLoop : public Loop {

public:
    GameLoop(std::unique_ptr<Level> level,
             SceneWindow* game_window,
             std::unique_ptr<InputHandler> input_handler,
             std::unique_ptr<FrameTimer> timer,
             std::unique_ptr<Menu> main_menu);
    ~GameLoop() noexcept;

    GameLoop(GameLoop&&) = default;
    GameLoop& operator=(GameLoop&&) = default;
    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    void RunLoop() final;
    void ReturnToGame() final;
    void ExitGame() final;

private:
    static constexpr float kMsInSecond = 1000.0f;

    static constexpr int kExitState = 0;
    static constexpr int kInGameState = 1;
    static constexpr int kInMenuState = 2;

    void UpdateTime();
    void UpdateCameraOrientation();
    void HandlerInput();
    void ManageElementStates();
    void Draw();
    void LogLoop();
    void LogFps();
    void PollEvents();
    void CheckCurrentState();
    void ApplyLoop();
    void RunGame();
    void DisplayMenu();
    void SetMenuState();

    inline bool IsInRunningState() const { return current_state_ != kExitState; }
    inline bool IsInGame() const { return current_state_ == kInGameState; }
    inline bool IsInMenu() const { return current_state_ == kInMenuState; }

    std::unique_ptr<InputHandler> input_handler_{nullptr};
    SceneWindow* game_window_{nullptr};
    std::unique_ptr<FrameTimer> timer_{nullptr};
    std::unique_ptr<Level> level_{nullptr};
    std::unique_ptr<Menu> main_menu_{nullptr};
    int current_state_{kInGameState};
};

}  // namespace gameplay

}  // namespace nextfloor

#endif  // NEXTFLOOR_RENDERER_GAMELOOP_H_
