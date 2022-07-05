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
#include <primatives.h>
#include <block/entities.h>


void entity_init(Entity* obj, vec3 pos,u32 texture){
    obj->texture = texture;
    glm_vec3_copy(pos,obj->pos);
}
