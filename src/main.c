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

int main(int argc, char * argv[]){
    Global global = {0};
    global.renderer.width = 800;
    global.renderer.height = 600;

    window_init(&global);
    renderInternalInit(&global.renderInternal,1);
    
    Object obj; u32 texture1, texture2;

    const char * fragfile = "shaders/triangleShader.frag"; const char * vertfile = "shaders/triangleShader.vert";
    setUpShaders(vertfile, fragfile, &obj.shader);

    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    memcpy(obj.vertices, vertices, sizeof(obj.vertices));
    memcpy(obj.indices, indices, sizeof(obj.indices));

    objectRendererInit(&obj,&global.renderInternal);
    texInit((const char *)"shaders/container.jpg", &obj.texture, false, false);
    texInit((const char *)"shaders/awesomeface.png", &texture2, true, true);
    texture1 = obj.texture;

    use(obj.shader.ID); 
    setInt("texture1", 0, obj.shader.ID);
    setInt("texture2", 1, obj.shader.ID);

    while(!glfwWindowShouldClose(global.renderer.window)){
        processInput(global.renderer.window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, obj.texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        mat4 transform; // make sure to initialize matrix to identity matrix first
        glm_translate_make(transform, (vec3){0.5f, -0.5f, 0.0f});
        glm_rotate_make(transform, (f32)glfwGetTime(), GLM_ZUP);

        // get matrix's uniform location and set matrix
        use(obj.shader.ID);
        u32 transformLoc = glGetUniformLocation(obj.shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,(const f32 *)transform[0]);
        
        glBindVertexArray(global.renderInternal.VAO.iArray[obj.arrayBuffer]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(global.renderer.window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
