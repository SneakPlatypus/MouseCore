#include "MouseCore/PersistentMappedBuffer.h"
#include <stdlib.h>

mouse_persistentMappedBuffer* mouse_persistentMappedBuffer_create(size_t dataSize, int bufferStrategy)
{
    if(bufferStrategy < 2) { return NULL; }

    mouse_persistentMappedBuffer* persistentMappedBuffer = malloc(sizeof(mouse_persistentMappedBuffer));
    
    persistentMappedBuffer->dataSize = dataSize;
    persistentMappedBuffer->bufferStrategy = bufferStrategy;

    int totalBufferSize = dataSize * bufferStrategy;
    
    glCreateBuffers(1, &persistentMappedBuffer->buffer);    
    
    GLbitfield flags = GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_WRITE_BIT; // mapping flags

    glNamedBufferStorage(persistentMappedBuffer->buffer, totalBufferSize, NULL, flags);

    persistentMappedBuffer->gpuMemory = glMapNamedBufferRange(persistentMappedBuffer->buffer, 0, totalBufferSize, GL_READ_WRITE);
    if(persistentMappedBuffer->gpuMemory == NULL)
    {
        return NULL;
    }

    persistentMappedBuffer->fences = malloc(bufferStrategy*sizeof(GLsync));

    return persistentMappedBuffer;
}

void mouse_persistentMappedBuffer_delete(mouse_persistentMappedBuffer* self)
{
    glUnmapNamedBuffer(self->buffer);
    glDeleteBuffers(1, &self->buffer);
    free(self->fences);
    free(self);
}

void mouse_persistentMappedBuffer_lockWriteBuffer(mouse_persistentMappedBuffer* self)
{
    if(self->fences[self->writeIndex])
    {
        glDeleteSync(self->fences[self->writeIndex]);	
    }
    self->fences[self->writeIndex] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

void mouse_persistentMappedBuffer_waitForLockedBuffer(mouse_persistentMappedBuffer* self)
{
    GLenum waitReturn = GL_UNSIGNALED;
    while (waitReturn != GL_ALREADY_SIGNALED && waitReturn != GL_CONDITION_SATISFIED)
    {
        waitReturn = glClientWaitSync(self->fences[self->writeIndex], GL_SYNC_FLUSH_COMMANDS_BIT, 1);
    }
}

void mouse_persistentMappedBuffer_incrementWriteIndex(mouse_persistentMappedBuffer* self)
{
    self->writeIndex = (self->writeIndex + 1) % self->bufferStrategy; // loop writeIndex
}