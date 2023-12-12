#include "array.h"


void initArray(DynamicArray *arr, int capacity, size_t dataTypeSize) {
    arr->data = malloc(capacity * dataTypeSize);
    arr->size = 0;
    arr->capacity = capacity;
    arr->dataTypeSize = dataTypeSize;
}

void addElement(DynamicArray *arr, void* element) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(arr->dataTypeSize));
    }
    void *cursor = elementAt(arr, arr->size++);

    memcpy(cursor, element, arr->dataTypeSize);
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}


DynamicArray* newDynamicArray(int capacity, size_t dataTypeSize) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    initArray(arr, capacity, dataTypeSize);
    return arr;
}

void* elementAt(DynamicArray *arr, int idx) {
    void *data = arr->data;

    return (void *) &(data[idx * arr->dataTypeSize]);
}


void visitArray(DynamicArray *arr, void(*func)(void*)) {
    for(int i=0; i < arr->size; i++) {
        (*func)(&(arr->data[i]));
    }
};
