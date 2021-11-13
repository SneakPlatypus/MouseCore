#pragma once

#include <GL/glew.h>

typedef struct mouse_persistentMappedBuffer_t
{
    GLuint buffer;
    int dataSize;
    int writeIndex;
    int bufferStrategy;
    void* gpuMemory;
    GLsync* fences;
} mouse_persistentMappedBuffer;

mouse_persistentMappedBuffer* mouse_persistentMappedBuffer_create(size_t dataSize, int bufferStrategy);
void mouse_persistentMappedBuffer_delete(mouse_persistentMappedBuffer* self);

void mouse_persistentMappedBuffer_lockWriteBuffer(mouse_persistentMappedBuffer* self);
void mouse_persistentMappedBuffer_waitForLockedBuffer(mouse_persistentMappedBuffer* self);
void mouse_persistentMappedBuffer_incrementWriteIndex(mouse_persistentMappedBuffer* self);