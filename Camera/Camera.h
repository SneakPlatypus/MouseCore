#pragma once

#include "MouseCore/Utility.h"
#include <cglm/cglm.h>

typedef struct mouse_camera_t
{
    vec3 pos;
    float rotation;
    float orthoZoomFactor;
    vec3 front;
    vec3 up;
    float viewHeight;
    float aspect;
    float nearPlane;
    float farPlane;
    mat4 projection;
    mat4 view;
    mat4 projectionView;
} mouse_camera;

mouse_camera* mouse_camera_create(vec3 pos, float rotation, float ortho_zoom_factor, 
    vec3 front, vec3 up, 
    float viewHeight, float aspect,
    float near_plane, float far_plane);
void mouse_camera_delete(mouse_camera* self);
void mouse_camera_updateProjectionView(mouse_camera* self);

void mouse_camera_setAspect(mouse_camera* self, float width, float height);

void mouse_camera_screenToWorld(int screenX, int screenY, int windowWidth, int windowHeight, mouse_camera* camera, vec2 out);