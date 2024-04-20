/**
 *  @file element.h
 *  @brief Element class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_CHARACTER_H_
#define NEXTFLOOR_CHARACTER_CHARACTER_H_

#include "nextfloor/mesh/dynamic_mesh.h"

#include <glm/glm.hpp>

#include "nextfloor/element/fsm.h"
#include "nextfloor/element/camera.h"

namespace nextfloor {

namespace element {

/**
 *  @class Element
 *  @brief Abstract class who defines moving element
 */
class Element : public nextfloor::mesh::DynamicMesh {

public:
    ~Element() override = default;

    virtual Camera* camera() const { return nullptr; }

    virtual bool is_flying() const { return false; }

    virtual void Jump() { fsm_->JumpUp(); }
    virtual void MoveUp() { fsm_->MoveUp(); }
    virtual void MoveDown() { fsm_->MoveDown(); }
    virtual void MoveLeft() { fsm_->MoveLeft(); }
    virtual void MoveRight() { fsm_->MoveRight(); }
    virtual void Idle() { fsm_->Idle(); }
    virtual void UpdateState(double elapsed_time) { fsm_->Update(elapsed_time); }

    void reset_movement() { set_movement(glm::vec3(kNoMovement)); }

    std::string class_name() const final { return "Element"; }

protected:
    Element() = default;

    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;

    std::unique_ptr<FSM> fsm_{nullptr};

private:
    static constexpr float kNoMovement = 0.0f;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_CHARACTER_CHARACTER_H_
