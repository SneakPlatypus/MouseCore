#pragma once

#include "MouseCore/Quad/Quad.h"
#include "MouseCore/Quad/QuadBatchable.h"
#include "MouseCore/PersistentMappedBuffer.h"
#include "MouseCore/DataStructures/LinkedList.h"

typedef struct mouse_quadBatch_t mouse_quadBatch;

typedef void (*mouse_quadBatch_setShaderUniformsFn)(mouse_quadBatch* quadBatch);

struct mouse_quadBatch_t
{
    mouse_persistentMappedBuffer* mappedBuffer;
    mouse_quadBatchable** quads;
    int quadCount;
    int maxQuads;
    GLuint shader;
    mouse_quadBatch_setShaderUniformsFn setShaderUniforms;
};

mouse_quadBatch* mouse_quadBatch_create(int maxQuads, int bufferStrategy, GLuint shader, mouse_quadBatch_setShaderUniformsFn setShaderUniforms);
void mouse_quadBatch_delete(mouse_quadBatch* self);

void mouse_quadBatch_add(mouse_quadBatch* self, mouse_quadBatchable* quad);
void mouse_quadBatch_remove(mouse_quadBatch* self, mouse_quadBatchable* quad);
void mouse_quadBatch_removeAt(mouse_quadBatch* self, int index);

void mouse_quadBatch_update(mouse_quadBatch* self);

void mouse_quadBatch_draw(mouse_quadBatch* self);