#include "MouseCore/Transform.h"

mouse_transform* mouse_transform_createDefault()
{
    mouse_transform* transform = malloc(sizeof(mouse_transform));
    
    glm_vec3_zero(transform->position);
    glm_vec2_one(transform->scale);
    
    transform->rotation = 0.0f;
    
    return transform;
}

mouse_transform* mouse_transform_create(vec3 position, vec2 scale, float rotation)
{
    mouse_transform* transform = malloc(sizeof(mouse_transform));
    
    glm_vec3_copy(position, transform->position);
    glm_vec2_copy(scale, transform->scale);
    
    transform->rotation = rotation;
    
    return transform;
}

void mouse_transform_delete(mouse_transform* self)
{
    free(self);
}

void mouse_transform_getModel(mouse_transform* self, mat4 out)
{
    glm_mat4_identity(out);
    glm_translate(out, self->position);
    float radianRotation = glm_rad(self->rotation);
    glm_rotate(out, radianRotation, (vec3) { 0, 0, 1 });
    glm_scale(out, (vec3) { self->scale[0], self->scale[1], 1.0f });
}