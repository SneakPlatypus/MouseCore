#pragma once

#include <GL/glew.h>
#include "MouseCore/Camera/Camera.h"

// global version of functions that save the index used and track the Uniform Buffer Object internally
void mouse_cameraBuffer_createGlobal(int index);
void mouse_cameraBuffer_deleteGlobal();

void mouse_cameraBuffer_linkShaderGlobal(GLuint shader);
void mouse_cameraBuffer_updateGlobal(mouse_camera* camera);

void mouse_cameraBuffer_linkShader(GLuint shader, GLuint bufferObject, int index);
void mouse_cameraBuffer_udpate(GLuint bufferObject, mouse_camera* camera);

// non-global version of functions that require the caller to save the Uniform Buffer Object and the index
GLuint mouse_cameraBuffer_create(int index);
void mouse_cameraBuffer_delete(GLuint bufferObject);

