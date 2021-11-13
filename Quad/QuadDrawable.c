#include "MouseCore/Quad/QuadDrawable.h"
#include "MouseCore/Quad/QuadBufferHelpers.h"
#include <stdlib.h>
#include <stddef.h>

mouse_quadDrawable* mouse_quadDrawable_createDefault(GLuint shader)
{
    mouse_quadDrawable* quadDrawable = malloc(sizeof(mouse_quadDrawable));
    ;
    quadDrawable->buffers = mouse_quadBuffers_create(
        mouse_quadBufferHelpers_fillVerticesColorless(0.5f, 0.5f, 1.0f, 
        mouse_quadBufferHelpers_createVertices())
        );


    quadDrawable->shader = shader;
    quadDrawable->setShaderUniformsFn = &mouse_quadDrawable_setShaderUniformsDefault;
    quadDrawable->quad = mouse_quad_createDefault();

    return quadDrawable;
}

mouse_quadDrawable* mouse_quadDrawable_create(mouse_quad* quad, mouse_quadBuffers* quadBuffers, GLuint shader, mouse_quadDrawable_setShaderUniformsFn setShaderUniforms)
{
    mouse_quadDrawable* quadDrawable = malloc(sizeof(mouse_quadDrawable));

    quadDrawable->buffers = quadBuffers;
    quadDrawable->shader = shader;
    if(setShaderUniforms == NULL)
    {
        quadDrawable->setShaderUniformsFn = &mouse_quadDrawable_setShaderUniformsDefault;
    }
    else
    {
        quadDrawable->setShaderUniformsFn = setShaderUniforms;
    }
    
    quadDrawable->quad = quad;

    return quadDrawable;
}

void mouse_quadDrawable_delete(mouse_quadDrawable* self)
{
    mouse_quadBuffers_delete(self->buffers);
    mouse_quad_delete(self->quad);
    free(self);
}

void mouse_quadDrawable_draw(mouse_quadDrawable* self)
{
    glBindVertexArray(self->buffers->VAO);
    
    glUseProgram(self->shader);
    
    self->setShaderUniformsFn(self);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void mouse_quadDrawable_setShaderUniformsDefault(mouse_quadDrawable* self)
{
    mat4 model;
    mouse_transform_getModel(self->quad->transform, model);
    mouse_shader_setMat4(0, model);
    
    vec4 colorAlpha;
    glm_vec4(self->quad->color, self->quad->alpha, colorAlpha);
    mouse_shader_setVec4(1, colorAlpha);
}