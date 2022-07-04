#ifndef GLOBAL_H
#define GLOBAL_H
#include <types.h>
#include <render/render.h>
#include <render/camera.h>

typedef struct global {
    Render renderer;
    Render_Internal renderInternal;
    Camera camera;
} Global;

extern Global global;
extern f32 mousePosX, mousePosY;

void window_init(Global * global);
void processInput(GLFWwindow *window, Camera *c);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

#endif