#pragma once

#include "MouseCore/Quad/Quad.h"
#include "MouseCore/IndirectDraw.h"

typedef struct mouse_quadBatchable_t mouse_quadBatchable;

// use the current transformation of a quad to update an output buffer given some original mesh vertices
// use a staging buffer if threading a batch and then copy to gpu buffer synchronously
// send gpu buffer as output buffer if calling synchronously anyway
typedef void (*mouse_quadBatchable_updateBuffer)(mouse_quadBatchable* quadBatchable);

// a quad, function to update it's vertex buffer, staging vertex buffer, original vertices to transform from each time
struct mouse_quadBatchable_t
{
    mouse_quad* quad;
    mouse_quadBatchable_updateBuffer updateBuffer;
    float* vertices; // set to either an offset into the gpu buffer or a unique staging buffer
    float* originalVertices; // tracks an untransformed vertex buffer
};

mouse_quadBatchable* mouse_quadBatchable_createDefault();
mouse_quadBatchable* mouse_quadBatchable_create(mouse_quad* quad, mouse_quadBatchable_updateBuffer updateBuffer);
void mouse_quadBatchable_delete(mouse_quadBatchable* self);

void mouse_quadBatchable_updateBufferDefault(mouse_quadBatchable* quadBatchable);
