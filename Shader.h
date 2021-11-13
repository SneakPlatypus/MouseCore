#pragma once

#include <stdbool.h>
#include <GL/glew.h>
#include <cglm/cglm.h>

// remove uniform location querying eventually

GLuint mouse_shader_create(const char* vertex_path, const char* fragment_path);
void mouse_shader_delete(GLuint shader);

void mouse_shader_setInt(int binding, int value);
void mouse_shader_setFloat(int binding, float value);
void mouse_shader_setVec2(int binding, vec2 value);
void mouse_shader_setVec2f(int binding, float x, float y);
void mouse_shader_setVec3(int binding, vec3 value);
void mouse_shader_setVec3f(int binding, float x, float y, float z);
void mouse_shader_setVec4(int binding, vec4 value);
void mouse_shader_setVec4f(int binding, float x, float y, float z, float w);
void mouse_shader_setMat2(int binding, mat2 value);
void mouse_shader_setMat3(int binding, mat3 value);
void mouse_shader_setMat4(int binding, mat4 value);

void mouse_shader_setIntNamed(GLuint shader, const char*name, int value);
void mouse_shader_setFloatNamed(GLuint shader, const char*name, float value);
void mouse_shader_setVec2Named(GLuint shader, const char*name, vec2 value);
void mouse_shader_setVec2fNamed(GLuint shader, const char*name, float x, float y);
void mouse_shader_setVec3Named(GLuint shader, const char*name, vec3 value);
void mouse_shader_setVec3fNamed(GLuint shader, const char*name, float x, float y, float z);
void mouse_shader_setVec4Named(GLuint shader, const char*name, vec4 value);
void mouse_shader_setVec4fNamed(GLuint shader, const char*name, float x, float y, float z, float w);
void mouse_shader_setMat2Named(GLuint shader, const char*name, mat2 value);
void mouse_shader_setMat3Named(GLuint shader, const char*name, mat3 value);
void mouse_shader_setMat4Named(GLuint shader, const char*name, mat4 value);