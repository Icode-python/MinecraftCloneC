#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <io/array.h>
#include <render/shader.h>
#include <stdbool.h>
#include <types.h>
#include <render/render.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <global.h>
#include <camera/camera.h>
#include <render/render.h>
#include <block/entities.h>
#include <block/chunk.h>

void chunk_init(Chunk * self){
  for(int y=0; y<CHUNK_Y_SIZE; y++){
    for(int x=0; x<CHUNK_X_SIZE; x++){
      for(int z=0; z<CHUNK_Z_SIZE; z++){
        glm_vec3_copy((vec3){(f32)x, (f32)y, (f32)z},self->positions[y][x][z]); 
        if(y<16){
          entity_init(&self->blocks[y][x][z], self->positions[y][x][z], global.state.texture,GRASS);
        }
        else{
          entity_init(&self->blocks[y][x][z], self->positions[y][x][z], global.state.texture,AIR);
        }
      }
    }
  }
}

void render_chunk(Chunk *self){
  render_begin(&global.camera);
  for(int y=0; y<CHUNK_Y_SIZE; y++){
    for(int x=0; x<CHUNK_X_SIZE; x++){
      for(int z=0; z<CHUNK_Z_SIZE; z++){
          use(global.state.shader.ID);
          
          if(self->blocks[y][x][z].ID != AIR){
            Translate(self->positions[y][x][z], global.state.shader.ID);
            render_shown(self,&self->blocks[y][x][z]);
          }
          //glBindVertexArray(global.state.VAO);
          //glDrawArrays(GL_TRIANGLES, 0, allFaces);
      }
    }
  }
  render_end();
}

void block_array_init(chunk_array *self, size_t initialSize) {
    self->array = malloc(initialSize *sizeof(Chunk));
}

void chunk_append(chunk_array *self, Chunk element) {
  // self->used is the number of used entries, because self->array[self->used++] updates self->used only *after* the array has been accessed.
  // Therefore self->used can go up to self->size 
  if (self->used == self->size) {
    self->size *= 2;
    self->array = realloc(self->array, self->size * sizeof(Chunk));
  }
  self->array[self->used++] = element;
}

void freeChunkArray(chunk_array *self){
  free(self->array);
  self->used = self->size = 0;
}
