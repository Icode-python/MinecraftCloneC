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
Global global = {0};

int main(int argc, char * argv[]){
    //Global global = {0};
    global.renderer.width = 800;
    global.renderer.height = 600;

    window_init(&global);
    renderInternalInit(&global.renderInternal,1);
    
    Object obj; u32 texture1, texture2;

    const char * fragfile = "shaders/triangleShader.frag"; const char * vertfile = "shaders/triangleShader.vert";
    setUpShaders(vertfile, fragfile, &obj.shader);
    f32 vertices[180] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };
    memcpy(obj.vertices, vertices, sizeof(obj.vertices));
    //memcpy(obj.indices, indices, sizeof(obj.indices));

    objectRendererInit(&obj,&global.renderInternal);
    texInit((const char *)"shaders/container.jpg", &obj.texture, false, false);
    texInit((const char *)"shaders/awesomeface.png", &texture2, true, true);
    texture1 = obj.texture;

    use(obj.shader.ID); 
    setInt("texture1", 0, obj.shader.ID);
    setInt("texture2", 1, obj.shader.ID);
    setMat4("projection", global.camera.projection, obj.shader.ID);

    while(!glfwWindowShouldClose(global.renderer.window)){
        processInput(global.renderer.window,&global.camera);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, obj.texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        use(obj.shader.ID);
        mat4 view;
        vec3 addvec;
        glm_vec3_add(global.camera.pos, global.camera.front, addvec);
        glm_lookat(global.camera.pos, addvec, global.camera.up, view);
        setMat4("view", view, obj.shader.ID);
        glm_perspective(glm_rad(45.0f), global.renderer.width / global.renderer.height, 0.1f, 100.0f, global.camera.projection);        

        //mat4 view  = GLM_MAT4_IDENTITY_INIT;
        //glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
        //u32 viewLoc  = glGetUniformLocation(obj.shader.ID, "view");
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        for (u32 i = 0; i < 10; i++){
            mat4 model = GLM_MAT4_IDENTITY_INIT; f32 angle;
            glm_translate(model, cubePositions[i]);
            if(i % 3==0){angle = 20.0f * (i+1);}
            else{angle=0.0f;}
            glm_rotate(model, (f32)glfwGetTime() * glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});  
            setMat4("model", model,obj.shader.ID);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glBindVertexArray(global.renderInternal.VAO.iArray[obj.arrayBuffer]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(global.renderer.window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
