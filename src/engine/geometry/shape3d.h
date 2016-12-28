/*
* Shape3D class header
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#ifndef ENGINE_GEOMETRY_SHAPE3D_H_
#define ENGINE_GEOMETRY_SHAPE3D_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine {
namespace geometry {

/* 3d object base class */
class Shape3D {

public:
    glm::mat4 ComputeMVP();
    virtual void Draw() = 0;

    bool IsMoved() const { return move_[0] != 0.0f || move_[1] != 0.0f || move_[2] != 0.0f; }
    float distance() const { return distance_; }
    glm::vec4 move() const { return move_; }
    glm::vec4 location() const { return location_; }

    void set_distance(float distance) { distance_ = distance; }
    void set_move(glm::vec4 move) { move_ = move; }
    void set_move(glm::vec3 move) { move_ = glm::vec4(move, 0.0f); }

    virtual ~Shape3D() {}

protected:
    glm::vec4 location_;
    glm::vec4 move_;
    glm::vec3 scale_;
    float distance_;
};

}//namespace geometry
}//namespace engine

#endif //ENGINE_GEOMETRY_SHAPE3D_H_
