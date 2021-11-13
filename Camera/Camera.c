#include "MouseCore/Camera/Camera.h"
#include "MouseCore/Utility.h"
#include <math.h>
#include <stdlib.h>
#include <math.h>

mouse_camera* mouse_camera_create(
    vec3 pos, float rotation, float orthoZoomFactor, 
    vec3 front, vec3 up, 
    float viewHeight, float aspect, 
    float nearPlane, float farPlane)
{
    mouse_camera* camera = malloc(sizeof(mouse_camera));

    glm_mat4_identity(camera->projection);
    glm_mat4_identity(camera->view);

    glm_vec3_copy(pos, camera->pos);
    camera->rotation = rotation;
    camera->orthoZoomFactor = orthoZoomFactor;
    glm_vec3_copy(front, camera->front);
    glm_vec3_copy(up, camera->up);
    
    camera->viewHeight = viewHeight;
    camera->aspect = aspect;

    camera->nearPlane = nearPlane;
    camera->farPlane = farPlane;

    mouse_camera_updateProjectionView(camera);
    return camera;
}

void mouse_camera_delete(mouse_camera* self)
{
    free(self);
}

void mouse_camera_updateProjectionView(mouse_camera* self)
{
    float zoom_factor = powf(self->orthoZoomFactor, 2.0f);
	glm_ortho(
            0, self->viewHeight * self->aspect,
            0, self->viewHeight,
            self->nearPlane, self->farPlane, 
            self->projection);

    vec3 center;
    glm_vec3_add(self->pos, self->front, center);
    glm_lookat(self->pos, center, self->up, self->view);

    glm_mat4_mul(self->projection, self->view, self->projectionView);
}

void mouse_camera_setAspect(mouse_camera* self, float width, float height)
{
    self->aspect = width / height;
}

void mouse_camera_screenToWorld(int screenX, int screenY, int windowWidth, int windowHeight, mouse_camera* camera, vec2 out)
{
    float width = camera->viewHeight * camera->aspect;
    float height = camera->viewHeight;
    vec4 viewport = { 0, 0, windowWidth, windowHeight };

    vec3 position = { screenX, windowHeight - screenY, 0.0f };
    vec3 unprojected;


    glm_unproject(position, camera->projectionView, viewport, unprojected);
    out[0] = unprojected[0];
    out[1] = unprojected[1];
}