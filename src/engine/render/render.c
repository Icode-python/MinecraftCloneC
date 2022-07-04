#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <global.h>
#include <io/array.h>
#include <math.h>
#include <render/shader.h>
#include <stb_image.h>
#include <stdbool.h>
#include <types.h>
#include <render/render.h>
#include <render/camera.h>

void window_init(Global * global){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    global->renderer.window = glfwCreateWindow(global->renderer.width, global->renderer.height, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(global->renderer.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, global->renderer.width, global->renderer.height);
    setupCamera((vec3){0.0f, 0.0f,  3.0f}, (vec3){0.0f, 0.0f, -1.0f}, (vec3){0.0f, 1.0f,  0.0f}, 0.2, &global->camera, global->renderer.width, global->renderer.height);
    glEnable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow *window, Camera *c){
    vec3 dest = GLM_VEC3_ONE_INIT;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glm_vec3_mul(c->front,c->speed,dest);
        glm_vec3_add(c->pos,dest,c->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        glm_vec3_mul(c->front,c->speed,dest);
        glm_vec3_sub(c->pos,dest,c->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        glm_cross(c->front,c->up,dest); glm_normalize(dest);
        glm_vec3_mul(dest,c->speed,dest); glm_vec3_sub(c->pos,dest,c->pos);
    }   
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        glm_cross(c->front,c->up,dest); glm_normalize(dest);
        glm_vec3_mul(dest,c->speed,dest); glm_vec3_add(c->pos,dest,c->pos);
    }
}