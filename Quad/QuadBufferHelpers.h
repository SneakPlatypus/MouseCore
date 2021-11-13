#pragma once

#include <GL/glew.h>
#include <cglm/cglm.h>

#define MOUSE_QUAD_FLOAT_COUNT 32

// creates the right sized float array
float* mouse_quadBufferHelpers_createVertices();


/** Returns the provided pointer to enable the fill functions to be used for construction in the form **/
/** mouse_object_create( mouse_quadBufferHelpers_Fill( mouse_quadBufferHelpers_createVertices() )  ) **/
/** where mouse_object_create requires a float* for a quad **/

// origin x/y are each 0-1 percentage of where the origin lies
// aspect is width / height to set the model to a rectangle
// texture coordinates are set 0-1 
float* mouse_quadBufferHelpers_fillVertices(GLfloat originX, GLfloat originY, GLfloat aspect, vec4 colors[4], float* out);
float* mouse_quadBufferHelpers_fillVerticesColorless(GLfloat originX, GLfloat originY, GLfloat aspect, float* out);
// set the texture coordinates as well
float* mouse_quadBufferHelpers_fillVerticesUV(GLfloat originX, GLfloat originY, GLfloat aspect, vec2 uvs[4], vec4 colors[4], float* out);
float* mouse_quadBufferHelpers_fillVerticesUVColorless(GLfloat originX, GLfloat originY, GLfloat aspect, vec2 uvs[4], float* out);

// no aspect so square comes out
float* mouse_quadBufferHelpers_fillVerticesSquare(GLfloat originX, GLfloat originY, vec4 colors[4], float* out);
float* mouse_quadBufferHelpers_fillVerticesSquareColorless(GLfloat originX, GLfloat originY, float* out);
// square with settable uvs
float* mouse_quadBufferHelpers_fillVerticesSquareUV(GLfloat originX, GLfloat originY, vec2 uvs[4], vec4 colors[4], float* out);
float* mouse_quadBufferHelpers_fillVerticesSquareUVColorless(GLfloat originX, GLfloat originY, vec2 uvs[4], float* out);