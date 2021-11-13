#include "MouseCore/Quad/QuadBuffersMapped.h"
#include <stdlib.h>

mouse_quadBuffersMapped* mouse_quadBuffersMapped_create()
{
    mouse_quadBuffersMapped* quadMapped = malloc(sizeof(mouse_quadBuffersMapped));
    
    quadMapped->mappedBuffer = mouse_persistentMappedBuffer_create(sizeof(float) * MOUSE_QUAD_FLOAT_COUNT, 3);

    return quadMapped;
}

void mouse_quadBuffersMapped_delete(mouse_quadBuffersMapped* self)
{
    glDeleteVertexArrays(1, &self->VAO);
    glDeleteBuffers(1, &self->indexBuffer);
    mouse_persistentMappedBuffer_delete(self->mappedBuffer);
    free(self);
}