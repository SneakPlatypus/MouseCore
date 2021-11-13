#pragma once

#include "MouseCore/Quad/QuadBuffers.h"
#include "MouseCore/Transform.h"
#include "MouseCore/Shader.h"

typedef struct mouse_quad_t
{
    mouse_transform* transform;
    vec3 color;
    float alpha;
} mouse_quad;

typedef void (*mouse_quad_setShaderUniformsFn)(mouse_quad* quad, GLuint shader);

mouse_quad* mouse_quad_createDefault();
mouse_quad* mouse_quad_create(mouse_transform* transform, vec3 color, float alpha);

void mouse_quad_delete(mouse_quad* self);

void mouse_quad_drawDefault(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader);
void mouse_quad_draw(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader, mouse_quad_setShaderUniformsFn setShaderUniforms);

void mouse_quad_setShaderUniformsDefault(mouse_quad* quad, GLuint shader);