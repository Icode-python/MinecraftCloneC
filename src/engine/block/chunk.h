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

typedef struct chunk{
  Entity blocks[256][16][16];
  vec3 positions[256][16][16];
} Chunk;

typedef struct {
  Chunk * array;
  size_t used;
  size_t size;
} chunk_array;


#endif