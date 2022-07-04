#ifndef CAMERA_H
#define CAMERA_H
#include <types.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <primatives.h>

typedef struct camera{
    vec3 pos;
    vec3 front;
    vec3 up;
    vec3 speed;
    mat4 projection;
}Camera;

void setupCamera(vec3 initPos, vec3 front, vec3 up, f32 speed, Camera * c, f32 screenWidth, f32 screenHeight);

#endif