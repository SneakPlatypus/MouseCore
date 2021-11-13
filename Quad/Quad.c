#include "MouseCore/Quad/Quad.h"
#include <stdlib.h>

mouse_quad* mouse_quad_createDefault()
{
    mouse_quad* quad = malloc(sizeof(mouse_quad));
    quad->transform = mouse_transform_createDefault();

    glm_vec3_one(quad->color);
    quad->alpha = 1.0f;
    
    return quad;
}

mouse_quad* mouse_quad_create(mouse_transform* transform, vec3 color, float alpha)
{
    mouse_quad* quad = malloc(sizeof(mouse_quad));
    quad->transform = transform;
    
    glm_vec3_copy(color, quad->color);
    quad->alpha = alpha;

    return quad;
}

void mouse_quad_delete(mouse_quad* self)
{
    mouse_transform_delete(self->transform);
    free(self);
}

void mouse_quad_drawDefault(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader)
{
    glBindVertexArray(quadBuffers->VAO);
    
    glUseProgram(shader);

    mouse_quad_setShaderUniformsDefault(quad, shader);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void mouse_quad_draw(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader, mouse_quad_setShaderUniformsFn setShaderUniforms)
{
    glBindVertexArray(quadBuffers->VAO);
    
    glUseProgram(shader);

    setShaderUniforms(quad, shader);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void mouse_quad_setShaderUniformsDefault(mouse_quad* quad, GLuint shader)
{
    mat4 model;
    mouse_transform_getModel(quad->transform, model);
    mouse_shader_setMat4(0, model);
    
    vec4 colorAlpha;
    glm_vec4(quad->color, quad->alpha, colorAlpha);
    mouse_shader_setVec4(1, colorAlpha);
}