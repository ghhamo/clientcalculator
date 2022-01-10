#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <assert.h>

char *getSubString(unsigned int start, unsigned int end, const char *expression_string)
{
    char *line = malloc((end - start + 1) * sizeof(char));
    for (int i = 0; i < end - start; ++i)
    {
        line[i] = expression_string[start + i];
    }
    line[end - start] = '\0';
    return line;
}

char *readInput() {
#define CHUNK 200
    char *input = NULL;
    char tempBuf[CHUNK];
    size_t inputLen = 0, tempLen;
    do {
        fgets(tempBuf, CHUNK, stdin);
        tempLen = strlen(tempBuf);
        input = realloc(input, inputLen + tempLen + 1);
        strcpy(input + inputLen, tempBuf);
        inputLen += tempLen;
    } while (tempLen == CHUNK - 1 && tempBuf[CHUNK - 2] != '\n');
    return input;
}
#endif