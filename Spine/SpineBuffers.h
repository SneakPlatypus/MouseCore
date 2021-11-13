#pragma once 

#include <GL/glew.h>
#include <cglm/cglm.h>

typedef struct mouse_spineBuffers_t
{
    GLuint VAO;
    GLuint* buffers;
} mouse_spineBuffers;

typedef struct mouse_spineBuffers_vertex_t
{
    vec3 position;
    vec2 uv;
    vec4 color;
} mouse_spineBuffers_vertex;

mouse_spineBuffers* mouse_spineBuffers_create(int vertexCount, int indexCount);
void mouse_spineBuffers_delete(mouse_spineBuffers* self);