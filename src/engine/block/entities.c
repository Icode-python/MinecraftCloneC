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
#include <block/chunk.h>


void entity_init(Entity* self, vec3 pos,u32 texture, u32 BlockID){
    self->texture = texture;
    glm_vec3_copy(pos,self->pos);
    self->ID = BlockID;
}

void drawSelectedFace(u32 start, u32 count){
    glBindVertexArray(global.state.VAO);
    glDrawArrays(GL_TRIANGLES, start, count);
}
/*
void check_entity_face(Chunk * chunk, Entity * self, vec3 index_add, u32 index, bool oper, u32 compare_num, u32 face){
    if(oper){
        if(self->pos[index]>compare_num){
            if(chunk->blocks[(const int)self->pos[1]+(const int)index_add[0]][(const int)self->pos[0]+(const int)index_add[1]][(const int)self->pos[2]+(const int)index_add[2]].ID != GRASS){
                drawSelectedFace(face,numVertsFace);
            }
        }
        else if(self->pos[index]==compare_num){
            drawSelectedFace(face,numVertsFace);
        }
    }
    else{
       if(self->pos[index]<compare_num){
            if(chunk->blocks[(const int)self->pos[1]+(const int)index_add[0]][(const int)self->pos[0]+(const int)index_add[1]][(const int)self->pos[2]+(const int)index_add[2]].ID != GRASS){
                drawSelectedFace(face,numVertsFace);
            }
        }
        else if(self->pos[index]==compare_num){
            drawSelectedFace(face,numVertsFace);
        } 
    }
}
*/
void render_shown(Chunk * chunk, Entity * self){
    //printf("%f\n", self->pos[1]);
    //check_entity_face(chunk, self, (vec3){1,-1,0},0,true,0,negXFace);
    if(self->pos[0]>0){
        if(chunk->blocks[(const int)self->pos[1]][(const int)self->pos[0]-1][(const int)self->pos[2]].ID != GRASS){
            drawSelectedFace(negXFace,numVertsFace);
        }
    }
    else if(self->pos[0]==0){
        drawSelectedFace(negXFace,numVertsFace);
    }
    if(self->pos[1]>0){
        if(chunk->blocks[(const int)self->pos[1]-1][(const int)self->pos[0]][(const int)self->pos[2]].ID != GRASS){
            drawSelectedFace(negYFace,numVertsFace);
        }
    }
    else if(self->pos[1]==0){
        drawSelectedFace(negYFace,numVertsFace);
    }
    if(self->pos[2]>0){
        if(chunk->blocks[(const int)self->pos[1]][(const int)self->pos[0]][(const int)self->pos[2]-1].ID != GRASS){
            drawSelectedFace(negZFace,numVertsFace);
        }
    }
    else if(self->pos[2]==0){
        drawSelectedFace(negZFace,numVertsFace);
    }
    
    
    
    if(self->pos[0]<CHUNK_X_SIZE-1){
        if(chunk->blocks[(const int)self->pos[1]][(const int)self->pos[0]+1][(const int)self->pos[2]].ID != GRASS){
            drawSelectedFace(PosXFace,numVertsFace);
        }
    }
    else if(self->pos[0]==CHUNK_X_SIZE-1){
        drawSelectedFace(PosXFace,numVertsFace);
    }
    if(self->pos[1]<CHUNK_Y_SIZE-1){
        if(chunk->blocks[(const int)self->pos[1]+1][(const int)self->pos[0]][(const int)self->pos[2]].ID != GRASS){
            drawSelectedFace(PosYFace,numVertsFace);
        }
    }
    else if(self->pos[1]==CHUNK_Y_SIZE-1){
        drawSelectedFace(PosYFace,numVertsFace);
    }
    if(self->pos[2]<CHUNK_Z_SIZE-1){
        if(chunk->blocks[(const int)self->pos[1]][(const int)self->pos[0]][(const int)self->pos[2]+1].ID != GRASS){
            drawSelectedFace(PosZFace,numVertsFace);
        }
    }
    else if(self->pos[2]==CHUNK_Z_SIZE-1){
        drawSelectedFace(PosZFace,numVertsFace);
    }
}