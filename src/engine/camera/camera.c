#include <types.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <primatives.h>
#include <camera/camera.h>
#include <math.h>
#include <stdbool.h>
#include <primatives.h>
#include <block/entities.h>

void setupCamera(vec3 initPos, vec3 front, vec3 up, f32 speed, Camera * c, f32 screenWidth, f32 screenHeight, f32 sensitivity){
    glm_vec3_copy(initPos, c->pos);
    glm_vec3_copy(front, c->front);
    glm_vec3_copy(up, c->up);
    glm_vec3_copy((vec3){speed,speed,speed}, c->speed);
    glm_mat4_copy((mat4)GLM_MAT4_IDENTITY_INIT, c->projection);
    c->yaw = -90.0f; c->pitch = 0.0f; c->sensitivity = sensitivity;
    c->lastX = 800.0f / 2.0; c->lastY =  600.0 / 2.0; c->firstMouse=true;
    vec3 addvec;
    glm_vec3_add(c->pos, c->front, addvec);
    glm_lookat(c->pos, addvec, c->up, c->view);
    glm_perspective(glm_rad(45.0f), screenWidth / screenHeight, 0.1f, 100.0f, c->projection);
}

void setCameraView(Camera *c, f32 screenWidth, f32 screenHeight){
    vec3 addvec;
    glm_vec3_add(c->pos, c->front, addvec);
    glm_lookat(c->pos, addvec, c->up, c->view);
    glm_perspective(glm_rad(45.0f), screenWidth / screenHeight, 0.1f, 100.0f, c->projection);
}