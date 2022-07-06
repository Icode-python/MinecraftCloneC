#ifndef CHUNK_H
#define CHUNK_H
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

typedef enum {
  CHUNK_Z_SIZE = 16,
  CHUNK_X_SIZE = 16,
  CHUNK_Y_SIZE = 256
} CHUNK_SIZE;

typedef struct chunk{
  Entity blocks[CHUNK_Y_SIZE][CHUNK_X_SIZE][CHUNK_Z_SIZE];
  vec3 positions[CHUNK_Y_SIZE][CHUNK_X_SIZE][CHUNK_Z_SIZE];
} Chunk;

typedef struct {
  Chunk * array;
  size_t used;
  size_t size;
} chunk_array;


void chunk_init(Chunk * self);
void render_chunk(Chunk *self);
void render_shown(Chunk * chunk, Entity * self);

#endif