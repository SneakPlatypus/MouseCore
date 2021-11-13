#pragma once

#include <GL/glew.h>

typedef struct DrawElementsIndirectCmd_t
{
    GLuint vertexCount;
    GLuint instanceCount;
    GLuint firstIndex;
    GLuint baseVertex;
    GLuint baseInstance;
} DrawElementsIndirectCmd;