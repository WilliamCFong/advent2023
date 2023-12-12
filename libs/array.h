#ifndef __ARRAY_H___
#define __ARRAY_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
    int size;
    int capacity;
    size_t dataTypeSize;
    void *data;

} DynamicArray;


void initArray(DynamicArray *arr, int capacity, size_t dataTypeSize);
void addElement(DynamicArray *arr, void* element);
void freeArray(DynamicArray *arr);
DynamicArray* newDynamicArray(int capacity, size_t dataTypeSize);


void* elementAt(DynamicArray *arr, int idx);
void visitArray(DynamicArray *arr, void(*func)(void*));

#endif
