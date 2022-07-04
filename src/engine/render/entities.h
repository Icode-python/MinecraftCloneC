#ifndef ENTITIES_H
#define ENTITIES_H
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <io/array.h>
#include <render/shader.h>
#include <stdbool.h>
#include <types.h>
#include <render/render.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <render/camera.h>
#include <render/render.h>

typedef struct object {
    u32 texture;
    vec3 pos;
} Object;

void setupObject(Object * obj, vec3 pos,u32 texture);

#endif