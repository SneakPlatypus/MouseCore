#include "MouseCore/Camera/CameraBuffer.h"

static GLuint mouse_cameraBuffer_UBO = 0;
static int mouse_cameraBuffer_index = 0;

void mouse_cameraBuffer_createGlobal(int index)
{
    glGenBuffers(1, &mouse_cameraBuffer_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, mouse_cameraBuffer_UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, mouse_cameraBuffer_UBO);
    mouse_cameraBuffer_index = index;
}

void mouse_cameraBuffer_deleteGlobal()
{
    glDeleteBuffers(1, &mouse_cameraBuffer_UBO);
}

void mouse_cameraBuffer_linkShaderGlobal(GLuint shader)
{
    glUniformBlockBinding(shader, mouse_cameraBuffer_index, mouse_cameraBuffer_UBO);
}

void mouse_cameraBuffer_updateGlobal(mouse_camera* camera)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mouse_cameraBuffer_UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), &(camera->projection[0][0]));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), &(camera->view[0][0]));
}

void mouse_cameraBuffer_linkShader(GLuint shader, GLuint bufferObject, int index)
{
    glUniformBlockBinding(shader, index, bufferObject);
}

void mouse_cameraBuffer_udpate(GLuint bufferObject, mouse_camera* camera)
{
    glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), &(camera->projection[0][0]));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), &(camera->view[0][0]));
}

GLuint mouse_cameraBuffer_create(int index)
{
    GLuint UBO;
    
    glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, UBO);

    return UBO;
}

void mouse_cameraBuffer_delete(GLuint bufferObject)
{
    glDeleteBuffers(1, &bufferObject);
}