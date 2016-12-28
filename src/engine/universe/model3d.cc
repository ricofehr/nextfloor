/*
* Model3d class file
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#include "engine/universe/model3d.h"

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <iostream>

#include "engine/geometry/box.h"
#include "engine/geometry/shape3d.h"

namespace engine {
namespace universe {

namespace {
    /* Unique id for object */
    static int objectid = 1;
}

/* Constructor */
Model3D::Model3D()
{
    id_ = objectid++;
    distance_ = -1;
    obstacle_ = nullptr;
    id_last_collision_ = 0;
    is_controlled_ = false;
    is_crossed_ = false;
}

/* Comparaison operator */
bool operator==(const Model3D& o1, const Model3D& o2)
{
    return o1.id() == o2.id();
}

bool operator!=(const Model3D& o1, const Model3D& o2)
{
    return o1.id() != o2.id();
}

/* Draw the model */
void Model3D::Draw()
{
    /* if we can cross into object, make distance to 15 */
    if (obstacle_ != nullptr && obstacle_->IsCrossed()) {
        distance_ = 15.0f;
        obstacle_ = nullptr;
    }

    border_.set_distance(distance_);
    border_.MoveCoords();
    for (auto &element : elements_) {
        element->set_distance(distance_);
        element->Draw();
    }
    distance_ = -1;
    /* An object cant touch same object twice, except camera */
    if (!is_controlled_ && obstacle_ != nullptr)
        id_last_collision_ = obstacle_->id();
    obstacle_ = nullptr;
}

/* Task who detect if obstacle is in collision with current object */
std::vector<Model3D*> Model3D::DetectCollision(Model3D *obstacle)
{
    float distance = 0;
    int fact = 1, fact2 = 0;
    std::vector<Model3D*> recompute;
    Model3D *oldobstacle1, *oldobstacle2;

    engine::geometry::Box border2 = obstacle->border();
    std::vector<glm::vec3> coords1 = border_.ComputeCoords();
    std::vector<glm::vec3> coords2 = border2.ComputeCoords();

    /* First polygon point (x,y,z) and dimensions (h,w,d) */
    GLfloat x1, y1, z1, h1, w1, d1;
    GLfloat x2, y2, z2, h2, w2, d2;

    /* Cant touch same object twice in short time */
    if (obstacle->id() == id_last_collision_)
        return recompute;

    x1 = coords1.at(0)[0];
    y1 = coords1.at(0)[1];
    z1 = coords1.at(0)[2];
    x2 = coords2.at(0)[0];
    y2 = coords2.at(0)[1];
    z2 = coords2.at(0)[2];

    h1 = coords1.at(3)[1] - y1;
    w1 = coords1.at(1)[0] - x1;
    d1 = coords1.at(4)[2] - z1;
    h2 = coords2.at(3)[1] - y2;
    w2 = coords2.at(1)[0] - x2;
    d2 = coords2.at(4)[2] - z2;

    /* 1/10 precision */
    while (fact < 11) {
        x1 += 0.1 * border_.move()[0];
        y1 += 0.1 * border_.move()[1];
        z1 += 0.1 * border_.move()[2];
        x2 += 0.1 * border2.move()[0];
        y2 += 0.1 * border2.move()[1];
        z2 += 0.1 * border2.move()[2];
        if ((x2 >= x1 + w1)      /* Too much at right */
            || (x2 + w2 <= x1) /* Too much at left */
            || (y2 + h2 >= y1) /* Too much at top */
            || (y2 <= y1 + h1)  /* Too much at bottom */
            || (z2 <= z1 + d1)   /* Too much at back */
            || (z2 + d2 >= z1)) { /* Too much at front */
                fact++;
            continue;
        } else {
            /* Back 1/0 move */
            x1 -= 0.1 * border_.move()[0];
            y1 -= 0.1 * border_.move()[1];
            z1 -= 0.1 * border_.move()[2] ;
            x2 -= 0.1 * border2.move()[0];
            y2 -= 0.1 * border2.move()[1];
            z2 -= 0.1 * border2.move()[2];

            /* 1/100 precision */
            fact2 = 1;
            while (1) {
                x1 += 0.001 * border_.move()[0];
                y1 += 0.001 * border_.move()[1];
                z1 += 0.001 * border_.move()[2] ;
                x2 += 0.001 * border2.move()[0];
                y2 += 0.001 * border2.move()[1];
                z2 += 0.001 * border2.move()[2];
                if ((x2 >= x1 + w1)
                        || (x2 + w2 <= x1)
                        || (y2 + h2 >= y1)
                        || (y2 <= y1 + h1)
                        || (z2 <= z1 + d1)
                        || (z2 + d2 >= z1)) {
                        ++fact2;
                        continue;
                }

                break;
            }

            /* Compute distance and update collision properties if needed */
            distance = 0.1 * (fact - 1) + 0.001 * (fact2 - 1);
            if ((obstacle_ == nullptr || distance < distance_) &&
                (obstacle->obstacle() == nullptr || distance < obstacle->distance())) {

                std::cerr << "Obstacle::" << obstacle->id() << ", distance::" << distance << std::endl;
                oldobstacle1 = obstacle_;
                oldobstacle2 = obstacle->obstacle();

                obstacle_ = obstacle;
                distance_ = distance;
                obstacle_->set_distance(distance);
                obstacle_->set_obstacle(this);

                /* Recompute for polygons unbinded */
                if (oldobstacle1 != nullptr) {
                    oldobstacle1->set_distance(-1);
                    oldobstacle1->set_obstacle(nullptr);
                    if (oldobstacle1->IsMoved())
                        recompute.push_back(std::move(oldobstacle1));
                }

                if (oldobstacle2 != nullptr && oldobstacle2->IsMoved()) {
                    oldobstacle2->set_distance(-1);
                    oldobstacle2->set_obstacle(nullptr);
                    recompute.push_back(std::move(oldobstacle2));
                }

                oldobstacle1 = nullptr;
                oldobstacle2 = nullptr;

                return recompute;
            }
        }
        fact = 11;
    }

    return recompute;

}

}//namespace geometry
}//namespace engine
