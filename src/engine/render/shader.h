#ifndef SHADER_H
#define SHADER_H
#include <stdbool.h>
#include <types.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/mat2.h>
#include <cglm/mat3.h>
#include <cglm/types.h>

typedef struct shader{
    u32 ID;
}Shader;

void shader_create(const char* vertexPath, const char* fragmentPath, Shader * a);
// use/activate the shader
void use(u32 ID);
// utility uniform functions
void setBool(const char *name, bool value, u32 ID);  
void setInt(const char *name, u32 value, u32 ID);   
void setFloat(const char *name, f32 value, u32 ID);
void setVec2(const char *name, const vec2 value, u32 ID);
void setXY(const char *name, u32 x, u32 y, u32 ID);
void setVec3(const char *name, const vec3 value, u32 ID);
void setXYZ(const char *name, u32 x, u32 y, u32 z, u32 ID);
void setVec4(const char *name, const vec4 value, u32 ID);
void setXYZW(const char *name, u32 x, u32 y, u32 z, u32 w, u32 ID);
void setMat2(const char *name, const mat2 mat, u32 ID);
void setMat3(const char *name, const mat3 mat, u32 ID);
void setMat4(const char *name, const mat4 mat, u32 ID);


#endif