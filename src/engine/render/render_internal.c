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

int renderInternalInit(Render_Internal * r, size_t size){
    initArray(&r->VAO,size);
    initArray(&r->VBO,size);
    initArray(&r->EBO,size);
}

int objectRendererInit(Object * obj, Render_Internal *r){
    u32 i;
    glGenVertexArrays(1, &i);
    insertArrayU32(&r->VAO,i);
    u32 arrPos = findElement(&r->VAO,i);
    obj->arrayBuffer = arrPos;
    
    glGenBuffers(1, &i);
    insertArrayU32(&r->EBO,i);
    glGenBuffers(1, &i);
    insertArrayU32(&r->VBO,i);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(r->VAO.iArray[arrPos]);

    glBindBuffer(GL_ARRAY_BUFFER, r->VBO.iArray[arrPos]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj->vertices), obj->vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO.iArray[arrPos]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj->indices), obj->indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int texInit(const char * path, u32 * texture, bool flip, bool has_rgba){
    stbi_set_flip_vertically_on_load(flip); 
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data){
        if(has_rgba){glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);}
        else{glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);}
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("failed to load texture");
    }
    stbi_image_free(data);
}

void render_begin();
void render_end();