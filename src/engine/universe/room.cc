/*
* Room class file
* @author Eric Fehr (ricofehr@nextdeploy.io, @github: ricofehr)
*/

#include "engine/universe/room.h"

#include <iostream>
#include <map>

#include "engine/core/config_engine.h"

namespace engine {
namespace universe {

/* Constructors */
Room::Room()
     :Room(glm::vec4(1.0f)) {}

Room::Room(glm::vec4 location)
     :Room(location, nullptr){}

Room::Room(glm::vec4 location, std::unique_ptr<Camera> cam)
     :Room(location, std::vector<bool>(6, false), std::vector<bool>(6, false), std::move(cam)){}

Room::Room(glm::vec4 location, std::vector<bool> is_doors, std::vector<bool> is_windows,
           std::unique_ptr<Camera> cam) {
    location_ = location;
    type_ = kMODEL3D_ROOM;
    using engine::geometry::Box;
    border_ = Box(glm::vec3(kGRID_X*kGRID_UNIT/2, kGRID_Y*kGRID_UNIT/2, kGRID_Z*kGRID_UNIT/2), location);
    doors_ = is_doors;
    windows_ = is_windows;

    /* Check objects count into config file */
    using engine::core::ConfigEngine;
    nbobjects_ = ConfigEngine::getSetting<int>("objects_count");

    /* Push cam in objects_ array */
    if (cam != nullptr) {
        cam_ = cam.get();
        objects_.push_back(std::move(cam));
    }
}

/* Create 3D walls for Room */
void Room::GenerateWalls() {
    glm::vec3 scale_w = {1.0f, 1.0f, 1.0f};
    glm::vec4 location_0 {0.0f};
    glm::vec4 location_w {0.0f};

    /* First Room 3D Point */
    location_0 = location_ - glm::vec4(kGRID_X*kGRID_UNIT/2, kGRID_Y*kGRID_UNIT/2, kGRID_Z*kGRID_UNIT/2, 0.0f);

    auto it_doors = doors_.begin();
    auto it_windows = windows_.begin();

    /* Top and Roof */
    scale_w = {(kGRID_X/8)*kGRID_UNIT, kGRID_UNIT/4, (kGRID_Z/8)*kGRID_UNIT};
    for (auto i = 0; i < kGRID_Y+1; i+=(kGRID_Y)) {
        cilk_for (auto j = 0; j < kGRID_X; j+=kGRID_X/4) {
            cilk_for (auto k = 0; k < kGRID_Z; k+=kGRID_Z/4) {
                /* No brick floor/roof if trapdoor */
                if (!*it_doors || (j != 2*kGRID_X/4 && j != 3*kGRID_X/4) || (k != 2*kGRID_X/4 && k != 3*kGRID_X/4)) {
                    tbb::mutex::scoped_lock lock(room_mutex_);
                    location_w = location_0 + glm::vec4(scale_w[0], 0.0f, scale_w[2], 0.0f) + glm::vec4 {j*kGRID_UNIT, i*kGRID_UNIT, k*kGRID_UNIT, 0.0f};
                    if (i == 0) {
                        location_w[1] += kGRID_UNIT/4;
                    } else {
                        location_w[1] -= kGRID_UNIT/4;
                    }
                    auto wall_ptr{std::make_unique<Wall>(scale_w, location_w, (i == 0) ? static_cast<int>(Wall::kTEXTURE_FLOOR): static_cast<int>(Wall::kTEXTURE_TOP))};
                    objects_.push_back(std::move(wall_ptr));
                 }
            }
        }
        ++it_doors;
        ++it_windows;
    }

    scale_w = {kGRID_UNIT/4, (kGRID_Y/6)*kGRID_UNIT, (kGRID_Z/8)*kGRID_UNIT};
    for (auto i = 0; i < kGRID_X+1; i+=(kGRID_X)) {
        cilk_for (auto j = 0; j < kGRID_Y; j+=kGRID_Y/3) {
            cilk_for (auto k = 0; k < kGRID_Z; k+=kGRID_Z/4) {
                /* No brick wall if Doors or Windows */
                if ((!*it_doors || j > kGRID_Y/3 || k != 0) &&
                    (!*it_windows || j != kGRID_Y/3 || (k != 2*kGRID_Z/4 && k != 3*kGRID_Z/4))) {
                    tbb::mutex::scoped_lock lock(room_mutex_);
                    location_w = location_0 + glm::vec4(0.0f, scale_w[1], scale_w[2], 0.0f) + glm::vec4 {i*kGRID_UNIT, j*kGRID_UNIT, k*kGRID_UNIT, 0.0f};
                    if (i == 0) {
                        location_w[0] += kGRID_UNIT/4;
                    } else {
                        location_w[0] -= kGRID_UNIT/4;
                    }
                    auto wall_ptr{std::make_unique<Wall>(scale_w, location_w, static_cast<int>(Wall::kTEXTURE_WALL))};
                    objects_.push_back(std::move(wall_ptr));
                }
            }
        }
        ++it_doors;
        ++it_windows;
    }

    scale_w = {(kGRID_X/8)*kGRID_UNIT, (kGRID_Y/6)*kGRID_UNIT, kGRID_UNIT/4};
    for (auto i = 0; i < kGRID_Z+1; i+=(kGRID_Z)) {
        cilk_for (auto j = 0; j < kGRID_Y; j+=kGRID_Y/3) {
            cilk_for (auto k = 0; k < kGRID_X; k+=kGRID_X/4) {
                /* No brick wall if Doors or Windows */
                if ((!*it_doors || j > kGRID_Y/3 || k != 0) &&
                    (!*it_windows || j != kGRID_Y/3 || (k != 2*kGRID_X/4 && k != 3*kGRID_X/4))) {
                    tbb::mutex::scoped_lock lock(room_mutex_);
                    location_w = location_0 + glm::vec4(scale_w[0], scale_w[1], 0.0f, 0.0f) + glm::vec4 {k*kGRID_UNIT, j*kGRID_UNIT, i*kGRID_UNIT, 0.0f};
                    if (i == 0) {
                        location_w[2] += kGRID_UNIT/4;
                    } else {
                        location_w[2] -= kGRID_UNIT/4;
                    }
                    auto wall_ptr{std::make_unique<Wall>(scale_w, location_w, static_cast<int>(Wall::kTEXTURE_WALL))};
                    objects_.push_back(std::move(wall_ptr));
                }
            }
        }
        ++it_doors;
        ++it_windows;
    }
}

/* Generates Random bricks into Room */
void Room::GenerateObjects()
{
    ReinitGrid();

    /* If sequentially object creation, return */
    using engine::core::ConfigEngine;
    if (ConfigEngine::getSetting<float>("load_objects_freq") != 0.0f) {
        return;
    }

    while (nbobjects_) {
        GenerateRandomObject();
    }
}

/* Generates Random bricks into Room */
void Room::GenerateRandomObject()
{
    int index = objects_.size();
    float x = 0.0f, y = 0.0f, z = 0.0f;
    float scale = 1.0f;
    int x0 = 0, z0 = 0;

    /* Entropy value */
    auto r = rand();
    auto s = rand();
    auto t = rand();
    /* For sizes available */
    scale = 1.0f / (float)(index % 3 + 2.0);

    /* 1/7 moves on y axis */
    if (index % 7 == 0) {
        y = (rand() % 20 + 3) * 0.007f;
        x = 0.0f;
        z = 0.0f;
    } else {
        x = (rand() % 20 + 3) * 0.007f;
        x = (r % 2 == 0) ? -x : x;
        z = (rand() % 20 + 3) * 0.007f;
        z = (r % 3 == 0) ? -z : z;
        y = 0.0f;
    }

    /* First 3D point into Room */
    auto grid_0 = location_ - glm::vec4(kGRID_X*kGRID_UNIT/2, kGRID_Y*kGRID_UNIT/2, kGRID_Z*kGRID_UNIT/2, 0.0f);

    auto i = r;
    auto j = s;
    auto k = t;
    auto cnt = 0;
    /* Generate and place randomly object into room grid */
    while (cnt++ < (kGRID_Y-1) * (kGRID_X-1) * (kGRID_Z-1)) {
        auto l = r % (kGRID_Y-1);
        auto m = s % (kGRID_X-1);
        auto n = t % (kGRID_Z-1);

        auto y2 = grid_0[1] + l * kGRID_UNIT + kGRID_UNIT/2;
        auto x2 = grid_0[0] + m * kGRID_UNIT + kGRID_UNIT/2;
        auto z2 = grid_0[2] + n * kGRID_UNIT + kGRID_UNIT/2;

        grid_mutex_.lock();
        if (grid_[l][m][n].size() == 0) {
            Model3D *obj = GenerateObject(Model3D::kMODEL3D_BRICK, glm::vec4(x2, y2, z2, 0.0f),
                                          glm::vec4(x, y, z, 0.0f), scale);
            obj->add_placement(l, m, n);

            /* Lock room for ensure only one change at same time on grid_ array */
            grid_[l][m][n].push_back(obj);
            --nbobjects_;
            grid_mutex_.unlock();
            return;
        }
        grid_mutex_.unlock();

        switch (i % 6) {
        case 0:
            if (++t - k == kGRID_Z) {
                t = k;
                if (++s - j == kGRID_X) {
                    s = j;
                    r++;
                }
            }
            break;

        case 1:
            if (++s - j == kGRID_Z) {
                s = j;
                if (++r - i == kGRID_Y) {
                    r = i;
                    t++;
                }
            }
            break;

        case 2:
            if (++t - k == kGRID_Z) {
                t = k;
                if (++r - i == kGRID_Y) {
                    r = i;
                    s++;
                }
            }
            break;

        case 3:
            if (++s - j == kGRID_X) {
                s = j;
                if (++t - k == kGRID_Z) {
                    t = k;
                    r++;
                }
            }
            break;

        case 4:
            if (++r - i == kGRID_Y) {
                r = i;
                if (++t - k == kGRID_Z) {
                    t = k;
                    s++;
                }
            }
            break;

        case 5:
            if (++r - i == kGRID_Y) {
                r = i;
                if (++s - j == kGRID_X) {
                    s = j;
                    t++;
                }
            }
            break;
        }
    }
}

/* Create a moving object into Room */
Model3D *Room::GenerateObject(int type_object, glm::vec4 location, glm::vec4 move, float scale)
{
    int ind = objects_.size();
    std::unique_ptr<Model3D> obj_ptr;

    /* Lock room for ensure only one change at same time on objects_ array */
    tbb::mutex::scoped_lock lock(room_mutex_);

    /* Create Brick object and add to the Current Room */
    if (type_object == Model3D::kMODEL3D_BRICK) {
        obj_ptr = std::make_unique<Brick>(scale, location, move);
    }

    objects_.push_back(std::move(obj_ptr));
    return objects_[ind].get();
}

/* Draw room and all objects inside it */
void Room::Draw(Camera *cam)
{
    /* If current Room, compute new Camera GL Coords */
    if (cam_ != nullptr) {
        cam_->PrepareDraw(cam);
    }

    /* Compute objects GL coords  */
    cilk_for (auto cnt = 0; cnt < objects_.size(); cnt++) {
        if (objects_[cnt]->type() != Model3D::kMODEL3D_CAMERA) {
            objects_[cnt]->PrepareDraw(cam);
        }
    }

    /* GL draw in serial (must be not parallell !) */
    for (auto &o: objects_) {
        if (o->type() != Model3D::kMODEL3D_CAMERA) {
            o->Draw();
        }
    }
}

/* Detect collisions inside current room */
void Room::DetectCollision(std::vector<Room*> neighbors)
{
    /* First check camera collision */
    if (cam_ != nullptr &&
        cam_->IsMoved()) {
        PivotCollision(cam_, neighbors);
    }

    /* For all others moving objects
       Parallell loop with cilkplus */
    cilk_for (auto i = 0; i < objects_.size(); i++) {
        if (objects_[i]->IsMoved() && objects_[i]->type() != Model3D::kMODEL3D_CAMERA) {
            PivotCollision(objects_[i].get(), neighbors);
        }
    }
}

/* Detect all collision for one Object */
void Room::PivotCollision(Model3D *object, std::vector<Room*> neighbors)
{
    tbb::mutex pivot_mutex;
    /* ensure that 2 same objects are not checked at the same time */
    object->lock();

    /* Prepare an unique objects collection for collision detection */
    std::map<int, Model3D*> grid_objects;

    /* Grid coordinates for current object */
    std::vector<std::vector<int>> placements = object->get_placements();

    /* Check all grid placements for current object and select other objects near this one */
    cilk_for (auto p = 0; p < placements.size(); p++) {
        auto y = placements[p][0];
        auto x = placements[p][1];
        auto z = placements[p][2];

        /* Other room objects adding */
        cilk_for (auto i = y-1; i <= y+1; i++) {
            cilk_for (auto j = x-1; j <= x+1; j++) {
                if ((i != -1 && i != kGRID_Y) || (j != -1 && j != kGRID_X)) {
                    cilk_for (auto k = z-1; k <= z+1; k++) {
                        if (((i != -1 && i != kGRID_Y) || (k != -1 && k != kGRID_Z)) &&
                            ((j != -1 && j != kGRID_X) || (k != -1 && k != kGRID_Z))) {

                            std::vector<Model3D*> targets;

                            if (i < 0) {
                                if (neighbors[kFLOOR] != nullptr) {
                                    targets = neighbors[kFLOOR]->getObjects(kGRID_Y-1, j, k);
                                }
                            } else if (i == kGRID_Y) {
                                if (neighbors[kROOF] != nullptr) {
                                    targets = neighbors[kROOF]->getObjects(0, j, k);
                                }
                            } else if (j < 0) {
                                if (neighbors[kLEFT] != nullptr) {
                                    targets = neighbors[kLEFT]->getObjects(i, kGRID_X-1, k);
                                }
                            } else if (j == kGRID_X) {
                                if (neighbors[kRIGHT] != nullptr) {
                                    targets = neighbors[kRIGHT]->getObjects(i, 0, k);
                                }
                            } else if (k < 0) {
                                if (neighbors[kFRONT] != nullptr) {
                                    targets = neighbors[kFRONT]->getObjects(i, j, kGRID_Z-1);
                                }
                            } else if (k == kGRID_Z) {
                                if (neighbors[kBACK] != nullptr) {
                                    targets = neighbors[kBACK]->getObjects(i, j, 0);
                                }
                            } else {
                                targets = grid_[i][j][k];
                            }

                            /* Merge targets with collisions array */
                            for (auto &obj : targets) {
                                if (*obj != *object) {
                                    tbb::mutex::scoped_lock lock_map(pivot_mutex);
                                    grid_objects[obj->id()] = obj;
                                }
                            }
                        } //fi: test on i and k, j and k
                    } //cilk_for k
                } //fi: test on i and j
            } //cilk_for j
        } //cilk_for i
    } //cilk_for placements

    /* Prepare vector for collision compute */
    std::vector<Model3D*> room_objects;
    for (auto & obj_pair : grid_objects) {
        room_objects.push_back(obj_pair.second);
    }

    /* Parallell collision loop for objects with cilkplus */
    std::map<int, std::vector<Model3D*>> recompute;
    cilk_for (auto i = 0; i < room_objects.size(); i++) {
        /* Abort program if object and room_object loop are same (must no happend) */
        assert(*object != *room_objects[i]);

        std::vector<Model3D*> collision_recompute = collision_engine_->DetectCollision(object, room_objects[i], room_mutex_);
        if (collision_recompute.size() > 0) {
            recompute[room_objects[i]->id()] = collision_recompute;
        }
    }

    /* end mutex lock */
    object->unlock();

    /* If collision detected, recompute older ones if exists */
    if (object->obstacle() != nullptr ) {
        try {
            for (auto & r : recompute.at(object->obstacle()->id())) {
                using engine::core::ConfigEngine;
                if (ConfigEngine::getSetting<int>("debug") >= ConfigEngine::kDEBUG_COLLISION) {
                    std::cout << "Recompute " << object->id() << "::" << r->id() << std::endl;
                }
                cilk_spawn PivotCollision(r, neighbors);
            }
        }
        /* Silently catched out-of-range (not a problem) */
        catch (const std::out_of_range& oor) {}

        cilk_sync;
    }
}

}//namespace universe
}//namespace engine
