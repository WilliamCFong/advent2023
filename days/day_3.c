#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../libs/array.h"


typedef struct {
    int value;
    unsigned int startX;
    unsigned int endX;
    unsigned int y;
} SpacialNumber;

typedef struct {
    char symbol;
    unsigned int x;
    unsigned int y;
} SpacialSymbol;


int loadNumber(const char *BUFFER, int* pos) {
    // Read the number from BUFFER at position pos. Interate pos
    // until the full number is read, modifying the value of pos to
    // reflect consumed symbols
    char numericalBUF[16];
    int j = 0;
    while (isdigit(BUFFER[*pos])) {
        numericalBUF[j] = BUFFER[*pos];
        j++;
        (*pos)++;
    }
    // j points to unknown part of stack
    numericalBUF[j] = '\0'; // So set it as end of string
    return atoi(numericalBUF);
}

void parseInput(DynamicArray *numbers, DynamicArray *symbols) {
    char BUFFER[1024];
    int y = 0;
    while (scanf("%s\n", BUFFER) != EOF) {
        printf("%s\n", BUFFER);
        for (int i=0; BUFFER[i] != '\0'; i++) {
            const char c = BUFFER[i];
            if (isdigit(c)) {
                SpacialNumber snum;
                snum.startX = i;
                snum.y = y;
                snum.value = loadNumber(BUFFER, &i);
                snum.endX = i - 1;

                addElement(numbers, &snum);
                continue;
            }
            if (c != '.') {
                SpacialSymbol ssym;
                ssym.symbol = c;
                ssym.x = i;
                ssym.y = y;

                addElement(symbols, &ssym);
            }
        }
        y++;
    }
}



int main(int argc, char** argv) {
    DynamicArray numbers;
    DynamicArray symbols;
    initArray(&numbers, 10, sizeof(SpacialNumber));
    initArray(&symbols, 10, sizeof(SpacialSymbol));

    parseInput(&numbers, &symbols);

    printf("# of Numbers: %d\n", numbers.size);
    printf("# of Symbols: %d\n", symbols.size);

    for (int i=0; i < numbers.size; i++) {
        SpacialNumber *data = numbers.data;
        printf("%d, [%d, %d]\n", data[i].value, data[i].startX, data[i].endX);
    }

    for (int i=0; i < symbols.size; i++) {
        SpacialSymbol *data = symbols.data;
        printf("%c\n", data[i].symbol);
    }

    freeArray(&numbers);
    freeArray(&symbols);

    return 0;
}
