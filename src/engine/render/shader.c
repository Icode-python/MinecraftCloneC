#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <io/array.h>
#include <math.h>
#include <render/shader.h>
#include <types.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/mat2.h>
#include <cglm/mat3.h>
#include <cglm/types.h>



void setUpShaders(const char* vertexPath, const char* fragmentPath, Shader * a){
    u32 vertex, fragment;

    Array fragmentarr;
    ReadFile(fragmentPath, &fragmentarr);

    Array vertexarr;
    ReadFile(vertexPath, &vertexarr);

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char * const*)&vertexarr.chArray, NULL);
    glCompileShader(vertex);
    
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char * const*)&fragmentarr.chArray, NULL);
    glCompileShader(fragment);

    // shader Program
    a->ID = glCreateProgram();
    glAttachShader(a->ID, vertex);
    glAttachShader(a->ID, fragment);
    glLinkProgram(a->ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void use(u32 ID){
    glUseProgram(ID);
}

void setBool(const char *name, bool value,u32 ID){
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
void setInt(const char *name, u32 value, u32 ID){
    glUniform1i(glGetUniformLocation(ID, name), value); 
}
void setFloat(const char *name, f32 value, u32 ID){
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void setVec2(const char *name, const vec2 value, u32 ID){ 
    glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]); 
}
void setXY(const char *name, u32 x, u32 y, u32 ID){ 
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}
// ------------------------------------------------------------------------
void setVec3(const char *name, const vec3 value, u32 ID){ 
    glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]); 
}
void setXYZ(const char *name, u32 x, u32 y, u32 z, u32 ID){ 
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}
// ------------------------------------------------------------------------
void setVec4(const char *name, const vec4 value, u32 ID){ 
    glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]); 
}
void setXYZW(const char *name, u32 x, u32 y, u32 z, u32 w, u32 ID){ 
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}
// ------------------------------------------------------------------------
void setMat2(const char *name, const mat2 mat, u32 ID){
    glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void setMat3(const char *name, const mat3 mat, u32 ID){
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void setMat4(const char *name, const mat4 mat, u32 ID){
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}