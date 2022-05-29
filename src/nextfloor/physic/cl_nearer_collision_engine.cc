/**
 *  @file cl_collision_engine.cc
 *  @brief CLCollisionEngine class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/physic/cl_nearer_collision_engine.h"

#include <fstream>
#include <vector>
#include <glm/glm.hpp>

#ifdef __APPLE__
#include <OpenCL/cl2.hpp>
#else
#include <CL/cl2.hpp>
#endif

#include "nextfloor/mesh/border.h"

namespace nextfloor {

namespace physic {

ClNearerCollisionEngine::ClNearerCollisionEngine(int granularity) : NearerCollisionEngine(granularity)
{
    InitCollisionEngine();
}

void ClNearerCollisionEngine::InitCollisionEngine()
{
    cl::Platform platform_target;
    cl::Device device_target;
    int max_cores = 0;
    size_t num;

    /* Query for platforms */
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    /* Select best devices in the workstation */
    std::vector<cl::Device> devices;
    for (auto& pf : platforms) {
        pf.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        for (auto& dev : devices) {
            size_t num;
            dev.getInfo(CL_DEVICE_MAX_COMPUTE_UNITS, &num);
            if (num > max_cores) {
                platform_target = pf;
                device_target = dev;
                max_cores = num;
            }
        }
    }

    /* Ensure items size  are valid */
    size_t nums[3]{0};
    device_target.getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES, &nums);
    while (nums[0] < granularity_) {
        granularity_ /= 2;
    }

    /* Create a context for the devices */
    cl::Context context(device_target);

    /* Create a command-queue for the first device */
    cl_queue_ = cl::CommandQueue(context, device_target);

    /* Create the memory buffers */
    bufferin_.push_back(cl::Buffer(context, CL_MEM_READ_ONLY, kBufferSize * sizeof(float)));
    bufferin_.push_back(cl::Buffer(context, CL_MEM_READ_ONLY, kBufferSize * sizeof(float)));
    bufferout_.push_back(cl::Buffer(context, CL_MEM_WRITE_ONLY, granularity_ * sizeof(float)));

    /* Read the program Source */
    std::ifstream source_file("cl/collision_kernel.cl");
    std::string source_code(std::istreambuf_iterator<char>(source_file), (std::istreambuf_iterator<char>()));
    cl::Program::Sources source(1, source_code);

    /* Create the program from the source code */
    cl::Program program = cl::Program(context, source);

    /* Compile the program for the devices */
    program.build(std::vector<cl::Device>(1, device_target));

    /* Create the kernel */
    cl_kernel_ = cl::Kernel(program, "collision");

    /* Ensure items size and wkgroup size are valid */
    cl_kernel_.getWorkGroupInfo(device_target, CL_KERNEL_WORK_GROUP_SIZE, &num);
    while (num < wk_size_) {
        wk_size_ /= 2;
    }
}

PartialMove ClNearerCollisionEngine::ComputeCollision(nextfloor::mesh::Mesh* target, nextfloor::mesh::Mesh* obstacle)
{
    nextfloor::mesh::Border* target_border = target->border();
    nextfloor::mesh::Border* obstacle_border = obstacle->border();

    /* All tbb threads share same opencl objects, need mutex */
    collision_mutex_.lock();

    float* distances_ptr = new float[granularity_];
    PartialMove ret = {1.0f, glm::vec3(1.0f)};

    std::vector<glm::vec3> coords1 = target_border->getCoordsModelMatrixComputed();
    std::vector<glm::vec3> coords2 = obstacle_border->getCoordsModelMatrixComputed();

    /* First polygon point (x,y,z) and dimensions (h,w,d) */
    float x1, y1, z1, h1, w1, d1;
    float x2, y2, z2, h2, w2, d2;
    float move1x, move1y, move1z, move2x, move2y, move2z;

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

    move1x = target_border->movement()[0];
    move1y = target_border->movement()[1];
    move1z = target_border->movement()[2];
    move2x = obstacle_border->movement()[0];
    move2y = obstacle_border->movement()[1];
    move2z = obstacle_border->movement()[2];

    /* Prepare arrays for computecollision */
    float box1[kBufferSize] = {x1, y1, z1, w1, h1, d1, move1x, move1y, move1z};
    float box2[kBufferSize] = {x2, y2, z2, w2, h2, d2, move2x, move2y, move2z};

    /* Copy the input data to the input buffer */
    cl_queue_.enqueueWriteBuffer(bufferin_[0], CL_TRUE, 0, kBufferSize * sizeof(float), box1);
    cl_queue_.enqueueWriteBuffer(bufferin_[1], CL_TRUE, 0, kBufferSize * sizeof(float), box2);
    cl_queue_.enqueueWriteBuffer(bufferout_[0], CL_TRUE, 0, granularity_ * sizeof(float), distances_ptr);

    /* Set kernel arguments */
    cl_kernel_.setArg(0, bufferin_[0]);
    cl_kernel_.setArg(1, bufferin_[1]);
    cl_kernel_.setArg(2, bufferout_[0]);

    /* Execute the kernel (1 workitem in 10 workgroup => compute distance for the 10 fact) */
    cl::NDRange global(granularity_);
    cl::NDRange local(wk_size_);
    cl_queue_.enqueueNDRangeKernel(cl_kernel_, cl::NullRange, global, local);

    /* Copy the output data back to the host */
    cl_queue_.enqueueReadBuffer(bufferout_[0], CL_TRUE, 0, granularity_ * sizeof(float), distances_ptr);

    for (auto i = 0; i < granularity_; i++) {
        if (distances_ptr[i] != 1.0f) {
            ret = {distances_ptr[i], glm::vec3(-1.0f)};
            break;
        }
    }

    delete[] distances_ptr;
    collision_mutex_.unlock();

    return ret;
}

}  // namespace physic

}  // namespace nextfloor
