#include "MouseCore/Spine/SpineBuffers.h"


typedef enum mouse_spineBuffers_name_e
{
    MOUSE_SPINEBUFFERS_NAME_VERTEX,
    MOUSE_SPINEBUFFERS_NAME_INDEX,
    MOUSE_SPINEBUFFERS_NAME_COUNT
} mouse_spineBuffers_name;

mouse_spineBuffers* mouse_spineBuffers_create(int vertexCount, int indexCount)
{
    mouse_spineBuffers* spineBuffers = malloc(sizeof(mouse_spineBuffers));
    
    glCreateVertexArrays(1, &spineBuffers->VAO);
    glCreateBuffers(MOUSE_SPINEBUFFERS_NAME_COUNT, spineBuffers->buffers);


}

void mouse_spineBuffers_delete(mouse_spineBuffers* self)
{
    glDeleteVertexArrays(1, &self->VAO);
    glDeleteBuffers(MOUSE_SPINEBUFFERS_NAME_COUNT, self->buffers);
    free(self);
}