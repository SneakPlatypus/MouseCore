#include "MouseCore/Quad/QuadBuffers.h"
#include <stdlib.h>

struct mouse_quadBuffers_t_prv
{
    GLuint buffers[MOUSE_QUADBUFFERS_NAME_COUNT];
    float* vertices;
};

GLfloat bottomLeftVertices[32] = 
{
    //positions			 texture coords
    1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
};

GLfloat centeredVertices[32] =
{
    //positions			texture coords
     0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
};

GLushort indices[6] =
{
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

// allocates and returns a struct containing a VAO and 2 buffers (vertex/textureCoordinates, index) using DSA
mouse_quadBuffers* mouse_quadBuffers_create(float* quadVertices)
{
    mouse_quadBuffers* quadBuffers = malloc(sizeof(mouse_quadBuffers));
    quadBuffers->prv = malloc(sizeof(mouse_quadBuffers_prv));
    quadBuffers->prv->vertices = quadVertices;

    // create initialized buffers
    glCreateVertexArrays(1, &quadBuffers->VAO);
    glCreateBuffers(MOUSE_QUADBUFFERS_NAME_COUNT, quadBuffers->prv->buffers);
    
    // allocate storage for vertex and index buffers
    glNamedBufferStorage(quadBuffers->prv->buffers[MOUSE_QUADBUFFERS_NAME_VERTEX], sizeof(float) * MOUSE_QUAD_FLOAT_COUNT, quadVertices, GL_DYNAMIC_STORAGE_BIT);
    
    glNamedBufferStorage(quadBuffers->prv->buffers[MOUSE_QUADBUFFERS_NAME_INDEX], sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);
    
    // relate vertex buffer to an arbitrary index and associate element array buffer
    glVertexArrayVertexBuffer(quadBuffers->VAO, 0, quadBuffers->prv->buffers[MOUSE_QUADBUFFERS_NAME_VERTEX], 0, 8*sizeof(GLfloat));
    glVertexArrayElementBuffer(quadBuffers->VAO, quadBuffers->prv->buffers[MOUSE_QUADBUFFERS_NAME_INDEX]);

    // link the shader attribute indexes to the earlier arbitrary index
    glVertexArrayAttribBinding(quadBuffers->VAO, 0, 0);
    glVertexArrayAttribBinding(quadBuffers->VAO, 1, 0);
    glVertexArrayAttribBinding(quadBuffers->VAO, 2, 0);

    //specify the shader attribute index to format, number of items not byte size, float type, not normalized, offset to first element in bytes
    glVertexArrayAttribFormat(quadBuffers->VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(quadBuffers->VAO, 1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat));
    glVertexArrayAttribFormat(quadBuffers->VAO, 2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat));

    // enable the two shader attributes
    glEnableVertexArrayAttrib(quadBuffers->VAO, 0);
    glEnableVertexArrayAttrib(quadBuffers->VAO, 1);
    glEnableVertexArrayAttrib(quadBuffers->VAO, 2);

    return quadBuffers;
}

void mouse_quadBuffers_delete(mouse_quadBuffers* self)
{
    glDeleteVertexArrays(1, &self->VAO);
    glDeleteBuffers(MOUSE_QUADBUFFERS_NAME_COUNT, self->prv->buffers);
    free(self->prv->vertices);
    free(self->prv);
    free(self);
}