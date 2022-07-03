#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <io/array.h>
#include <render/shader.h>
#include <stdbool.h>
#include <types.h>
#include <render/render.h>
#include <stdbool.h>

int texInit(const char * path, u32 * texture, bool flip, bool has_rgba);

#endif