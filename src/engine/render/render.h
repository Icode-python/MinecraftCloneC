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

typedef struct object {
    Shader shader;
    u32 texture;
    float vertices[1000];
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

int objectRendererInit(Object * obj, Render_Internal * r);
int renderInternalInit(Render_Internal * r, size_t size);
void render_begin();
void render_end();

#endif