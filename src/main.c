#include "main.h"

int main(int argc, char** argv) {
    char* line = ReadInput();
    printf("Read %s", line);
    //Tokenize(line, strlen(line));
    free(line);
}