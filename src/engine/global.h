#ifndef GLOBAL_H
#define GLOBAL_H
#include <types.h>
#include <render/render.h>

typedef struct global {
    Render renderer;
    Render_Internal renderInternal;
} Global;

extern Global global;

void window_init(Global * global);
void processInput(GLFWwindow *window);

#endif