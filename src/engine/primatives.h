#ifndef PRIMATIVES_H
#define PRIMATIVES_H
#include <stdio.h>
#include <string.h>
#include <types.h>
 
extern f32 cube_vertices[180];


// cube face list coordinates 
// so gl can render faces that are only visible and arent rendering faces on inside
#define PosXFace 18
#define negXFace 12

#define PosYFace 24
#define negYFace 16

#define PosZFace 6
#define negZFace 0

#define numVertsFace 6
#define allFaces 36

#endif