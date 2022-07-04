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
#include <global.h>

void window_init(Global * global){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    global->renderer.window = glfwCreateWindow(global->renderer.width, global->renderer.height, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(global->renderer.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetInputMode(global->renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(global->renderer.window, mouse_callback);  
    glViewport(0, 0, global->renderer.width, global->renderer.height);
    setupCamera((vec3){0.0f, 0.0f,  3.0f}, (vec3){0.0f, 0.0f, -1.0f}, (vec3){0.0f, 1.0f,  0.0f}, 0.2, &global->camera, global->renderer.width, global->renderer.height, 0.1f);
    glEnable(GL_DEPTH_TEST);
    
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    f32 xpos = (f32)xposIn; f32 ypos = (f32)yposIn;
    moveCamera(xpos,ypos,&global.camera);
    /*
    float xoffset = xpos - global.camera.lastX;
    float yoffset = global.camera.lastY - ypos; // reversed since y-coordinates go from bottom to top
    global.camera.lastX = xpos;
    global.camera.lastY = ypos;

    xoffset *= global.camera.sensitivity;
    yoffset *= global.camera.sensitivity;

    global.camera.yaw += xoffset;
    global.camera.pitch += yoffset;

    if (global.camera.pitch > 89.0f){
        global.camera.pitch = 89.0f;
    }
    if (global.camera.pitch < -89.0f){
        global.camera.pitch = -89.0f;
    }

    vec3 front = GLM_VEC3_ONE_INIT;
    front[0] = cos(glm_rad(global.camera.yaw)) * cos(glm_rad(global.camera.pitch));
    front[1] = sin(glm_rad(global.camera.pitch));
    front[2] = sin(glm_rad(global.camera.yaw)) * cos(glm_rad(global.camera.pitch));
    glm_normalize(front);
    glm_vec3_copy(front, global.camera.front);
    */
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
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
    }
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); 
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