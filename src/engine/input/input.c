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
#include <camera/camera.h>
#include <global.h>
#include <primatives.h>
#include <block/entities.h>

void processInput(GLFWwindow *window, Camera *c){
    vec3 dest = GLM_VEC3_ONE_INIT;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
    
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        glm_vec3_copy((vec3){0.0,0.0,4.0},c->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glm_vec3_mul(c->front,(vec3){c->speed[0],0.0,c->speed[2]},dest);
        glm_vec3_normalize(dest);
        glm_vec3_mul(dest,(vec3){c->speed[0],0.0,c->speed[2]},dest);
        glm_vec3_add(c->pos,dest,c->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        glm_vec3_mul(c->front,(vec3){c->speed[0],0.0,c->speed[2]},dest);
        glm_vec3_normalize(dest);
        glm_vec3_mul(dest,(vec3){c->speed[0],0.0,c->speed[2]},dest);
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        glm_vec3_add(c->up, (vec3){0.0f,0.1f,0.0f}, dest);
        glm_normalize(dest); glm_vec3_mul(dest,c->speed,dest); glm_vec3_add(c->pos,dest,c->pos);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        glm_vec3_add(c->up, (vec3){0.0f,0.1f,0.0f}, dest);
        glm_normalize(dest); glm_vec3_mul(dest,c->speed,dest); glm_vec3_sub(c->pos,dest,c->pos);
    }
}

void moveCamera(f32 xpos, f32 ypos, Camera * c){
    f32 xoffset = xpos - c->lastX;
    f32 yoffset = c->lastY - ypos; // reversed since y-coordinates go from bottom to top
    c->lastX = xpos;
    c->lastY = ypos;

    if (c->firstMouse){
        c->lastX = xpos;
        c->lastY = ypos;
        c->firstMouse = false;
    }

    xoffset *= c->sensitivity;
    yoffset *= c->sensitivity;

    c->yaw += xoffset;
    c->pitch += yoffset;

    if (c->pitch > 89.0f){
        c->pitch = 89.0f;
    }
    if (c->pitch < -89.0f){
        c->pitch = -89.0f;
    }

    vec3 front;
    front[0] = cos(glm_rad(c->yaw)) * cos(glm_rad(c->pitch));
    front[1] = sin(glm_rad(c->pitch));
    front[2] = sin(glm_rad(c->yaw)) * cos(glm_rad(c->pitch));
    glm_normalize(front);
    glm_vec3_copy(front, c->front);
}
