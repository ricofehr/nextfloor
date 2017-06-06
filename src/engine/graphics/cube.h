/*
* Cube class header
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#ifndef ENGINE_GRAPHICS_CUBE_H_
#define ENGINE_GRAPHICS_CUBE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "engine/graphics/shape3d.h"

namespace engine {
namespace graphics {

/* Cube 3d object, inherit Shape3D */
class Cube : public Shape3D {

public:

    Cube(float scale, glm::vec4 location);
    Cube(float scale, glm::vec4 location, glm::vec4 move);
    Cube(glm::vec3 scale, glm::vec4 location);
    Cube(glm::vec3 scale, glm::vec4 location, glm::vec4 move);
    Cube(float scale, glm::vec4 location, GLuint vertexbuffer, GLuint texturebuffer);
    Cube(float scale, glm::vec4 location, glm::vec4 move, GLuint vertexbuffer, GLuint texturebuffer);
    Cube(glm::vec3 scale, glm::vec4 location, glm::vec4 move, GLuint vertexbuffer, GLuint texturebuffer);

    /* Default move and copy constructor / operator */
    Cube(Cube&&) = default;
    Cube& operator=(Cube&&) = default;

    Cube(const Cube&) = default;
    Cube& operator=(const Cube&) = default;

    /* Default destructor */
    virtual ~Cube() override = default;

    void Draw() noexcept override final;

private:

    GLuint vertexbuffer_;
    GLuint texturebuffer_;
};

}//namespace graphics
}//namespace engine

#endif //ENGINE_GRAPHICS_CUBE_H_
