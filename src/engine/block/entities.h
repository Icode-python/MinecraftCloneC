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
#include <camera/camera.h>
#include <render/render.h>

typedef enum{
    AIR = 0,
    GRASS = 1
} BLOCK_TYPE;

typedef struct entity {
    u32 texture;
    vec3 pos;
    BLOCK_TYPE ID;
} Entity ;

void entity_init(Entity * obj, vec3 pos,u32 texture);

#endif