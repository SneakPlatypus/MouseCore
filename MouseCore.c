#include "MouseCore/MouseCore.h"
#include <stdio.h>

GLenum mouse_coreGL_load()
{
    glewExperimental = GL_TRUE;
    return glewInit();
}

static void mouse_defaultDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf("GL message: %s severity: %d\n", message, severity);
}

void mouse_coreGL_setDefaultState(GLDEBUGPROC debugCallback)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    
    glEnable(GL_DEBUG_OUTPUT);
    if (debugCallback == NULL)
    {
        glDebugMessageCallback(&mouse_defaultDebugCallback, NULL);
    }
    else
    {
        glDebugMessageCallback(debugCallback, NULL);
    }
}