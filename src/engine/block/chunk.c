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
#include <camera/camera.h>
#include <render/render.h>
#include <block/entities.h>
#include <block/chunk.h>

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

/*
int findElement(Array *a, u32 Element){
  for(int x=0;x<self->size;x++){
    if(self->iArray[x] == Element){
      return x;
    }
  }
}
*/