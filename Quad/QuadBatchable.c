#include "MouseCore/Quad/QuadBatchable.h"
#include <stddef.h>

mouse_quadBatchable* mouse_quadBatchable_createDefault()
{
    mouse_quadBatchable* quadBatchable = malloc(sizeof(mouse_quadBatchable));
    
    quadBatchable->quad = mouse_quad_createDefault();
    quadBatchable->updateBuffer = &mouse_quadBatchable_updateBufferDefault;
    
    return quadBatchable;
}

mouse_quadBatchable* mouse_quadBatchable_create(mouse_quad* quad, mouse_quadBatchable_updateBuffer updateBuffer)
{
    mouse_quadBatchable* quadBatchable = malloc(sizeof(mouse_quadBatchable));
    
    quadBatchable->quad = quad;
    if(updateBuffer == NULL)
    {
        quadBatchable->updateBuffer = &mouse_quadBatchable_updateBufferDefault;
    }
    else
    {
        quadBatchable->updateBuffer = updateBuffer;
    }

    return quadBatchable;
}

void mouse_quadBatchable_delete(mouse_quadBatchable* self)
{
    mouse_quad_delete(self->quad);
    free(self);
}

void mouse_quadBatchable_updateBufferDefault(mouse_quadBatchable* quadBatchable)
{
    mat4 model;
    mouse_transform_getModel(quadBatchable->quad->transform, model);
    
    // get the 4 vertices without any transformation applied
    vec4 vertices[4] = { 
        { quadBatchable->originalVertices[0], quadBatchable->originalVertices[1], 0.0f, 1.0f },
        { quadBatchable->originalVertices[8], quadBatchable->originalVertices[9], 0.0f, 1.0f },
        { quadBatchable->originalVertices[16], quadBatchable->originalVertices[17], 0.0f, 1.0f },
        { quadBatchable->originalVertices[24], quadBatchable->originalVertices[25], 0.0f, 1.0f }
    };

    // apply current transformation
    vec4 modelVertices[4];
    glm_mat4_mulv(model, vertices[0], modelVertices[0]);
    glm_mat4_mulv(model, vertices[1], modelVertices[1]);
    glm_mat4_mulv(model, vertices[2], modelVertices[2]);
    glm_mat4_mulv(model, vertices[3], modelVertices[3]);

    // update current vertex buffer
    quadBatchable->vertices[0] = modelVertices[0][0];
    quadBatchable->vertices[1] = modelVertices[0][1];

    quadBatchable->vertices[0] = modelVertices[1][0];
    quadBatchable->vertices[0] = modelVertices[1][1];

    quadBatchable->vertices[0] = modelVertices[2][0];
    quadBatchable->vertices[0] = modelVertices[2][1];

    quadBatchable->vertices[0] = modelVertices[3][0];
    quadBatchable->vertices[0] = modelVertices[3][1];
}