#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/array.h"
#include "../libs/slice.h"

#define DEBUG 1

#define debug_print(fmt, ...) \
            do { if (DEBUG == 1) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#define BUFLEN 1024



typedef struct {
    unsigned int nRed;
    unsigned int nGreen;
    unsigned int nBlue;
} Draw;


typedef struct {
    unsigned int id;
    DynamicArray draws;
} Game;


Draw parseDrawString(const char* string) {
    char TMPSpace[BUFLEN];
    strncpy(TMPSpace, string, BUFLEN - 1);
    char colorBuf[6];
    char intBuf[20];
    char* token = NULL;
    TMPSpace[strlen(string)] = '\0';
    Draw draw;

    draw.nRed = 0;
    draw.nGreen = 0;
    draw.nBlue = 0;

    token = strtok(TMPSpace, ",");
    while (token != NULL) {
        int i = 0;
        int nColor = 0;
        intBuf[0] = token[i];

        while (!isdigit(token[i])) {
           i++; 
        }
        int offset = i;
        for(;isdigit(token[i]); i++) {
            intBuf[i - offset] = token[i];
        }
        intBuf[i - offset] = '\0';
        nColor = atoi(intBuf);

        while(token[i] == ' ') {
            i++;
        }

        // Load color
        offset = i;
        for(;isalpha(token[i]); i++) {
            colorBuf[i - offset] = token[i];
        }
        colorBuf[i - offset] = '\0';

        if (strcmp(colorBuf, "red") == 0) {
            draw.nRed += nColor;
        } else if (strcmp(colorBuf, "green") == 0) {
            draw.nGreen += nColor;
        } else if (strcmp(colorBuf, "blue") == 0) {
            draw.nBlue += nColor;
        } else {
            debug_print("unknown color '%s'\n", colorBuf);
        }

        token = strtok(NULL, ",");
    }
    return draw;
}


DynamicArray *parseDraws(const char* string) {
    DynamicArray* draws = newDynamicArray(5, sizeof(Draw));
    DynamicArray drawStrings;
    initArray(&drawStrings, 5, sizeof(char*));

    char TMPSpace[BUFLEN];
    char* token = NULL;
    char* colorToken = NULL;
    strncpy(TMPSpace, string, BUFLEN - 1);
    TMPSpace[BUFLEN - 1] = '\0';
    token = strtok(TMPSpace, ";");
    debug_print("Parsing draw str: %s\n", string);
    while (token != NULL) {
        const size_t tokenLen = strlen(token);
        char *tokenCopy = strncpy(
            malloc(sizeof(char) * tokenLen),
            token,
            tokenLen
        );

        debug_print("\tWill parse: %s\n", tokenCopy);
        addElement(&drawStrings, &tokenCopy);

        char **strData = drawStrings.data;
        strData[drawStrings.size - 1] = tokenCopy;

        token = strtok(NULL, ";");
    }

    for (int i=0; i < drawStrings.size; i++) {
        char** strData = drawStrings.data;

        debug_print("Parsing '%s' for draws\n", strData[i]);
        Draw draw = parseDrawString(strData[i]);
        addElement(draws, &draw);
    }

    visitArray(&drawStrings, free);
    freeArray(&drawStrings);
    return draws;
}


int main(int argc, char** argv) {
    char BUFFER[BUFLEN]; 
    char SECOND_BUF[BUFLEN];

    DynamicArray games;

    initArray(&games, 10, sizeof(Game));

    while (fgets(BUFFER, BUFLEN, stdin)) {
        Game tmp;
        sscanf(BUFFER, "Game %d: %[^\t\n]\n", &(tmp.id), SECOND_BUF);
        debug_print("%s\n", SECOND_BUF);
        tmp.draws = *parseDraws(SECOND_BUF);
        addElement(&games, &tmp);
    }


    Game* gameArray = games.data;
    for (int i=0; i<games.size; i++) {
        DynamicArray drawArray = gameArray[i].draws;
        freeArray(&drawArray);
    }

    freeArray(&games);

    return 0;
}
