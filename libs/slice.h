#ifndef __SLICE_H__
#define __SLICE_H__

#include "string.h"


typedef struct {
    int start;
    int end;
} Slice;

Slice initSlice();
Slice findFirstWith(const char* toSearch, const char* substring);
Slice findFirstWithOffset(const char* toSearch, const char* substring, int offset);

#endif
