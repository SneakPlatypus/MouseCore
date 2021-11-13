#pragma once

#include <cglm/cglm.h>

typedef struct mouse_transform_t
{
    vec3 position;
    vec2 scale;
    float rotation;
} mouse_transform;


mouse_transform* mouse_transform_createDefault();
mouse_transform* mouse_transform_create(vec3 position, vec2 scale, float rotation);
void mouse_transform_delete(mouse_transform* self);

void mouse_transform_getModel(mouse_transform* self, mat4 out);