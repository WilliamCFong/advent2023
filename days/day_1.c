#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


const char ONE[] = "one";
const char TWO[] = "two";
const char THREE[] = "three";
const char FOUR[] = "four";
const char FIVE[] = "five";
const char SIX[] = "six";
const char SEVEN[] = "seven";
const char EIGHT[] = "eight";
const char NINE[] = "nine";

//const char ZERO_D[] = "0";
//const char ONE_D[] = "1";
//const char TWO_D[] = "2";
//const char THREE_D[] = "3";
//const char FOUR_D[] = "4";
//const char FIVE_D[] = "5";
//const char SIX_D[] = "6";
//const char SEVEN_D[] = "7";
//const char EIGHT_D[] = "8";
//const char NINE_D[] = "9";


const char* NUM_MATRIX[9] = {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
}; // Needs to be in order


int makeNum(char c) {
    char NUMBUF[2] = "0\0";
    NUMBUF[0] = c;
    return atoi(NUMBUF);
};


bool doesMatch(const char *BUFFER, const char *compare, int i) {
    // Returns True if BUFFER starting at position i matches the given
    // string compare
    unsigned short BUFLEN = strlen(BUFFER);
    unsigned short CMPLEN = strlen(compare);

    if ((i + CMPLEN - 1) >= BUFLEN) {
        // Impossible to match
        return false;
    }

    for (unsigned short j=0; j < CMPLEN; j++) {
        if (compare[j] != BUFFER[j+i]) {
            return false;
        }
    }
    // All characters matched
    return true;
};


int match(const char* BUFFER, unsigned short length, int i) {
    // Attempt to match buffer at position i to the numerical definition matrix
    unsigned short matrixLength = (unsigned short) (sizeof(NUM_MATRIX) / sizeof(char*));

    for (unsigned short j = 0; j < matrixLength; j++) {
        const char* strNum = NUM_MATRIX[j];
        if (doesMatch(BUFFER, strNum, i)) {
            return j + 1;
        };
    }
    return -1; // No match
};


int findNumbers(const char* BUFFER) {
    unsigned short length = strlen(BUFFER);
    int first = -1;
    int second = -1;

    int hitIdx = -1;

    for (unsigned short i = 0; i < length; i++) {
        char c = BUFFER[i];
        if (isdigit(c)) {
            first = makeNum(c);
            hitIdx = i;
            break;
        }
    }

    if (first < 0) {
        // Found no numerical strings
        return -1;
    }

    for (int i = length - 1; i > (hitIdx - 1); i--) {
        char c = BUFFER[i];
        if (isdigit(c)) {
            second = makeNum(c);
            break;
        }
    }

    return (first * 10) + second;

};


void printStack(int n, int* numberStack) {
    for (int i=0; i < n; i++) {
        printf("[%d]: %d\n", i, numberStack[i]);
    }
};


int findNumbersAsStrings(const char* BUFFER) {
    unsigned short length = strlen(BUFFER);
    unsigned short nNum = 0;
    int* numberStack = (int*) malloc(length * sizeof(int));

    for (int i = 0; i < length; i++) {
        if (isdigit(BUFFER[i])) {
            numberStack[nNum] = makeNum(BUFFER[i]);
            nNum++;
            continue;
        }
        int intMatch = match(BUFFER, length, i);
        if (intMatch > 0) {
            numberStack[nNum] = intMatch;
            nNum++;
            continue;
        }
    }

    if (nNum == 0) {
        return 0;
    }

    //printStack(nNum, numberStack);

    int startInteger = numberStack[0];
    int endInteger = numberStack[nNum - 1];

    free(numberStack);
    return (startInteger * 10) + endInteger;
};


int main(int argc, char** argv) {

    const char BUFFER[1024];
    int sum = 0;

    while (scanf("%s\n", BUFFER) != EOF) {
        int result = findNumbersAsStrings(BUFFER);
        if (result < 0) {
            printf("BAD STRING '%s'\n", BUFFER);
            return 1;
        } else {
            sum += result;
        }
    }
    printf("%d\n", sum);
    return 0;
};
