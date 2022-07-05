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
#include <render/camera.h>
#include <render/entities.h>
Global global = {0};

int main(int argc, char * argv[]){
    //Global global = {0};
    global.renderer.width = 940;
    global.renderer.height = 620;

    window_init(&global);
    RendererInitCube(&global.renderInternal);
    
    Object obj[2][10][10];
    vec3 cubePositions[2][10][10];
    texInit((const char *)"shaders/grass.jpg", &global.renderInternal.texture, false, false);
    setUpShaders((const char *)"shaders/triangleShader.vert", (const char *)"shaders/triangleShader.frag", &global.renderInternal.shader);
    for(int y=0; y<2; y++){
        for(int x=0; x<10; x++){
            for(int z=0; z<10; z++){
                glm_vec3_copy((vec3){(f32)x, (f32)y, (f32)z},cubePositions[y][x][z]); 
                setupObject(&obj[y][x][z], cubePositions[y][x][z], global.renderInternal.texture);
            }
        }
    }
    //memcpy(obj.indices, indices, sizeof(obj.indices));

    while(!glfwWindowShouldClose(global.renderer.window)){
        processInput(global.renderer.window,&global.camera);
        setCameraView(&global.camera,global.renderer.width,global.renderer.height);

        render_begin(&global.camera);
        for(int y=0; y<2; y++){
            for(int x=0; x<10; x++){
                for(int z=0; z<10; z++){
                    use(global.renderInternal.shader.ID);

                    mat4 model = GLM_MAT4_IDENTITY_INIT;
                    glm_translate(model, cubePositions[y][x][z]);
                    setMat4("model", model,global.renderInternal.shader.ID);

                    glBindVertexArray(global.renderInternal.VAO);
                    glDrawArrays(GL_TRIANGLES, 0, allFaces);

                    //printf("x: %f,y: %f,z: %f,#x %d,#y %d\n", obj[x][y].pos[0],obj[x][y].pos[1],obj[x][y].pos[2],x,y);
                }
            }
        }

        render_end();  
    }

    glfwTerminate();
    return 0;
}
