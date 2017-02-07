/*
* Box class header
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#ifndef ENGINE_GEOMETRY_BOX_H_
#define ENGINE_GEOMETRY_BOX_H_

#include <glm/glm.hpp>

#include <vector>

#include "engine/geometry/cube.h"

namespace engine {
namespace geometry {

/**
*    Each 3d model in the scene must be fill into a box.
*    Uses for coordinates and collision compute.
*    A box is a cube with additional properties, so it ihnerits from Cube
**/
class Box : public Cube {

public:
    Box();
    Box(float scale, glm::vec4 location, std::vector<glm::vec3> coords);
    Box(float scale, glm::vec4 location, glm::vec4 move, std::vector<glm::vec3> coords);
    ~Box() {}

    std::vector<glm::vec3> ComputeCoords() const;
    void MoveCoords();

private:
    std::vector<glm::vec3> coords_;
};

}//namespace geometry
}//namespace engine

#endif //ENGINE_GEOMETRY_BOX_H_
