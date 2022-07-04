#include <types.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <primatives.h>
#include <render/camera.h>

void setupCamera(vec3 initPos, vec3 front, vec3 up, f32 speed, Camera * c, f32 screenWidth, f32 screenHeight){
    glm_vec3_copy(initPos, c->pos);
    glm_vec3_copy(front, c->front);
    glm_vec3_copy(up, c->up);
    glm_vec3_copy((vec3){speed,speed,speed}, c->speed);
    glm_mat4_copy((mat4)GLM_MAT4_IDENTITY_INIT, c->projection);
    glm_perspective(glm_rad(45.0f), screenWidth / screenHeight, 0.1f, 100.0f, c->projection);
}