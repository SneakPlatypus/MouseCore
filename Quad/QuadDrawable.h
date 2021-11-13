#pragma once

#include "MouseCore/Quad/Quad.h"

typedef struct mouse_quadDrawable_t mouse_quadDrawable;

typedef void (*mouse_quadDrawable_setShaderUniformsFn)(mouse_quadDrawable* quad);

struct mouse_quadDrawable_t
{
    mouse_quad* quad;
    mouse_quadBuffers* buffers;
    GLuint shader;
    mouse_quadDrawable_setShaderUniformsFn setShaderUniformsFn;
};

mouse_quadDrawable* mouse_quadDrawable_createDefault(GLuint shader);
mouse_quadDrawable* mouse_quadDrawable_create(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader, mouse_quadDrawable_setShaderUniformsFn setShaderUniforms);

void mouse_quadDrawable_delete(mouse_quadDrawable* self);

void mouse_quadDrawable_draw(mouse_quadDrawable* self);

void mouse_quadDrawable_setShaderUniformsDefault(mouse_quadDrawable* self);