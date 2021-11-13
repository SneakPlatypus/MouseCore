#pragma once

// QuadBuffers.h automates the creation of a basic quad buffer
// a VAO is generated with one vertex/textureCoordinate/color buffer and one index buffer

#include <GL/glew.h>
#include "MouseCore/PersistentMappedBuffer.h"
#include "MouseCore/Quad/QuadBufferHelpers.h"

typedef enum mouse_quadBuffers_name_e
{
    MOUSE_QUADBUFFERS_NAME_VERTEX = 0,
    MOUSE_QUADBUFFERS_NAME_INDEX,
    MOUSE_QUADBUFFERS_NAME_COUNT
} mouse_quadBuffers_name;

typedef struct mouse_quadBuffers_t_prv mouse_quadBuffers_prv;

typedef struct mouse_quadBuffers_t
{
    GLuint VAO;
    mouse_quadBuffers_prv* prv;
} mouse_quadBuffers;

// allocates and returns a struct containing a VAO and 2 buffers (vertex/textureCoordinates, index) using DSA
// expects a float array allocated from any form of mouse_quadBufferHelpers_createVertices[..](...);
// function takes ownership of the vertex buffer and frees it
mouse_quadBuffers* mouse_quadBuffers_create(float* quadVertices);
// delete gl buffers and free struct
void mouse_quadBuffers_delete(mouse_quadBuffers* self);
