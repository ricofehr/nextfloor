/**
 *  @file gl_cube_renderer.cc
 *  @brief GlCubeRenderer class file
 *  @author Eric Fehr (ricofehr@nextdeploy.io, github: ricofehr)
 */

#include "nextfloor/renderer/cube_gl_renderer_engine.h"

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "stb_image.h"

namespace nextfloor {

namespace renderer {

namespace {

// clang-format off
/* Brick vertex (3) / color (3) / texture (2) coordinates */
const GLfloat sBufferData[192] = {
    /* Front */
    -1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    /* Right */
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    /* Back */
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    /* Left */
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    /* Bottom */
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
    /* Top */
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,
};
// clang-format on

}  // namespace

CubeGlRendererEngine::CubeGlRendererEngine(const std::string& texture, PipelineProgram* pipeline_program)
      : GlRendererEngine(pipeline_program)
{
    texture_ = texture;
}

void CubeGlRendererEngine::Init()
{
    CreateVertexBuffer();
    CreateElementBuffer();
    CreateTextureBuffer();
    InitShaderAttributes();
    is_initialized_ = true;
}

/*
 *  Fill vertex buffer
 */
void CubeGlRendererEngine::CreateVertexBuffer()
{
    glGenVertexArrays(1, &vertexarray_);
    glGenBuffers(1, &vertexbuffer_);
    assert(vertexbuffer_ != 0);

    glBindVertexArray(vertexarray_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sBufferData), sBufferData, GL_STATIC_DRAW);
}

/* Load element coordinates into buffer */
void CubeGlRendererEngine::CreateElementBuffer()
{
    // clang-format off
    GLuint elements[] = {
        /* front */
        0, 1, 2,
        2, 3, 0,
        /* right */
        4, 5, 6,
        6, 7, 4,
        /* back */
        8, 9, 10,
        10, 11, 8,
        /* left */
        12, 13, 14,
        14, 15, 12,
        /* bottom */
        16, 17, 18,
        18, 19, 16,
        /* top */
        20, 21, 22,
        22, 23, 20,
    };
    // clang-format on

    glGenBuffers(1, &elementbuffer_);
    assert(elementbuffer_ != 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

void CubeGlRendererEngine::InitShaderAttributes()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

/*
 *  Fill texture buffer
 */
void CubeGlRendererEngine::CreateTextureBuffer()
{
    int width, height, nr_channels;
    unsigned char* image;

    glGenTextures(1, &texturebuffer_);
    assert(texturebuffer_ != 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturebuffer_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* Minification Filter (Shrink the texture) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    /* Magnification filter (Stretch the texture) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Load Texture */
    image = stbi_load(texture_.c_str(), &width, &height, &nr_channels, 0);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture:" << texture_ << "::" << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(image);
    glUseProgram(pipeline_program_->getProgramId());
    glUniform1i(glGetUniformLocation(pipeline_program_->getProgramId(), "tex"), 0);
}

void CubeGlRendererEngine::Draw(const glm::mat4& mvp)
{
    if (!is_initialized_) {
        Init();
    }

    glBindVertexArray(vertexarray_);
    glUseProgram(pipeline_program_->getProgramId());
    /* Assign projection matrix to drawn */
    glUniformMatrix4fv(pipeline_program_->getMatrixId(), 1, GL_FALSE, &mvp[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturebuffer_);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

CubeGlRendererEngine::~CubeGlRendererEngine()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDeleteVertexArrays(1, &vertexarray_);
    glDeleteBuffers(1, &vertexbuffer_);
    glDeleteBuffers(1, &texturebuffer_);
    glDeleteBuffers(1, &elementbuffer_);
}

}  // namespace renderer

}  // namespace nextfloor
