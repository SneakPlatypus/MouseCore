#include "MouseCore/Shader.h"
#include "MouseCore/Utility.h"
#include <string.h>

typedef enum mouse_shader_buildType_e
{
    MOUSE_SHADER_BUILD_COMPILE,
    MOUSE_SHADER_BUILD_LINK
} mouse_shader_buildType;

void mouse_shader_checkBuildErrors(GLuint shader, const char* vertex_path, const char* fragment_path, mouse_shader_buildType type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type == MOUSE_SHADER_BUILD_COMPILE)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("Error linking shader program, vertex path: %s, fragment path: %s\n", vertex_path, fragment_path);
            printf("Error info log: %s\n", infoLog);
        }
    }
    else if(type == MOUSE_SHADER_BUILD_LINK)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("Error compiling shader program, vertex path: %s, fragment path: %s\n", vertex_path, fragment_path);
            printf("Error info log: %s\n", infoLog);
        }
    }
}

GLuint mouse_shader_create(const char* vertex_path, const char* fragment_path)
{
    FILE* vertexFile = fopen(vertex_path, "r");
    FILE* fragmentFile = fopen(fragment_path, "r");
    
    size_t vertexLineCount = mouse_utility_getFileLineCount(vertexFile);
    char** vertexFileLines = mouse_utility_readFileLines(vertexFile, vertexLineCount);

    size_t fragmentLineCount = mouse_utility_getFileLineCount(fragmentFile);
    char** fragmentFileLines = mouse_utility_readFileLines(fragmentFile, fragmentLineCount);

    const char** const_v = (const char**)vertexFileLines;
    const char** const_f = (const char**)fragmentFileLines;
    
    //print_char_arrays(vertexFileLines, vertexLineCount);
    //print_char_arrays(fragmentFileLines, fragmentLineCount);

    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, vertexLineCount, const_v, NULL);
    glCompileShader(vertex_id);
    mouse_shader_checkBuildErrors(vertex_id, vertex_path, fragment_path, MOUSE_SHADER_BUILD_COMPILE);

    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, fragmentLineCount, const_f, NULL);
    glCompileShader(fragment_id);
    mouse_shader_checkBuildErrors(fragment_id, vertex_path, fragment_path, MOUSE_SHADER_BUILD_COMPILE);

    GLuint shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex_id);
    glAttachShader(shader_id, fragment_id);
    glLinkProgram(shader_id);
    mouse_shader_checkBuildErrors(shader_id, vertex_path, fragment_path, MOUSE_SHADER_BUILD_LINK);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    fclose(vertexFile);
    fclose(fragmentFile);

    mouse_utility_deleteFileLines(vertexFileLines, vertexLineCount);
    mouse_utility_deleteFileLines(fragmentFileLines, fragmentLineCount);
    
    return shader_id;
}

void mouse_shader_delete(GLuint shader_id)
{
    glDeleteProgram(shader_id);
}

void mouse_shader_setInt(int binding, int value)
{
    glUniform1i(binding, value);
}

void mouse_shader_setFloat(int binding, float value)
{
    glUniform1f(binding, value);
}

void mouse_shader_setVec2(int binding, vec2 value)
{
    glUniform2fv(binding, 1, value);
}

void mouse_shader_setVec2f(int binding, float x, float y) 
{
    glUniform2f(binding, x, y);
}

void mouse_shader_setVec3(int binding, vec3 value) 
{
    glUniform3fv(binding, 1, value);
}

void mouse_shader_setVec3f(int binding, float x, float y, float z)
{
    glUniform3f(binding, x, y, z);
}

void mouse_shader_setVec4(int binding, vec4 value)
{
    glUniform4fv(binding, 1, value);
}

void mouse_shader_setVec4f(int binding, float x, float y, float z, float w)
{
    glUniform4f(binding, x, y, z, w);
}

void mouse_shader_setMat2(int binding, mat2 value)
{
    glUniformMatrix2fv(binding, 1, GL_FALSE, value[0]);
}

void mouse_shader_setMat3(int binding, mat3 value)
{
    glUniformMatrix3fv(binding, 1, GL_FALSE, value[0]);
}

void mouse_shader_setMat4(int binding, mat4 value)
{
    glUniformMatrix4fv(binding, 1, GL_FALSE, value[0]);
}

// look up uniform location by name
void mouse_shader_setIntNamed(GLuint shader_id, const char*name, int value)
{
    glUniform1i(glGetUniformLocation(shader_id, name), value);
}

void mouse_shader_setFloatNamed(GLuint shader_id, const char*name, float value)
{
    glUniform1f(glGetUniformLocation(shader_id, name), value);
}

void mouse_shader_setVec2Named(GLuint shader_id, const char*name, vec2 value)
{
    glUniform2fv(glGetUniformLocation(shader_id, name), 1, value);
}

void mouse_shader_setVec2fNamed(GLuint shader_id, const char*name, float x, float y) 
{
    glUniform2f(glGetUniformLocation(shader_id, name), x, y);
}

void mouse_shader_setVec3Named(GLuint shader_id, const char*name, vec3 value) 
{
    glUniform3fv(glGetUniformLocation(shader_id, name), 1, value);
}

void mouse_shader_setVec3fNamed(GLuint shader_id, const char*name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(shader_id, name), x, y, z);
}

void mouse_shader_setVec4Named(GLuint shader_id, const char*name, vec4 value)
{
    glUniform4fv(glGetUniformLocation(shader_id, name), 1, value);
}

void mouse_shader_setVec4fNamed(GLuint shader_id, const char*name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(shader_id, name), x, y, z, w);
}

void mouse_shader_setMat2Named(GLuint shader_id, const char*name, mat2 value)
{
    glUniformMatrix2fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, value[0]);
}

void mouse_shader_setMat3Named(GLuint shader_id, const char*name, mat3 value)
{
    glUniformMatrix3fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, value[0]);
}

void mouse_shader_setMat4Named(GLuint shader_id, const char*name, mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, value[0]);
}