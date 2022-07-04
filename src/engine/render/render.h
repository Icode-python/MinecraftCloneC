#ifndef RENDER_H
#define RENDER_H
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

typedef struct object {
    Shader shader;
    u32 texture;
    vec3 pos;
    f32 vertices[1000];
    u32 indices[12];
    u32 arrayBuffer;
} Object;

typedef struct render_internal{
    Array VAO;
    Array VBO;
    Array EBO;
}Render_Internal;

typedef struct render {
    GLFWwindow * window;
    f32 width;
    f32 height;
} Render;

void setupObject(Object * obj, vec3 pos, Shader *shader, u32 texture, f32 vertices[200], Render_Internal * r);
int objectRendererInit(Object * obj, Render_Internal * r);
int renderInternalInit(Render_Internal * r, size_t size);
void set_render(Object * obj, Camera * c);
void render(Object * obj, Render_Internal * r);

#endif