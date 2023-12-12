#include "slice.h"


Slice initSlice() {
    Slice slice;
    slice.start = -1;
    slice.end = -1;
    return slice;
}


Slice findFirstWith(const char* toSearch, const char* substring) {
    return findFirstWithOffset(toSearch, substring, 0);
}


Slice findFirstWithOffset(const char* toSearch, const char* substring, int offset) {
    Slice slice = initSlice();
    int i, j;
    int substringLength = strlen(substring);
    int toSearchLength = strlen(toSearch);
 
    for (i = 0; i <= toSearchLength - substringLength; i++) {
        for (j = 0; j < substringLength; j++) {
            if (toSearch[i + j] != substring[j])
                break;
        }
        if (j == substringLength) {
            // Strings are equal
            slice.start = j - substringLength;
            slice.end = j - 1;
            break;
        }
    }
    return slice;
}
