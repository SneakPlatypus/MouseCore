#pragma once

#include "MouseCore/Quad/QuadBuffers.h"
#include "MouseCore/PersistentMappedBuffer.h"

// single quad buffer persistently mapped
typedef struct mouse_quadBuffersMapped_t
{
    GLuint VAO;
    GLuint indexBuffer;
    mouse_persistentMappedBuffer* mappedBuffer;
} mouse_quadBuffersMapped;

mouse_quadBuffersMapped* mouse_quadBuffersMapped_create();
void mouse_quadBuffersMapped_delete(mouse_quadBuffersMapped* self);