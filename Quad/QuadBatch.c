#include "MouseCore/Quad/QuadBatch.h"
#include "MouseCore/IndirectDraw.h"
#include <stddef.h>

mouse_quadBatch* mouse_quadBatch_create(int maxQuads, int bufferStrategy, GLuint shader, mouse_quadBatch_setShaderUniformsFn setShaderUniforms)
{
    if(maxQuads <= 0) { return NULL; }

    mouse_quadBatch* quadBatch = malloc(sizeof(mouse_quadBatch));    
        
    quadBatch->mappedBuffer = mouse_persistentMappedBuffer_create(maxQuads * MOUSE_QUAD_FLOAT_COUNT * sizeof(float), 3);

    quadBatch->quads = malloc(sizeof(mouse_quadBatchable*) * maxQuads);
    quadBatch->quadCount = 0;
    quadBatch->maxQuads = maxQuads;

    quadBatch->shader = shader;
    quadBatch->setShaderUniforms = setShaderUniforms;

    return quadBatch;
}

void mouse_quadBatch_delete(mouse_quadBatch* self)
{
    mouse_persistentMappedBuffer_delete(self->mappedBuffer);
    for(int i=0; i<self->quadCount; i++)
    {
        mouse_quadBatchable_delete(self->quads[i]);
    }
    free(self->quads);
    free(self);
}

void mouse_quadBatch_add(mouse_quadBatch* self, mouse_quadBatchable* quad)
{
    if(self->quadCount >= self->maxQuads) { return; }

    self->quads[self->quadCount] = quad;
    self->quadCount++;
}

void mouse_quadBatch_remove(mouse_quadBatch* self, mouse_quadBatchable* quad)
{
    for(int i=0; i<self->quadCount; i++)
    {
        if(self->quads[i] == quad)
        {
            mouse_quadBatchable_delete(self->quads[i]);
            for(int j=i+1; j<self->quadCount;j++)
            {
                self->quads[j - 1] = self->quads[j];
            }
            self->quadCount--;
            break;
        }
    }
}

void mouse_quadBatch_removeAt(mouse_quadBatch* self, int index)
{
    if(index < 0 || index >= self->quadCount - 1) { return; }

    for(int i=index+1; i<self->quadCount;i++)
    {
        self->quads[i - 1] = self->quads[i];
    }
}

void mouse_quadBatch_updateCommands(mouse_quadBatch* self)
{

}

void mouse_quadBatch_draw(mouse_quadBatch* self)
{
    //glBindVertexArray(self->quadBuffers->VAO);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, self->mappedBuffer->buffer);

    glUseProgram(self->shader);
    self->setShaderUniforms(self);

    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, (GLvoid*)(self->mappedBuffer->writeIndex * self->maxQuads * sizeof(DrawElementsIndirectCmd)), self->quadCount, sizeof(DrawElementsIndirectCmd));

    mouse_persistentMappedBuffer_lockWriteBuffer(self->mappedBuffer);
    mouse_persistentMappedBuffer_incrementWriteIndex(self->mappedBuffer);
}

