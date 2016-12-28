/*
* Cube class header
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#ifndef ENGINE_GEOMETRY_CUBE_H_
#define ENGINE_GEOMETRY_CUBE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "engine/geometry/shape3d.h"

namespace engine {
namespace geometry {

/* Cube 3d object, inherit Shape3D */
class Cube : public Shape3D {

public:
    Cube(float scale, glm::vec4 location);
    Cube(float scale, glm::vec4 location, glm::vec4 move);
    Cube(float scale, glm::vec4 location, GLuint vertexbuffer, GLuint texturebuffer);
    Cube(float scale, glm::vec4 location, glm::vec4 move, GLuint vertexbuffer, GLuint texturebuffer);
    virtual ~Cube() override {}

    void Draw() override;

private:
    GLuint vertexbuffer_;
    GLuint texturebuffer_;
};

}//namespace geometry
}//namespace engine

#endif //ENGINE_GEOMETRY_CUBE_H_
