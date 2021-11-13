#include "MouseCore/Quad/QuadBufferHelpers.h"
#include <math.h>

float* mouse_quadBufferHelpers_fillVertices(GLfloat originX, GLfloat originY, GLfloat aspect, vec4 colors[4], float* out)
{
    float width;
    float height;
    aspect = fabsf(aspect);
    if(aspect > 1.0f)
    {
        width = 1.0f;
        height = 1.0f / aspect;
    }
    else
    {
        width = aspect;
        height = 1.0f;
    }

    float originOffsetX = originX*width;
    float originOffsetY = originY*height;
    // first vertex
    // (x, y)
    out[0] = width - originOffsetX;
    out[1] = height - originOffsetY;
    // (u, v)
    out[2] = 1.0f;
    out[3] = 1.0f;
    // (r, g, b, a)
    out[4] = colors[0][0];
    out[5] = colors[0][1];
    out[6] = colors[0][2];
    out[7] = colors[0][3];

    // second vertex
    // (x, y)
    out[8] = width - originOffsetX;
    out[9] = -originOffsetY;
    // (u, v)
    out[10] = 1.0f;
    out[11] = 0.0f;
    // (r, g, b, a)
    out[12] = colors[1][0];
    out[13] = colors[1][1];
    out[14] = colors[1][2];
    out[15] = colors[1][3];

    // third vertex
    // (x, y)
    out[16] = -originOffsetX;
    out[17] = -originOffsetY;
    // (u, v)
    out[18] = 0.0f;
    out[19] = 0.0f;
    // (r, g, b, a)
    out[20] = colors[2][0];
    out[21] = colors[2][1];
    out[22] = colors[2][2];
    out[23] = colors[2][3];

    // fourth vertex
    // (x, y)
    out[24] = -originOffsetX;
    out[25] = height - originOffsetY;
    // (u, v)
    out[26] = 0.0f;
    out[27] = 1.0f;
    // (r, g, b, a)
    out[28] = colors[3][0];
    out[29] = colors[3][1];
    out[30] = colors[3][2];
    out[31] = colors[3][3];

    return out;
}

float* mouse_quadBufferHelpers_fillVerticesColorless(GLfloat originX, GLfloat originY, GLfloat aspect, float* out)
{   
    float width;
    float height;
    aspect = fabsf(aspect);
    if(aspect > 1.0f)
    {
        width = 1.0f;
        height = 1.0f / aspect;
    }
    else
    {
        width = aspect;
        height = 1.0f;
    }

    float originOffsetX = originX*width;
    float originOffsetY = originY*height;
    // first vertex
    // (x, y)
    out[0] = width - originOffsetX;
    out[1] = height - originOffsetY;
    // (u, v)
    out[2] = 1.0f;
    out[3] = 1.0f;
    // (r, g, b, a)
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[6] = 0.0f;
    out[7] = 1.0f;

    // second vertex
    // (x, y)
    out[8] = width - originOffsetX;
    out[9] = -originOffsetY;
    // (u, v)
    out[10] = 1.0f;
    out[11] = 0.0f;
    // (r, g, b, a)
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    // third vertex
    // (x, y)
    out[16] = -originOffsetX;
    out[17] = -originOffsetY;
    // (u, v)
    out[18] = 0.0f;
    out[19] = 0.0f;
    // (r, g, b, a)
    out[20] = 0.0f;
    out[21] = 0.0f;
    out[22] = 0.0f;
    out[23] = 1.0f;

    // fourth vertex
    // (x, y)
    out[24] = -originOffsetX;
    out[25] = height - originOffsetY;
    // (u, v)
    out[26] = 0.0f;
    out[27] = 1.0f;
    // (r, g, b, a)
    out[28] = 0.0f;
    out[29] = 0.0f;
    out[30] = 0.0f;
    out[31] = 1.0f;

    return out;
}

// set the texture coordinates as well
float* mouse_quadBufferHelpers_fillVerticesUV(GLfloat originX, GLfloat originY, GLfloat aspect, vec2 uvs[4], vec4 colors[4], float* out)
{   
    float width;
    float height;
    aspect = fabsf(aspect);
    if(aspect > 1.0f)
    {
        width = 1.0f;
        height = 1.0f / aspect;
    }
    else
    {
        width = aspect;
        height = 1.0f;
    }

    float originOffsetX = originX*width;
    float originOffsetY = originY*height;
    // first vertex
    // (x, y)
    out[0] = width - originOffsetX;
    out[1] = height - originOffsetY;
    // (u, v)
    out[2] = uvs[0][0];
    out[3] = uvs[0][1];
    // (r, g, b, a)
    out[4] = colors[0][0];
    out[5] = colors[0][1];
    out[6] = colors[0][2];
    out[7] = colors[0][3];

    // second vertex
    // (x, y)
    out[8] = width - originOffsetX;
    out[9] = -originOffsetY;
    // (u, v)
    out[10] = uvs[1][0];
    out[11] = uvs[1][1];
    // (r, g, b, a)
    out[12] = colors[1][0];
    out[13] = colors[1][1];
    out[14] = colors[1][2];
    out[15] = colors[1][3];

    // third vertex
    // (x, y)
    out[16] = -originOffsetX;
    out[17] = -originOffsetY;
    // (u, v)
    out[18] = uvs[2][0];
    out[19] = uvs[2][1];
    // (r, g, b, a)
    out[20] = colors[2][0];
    out[21] = colors[2][1];
    out[22] = colors[2][2];
    out[23] = colors[2][3];

    // fourth vertex
    // (x, y)
    out[24] = -originOffsetX;
    out[25] = height - originOffsetY;
    // (u, v)
    out[26] = uvs[3][0];
    out[27] = uvs[3][1];
    // (r, g, b, a)
    out[28] = colors[3][0];
    out[29] = colors[3][1];
    out[30] = colors[3][2];
    out[31] = colors[3][3];

    return out;
}

float* mouse_quadBufferHelpers_fillVerticesUVColorless(GLfloat originX, GLfloat originY, GLfloat aspect, vec2 uvs[4], float* out)
{    
    float width;
    float height;
    aspect = fabsf(aspect);
    if(aspect > 1.0f)
    {
        width = 1.0f;
        height = 1.0f / aspect;
    }
    else
    {
        width = aspect;
        height = 1.0f;
    }

    float originOffsetX = originX*width;
    float originOffsetY = originY*height;
    // first vertex
    // (x, y)
    out[0] = width - originOffsetX;
    out[1] = height - originOffsetY;
    // (u, v)
    out[2] = uvs[0][0];
    out[3] = uvs[0][1];
    // (r, g, b, a)
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[6] = 0.0f;
    out[7] = 1.0f;

    // second vertex
    // (x, y)
    out[8] = width - originOffsetX;
    out[9] = -originOffsetY;
    // (u, v)
    out[10] = uvs[1][0];
    out[11] = uvs[1][1];
    // (r, g, b, a)
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    // third vertex
    // (x, y)
    out[16] = -originOffsetX;
    out[17] = -originOffsetY;
    // (u, v)
    out[18] = uvs[2][0];
    out[19] = uvs[2][1];
    // (r, g, b, a)
    out[20] = 0.0f;
    out[21] = 0.0f;
    out[22] = 0.0f;
    out[23] = 1.0f;

    // fourth vertex
    // (x, y)
    out[24] = -originOffsetX;
    out[25] = height - originOffsetY;
    // (u, v)
    out[26] = uvs[3][0];
    out[27] = uvs[3][1];
    // (r, g, b, a)
    out[28] = 0.0f;
    out[29] = 0.0f;
    out[30] = 0.0f;
    out[31] = 1.0f;

    return out;
}

// no aspect so square comes out
float* mouse_quadBufferHelpers_fillVerticesSquare(GLfloat originX, GLfloat originY, vec4 colors[4], float* out)
{
    // first vertex
    // (x, y)
    out[0] = 1.0f - originX;
    out[1] = 1.0f - originY;
    // (u, v)
    out[2] = 1.0f;
    out[3] = 1.0f;
    // (r, g, b, a)
    out[4] = colors[0][0];
    out[5] = colors[0][1];
    out[6] = colors[0][2];
    out[7] = colors[0][3];

    // second vertex
    // (x, y)
    out[8] = 1.0f - originX;
    out[9] = 0.0f - originY;
    // (u, v)
    out[10] = 1.0f;
    out[11] = 0.0f;
    // (r, g, b, a)
    out[12] = colors[1][0];
    out[13] = colors[1][1];
    out[14] = colors[1][2];
    out[15] = colors[1][3];

    // third vertex
    // (x, y)
    out[16] = 0.0f - originX;
    out[17] = 0.0f - originY;
    // (u, v)
    out[18] = 0.0f;
    out[19] = 0.0f;
    // (r, g, b, a)
    out[20] = colors[2][0];
    out[21] = colors[2][1];
    out[22] = colors[2][2];
    out[23] = colors[2][3];

    // fourth vertex
    // (x, y)
    out[24] = 0.0f - originX;
    out[25] = 1.0f - originY;
    // (u, v)
    out[26] = 0.0f;
    out[27] = 1.0f;
    // (r, g, b, a)
    out[28] = colors[3][0];
    out[29] = colors[3][1];
    out[30] = colors[3][2];
    out[31] = colors[3][3];

    return out;
}

float* mouse_quadBufferHelpers_fillVerticesSquareColorless(GLfloat originX, GLfloat originY, float* out)
{
    // first vertex
    // (x, y)
    out[0] = 1.0f - originX;
    out[1] = 1.0f - originY;
    // (u, v)
    out[2] = 1.0f;
    out[3] = 1.0f;
    // (r, g, b, a)
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[6] = 0.0f;
    out[7] = 1.0f;

    // second vertex
    // (x, y)
    out[8] = 1.0f - originX;
    out[9] = 0.0f - originY;
    // (u, v)
    out[10] = 1.0f;
    out[11] = 0.0f;
    // (r, g, b, a)
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    // third vertex
    // (x, y)
    out[16] = 0.0f - originX;
    out[17] = 0.0f - originY;
    // (u, v)
    out[18] = 0.0f;
    out[19] = 0.0f;
    // (r, g, b, a)
    out[20] = 0.0f;
    out[21] = 0.0f;
    out[22] = 0.0f;
    out[23] = 1.0f;

    // fourth vertex
    // (x, y)
    out[24] = 0.0f - originX;
    out[25] = 1.0f - originY;
    // (u, v)
    out[26] = 0.0f;
    out[27] = 1.0f;
    // (r, g, b, a)
    out[28] = 0.0f;
    out[29] = 0.0f;
    out[30] = 0.0f;
    out[31] = 1.0f;
    
    return out;
}

// square with settable uvs
float* mouse_quadBufferHelpers_fillVerticesSquareUV(GLfloat originX, GLfloat originY, vec2 uvs[4], vec4 colors[4], float* out)
{
    // first vertex
    // (x, y)
    out[0] = 1.0f - originX;
    out[1] = 1.0f - originY;
    // (u, v)
    out[2] = uvs[0][0];
    out[3] = uvs[0][1];
    // (r, g, b, a)
    out[4] = colors[0][0];
    out[5] = colors[0][1];
    out[6] = colors[0][2];
    out[7] = colors[0][3];

    // second vertex
    // (x, y)
    out[8] = 1.0f - originX;
    out[9] = 0.0f - originY;
    // (u, v)
    out[10] = uvs[1][0];
    out[11] = uvs[1][1];
    // (r, g, b, a)
    out[12] = colors[1][0];
    out[13] = colors[1][1];
    out[14] = colors[1][2];
    out[15] = colors[1][3];

    // third vertex
    // (x, y)
    out[16] = 0.0f - originX;
    out[17] = 0.0f - originY;
    // (u, v)
    out[18] = uvs[2][0];
    out[19] = uvs[2][1];
    // (r, g, b, a)
    out[20] = colors[2][0];
    out[21] = colors[2][1];
    out[22] = colors[2][2];
    out[23] = colors[2][3];

    // fourth vertex
    // (x, y)
    out[24] = 0.0f - originX;
    out[25] = 1.0f - originY;
    // (u, v)
    out[26] = uvs[3][0];;
    out[27] = uvs[3][1];
    // (r, g, b, a)
    out[28] = colors[3][0];
    out[29] = colors[3][1];
    out[30] = colors[3][2];
    out[31] = colors[3][3];

    return out;
}

float* mouse_quadBufferHelpers_fillVerticesSquareUVColorless(GLfloat originX, GLfloat originY, vec2 uvs[4], float* out)
{
    // first vertex
    // (x, y)
    out[0] = 1.0f - originX;
    out[1] = 1.0f - originY;
    // (u, v)
    out[2] = uvs[0][0];
    out[3] = uvs[0][1];
    // (r, g, b, a)
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[6] = 0.0f;
    out[7] = 1.0f;

    // second vertex
    // (x, y)
    out[8] = 1.0f - originX;
    out[9] = 0.0f - originY;
    // (u, v)
    out[10] = uvs[1][0];
    out[11] = uvs[1][1];
    // (r, g, b, a)
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;

    // third vertex
    // (x, y)
    out[16] = 0.0f - originX;
    out[17] = 0.0f - originY;
    // (u, v)
    out[18] = uvs[2][0];
    out[19] = uvs[2][1];
    // (r, g, b, a)
    out[20] = 0.0f;
    out[21] = 0.0f;
    out[22] = 0.0f;
    out[23] = 1.0f;

    // fourth vertex
    // (x, y)
    out[24] = 0.0f - originX;
    out[25] = 1.0f - originY;
    // (u, v)
    out[26] = uvs[3][0];;
    out[27] = uvs[3][1];
    // (r, g, b, a)
    out[28] = 0.0f;
    out[29] = 0.0f;
    out[30] = 0.0f;
    out[31] = 1.0f;

    return out;
}