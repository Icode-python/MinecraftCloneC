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
#include <camera/camera.h>


typedef struct render_internal{
    u32 VAO;
    u32 VBO;
    u32 EBO;
    Shader shader;
    u32 texture;
}Render_State_Internal;

typedef struct render {
    GLFWwindow * window;
    f32 width;
    f32 height;
} Render;

int RendererInitCube(Render_State_Internal *r);
void Translate(vec3 pos, u32 ID);
void render_begin(Camera * c);
void render_end();
#endif