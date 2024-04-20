/**
 *  @file camera.h
 *  @brief Camera class header
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#ifndef NEXTFLOOR_CHARACTER_CAMERA_H_
#define NEXTFLOOR_CHARACTER_CAMERA_H_

#include <glm/glm.hpp>

#include "nextfloor/mesh/mesh.h"

namespace nextfloor {

namespace element {

class Element;

/**
 *  @class Camera
 *  @brief Camera Interface
 */
class Camera {

public:
    virtual ~Camera() = default;

    virtual void ComputeOrientation() = 0;
    virtual bool IsInFieldOfView(const nextfloor::mesh::Mesh& target) const = 0;
    virtual glm::mat4 GetViewProjectionMatrix(float window_size_ratio) const = 0;
    virtual glm::mat4 GetFarAndStaticViewProjectionMatrix(float window_size_ratio) const = 0;

    virtual void increment_angles(float horizontal_angle, float vertical_angle) = 0;

    virtual glm::vec3 direction() const = 0;
    virtual glm::vec3 owner_movement() const = 0;
    virtual glm::vec3 head() const = 0;

    virtual void set_owner(Element* owner) = 0;
};

}  // namespace element

}  // namespace nextfloor

#endif  // NEXTFLOOR_OBJECTS_CAMERA_H_
