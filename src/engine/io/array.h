#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <types.h>

typedef struct {
  char *chArray;
  u32 *iArray;
  f32 *fArray;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArrayChar(Array *a, char element);
void insertArrayFloat(Array *a, f32 element);
void insertArrayU32(Array *a, u32 element);
int findElement(Array *a, u32 Element);

void freeArray(Array *a);
void ReadFile(const char *path, Array *a);

#endif