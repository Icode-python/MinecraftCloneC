#define STB_IMAGE_IMPLEMENTATION
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
#include <render/texture.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <primatives.h>
#include <camera/camera.h>
#include <block/entities.h>
#include <block/chunk.h>

int main(int argc, char * argv[]){
    //Global global = {0};
    global.renderer.width = 856;
    global.renderer.height = 482;

    window_init(&global);
    RendererInitCube(&global.state);
    texInit((const char *)"shaders/grass.jpg", &global.state.texture, false, false);
    shader_create((const char *)"shaders/triangleShader.vert", (const char *)"shaders/triangleShader.frag", &global.state.shader);
    Chunk chunk;
    chunk_init(&chunk);
    
    while(!glfwWindowShouldClose(global.renderer.window)){
        processInput(global.renderer.window,&global.camera);
        setCameraView(&global.camera,global.renderer.width,global.renderer.height);  
        render_chunk(&chunk);
    }

    glfwTerminate();
    return 0;
}
