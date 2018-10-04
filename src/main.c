#include "main.h"

int main(int argc, char** argv) {

    // Temporary stuff.
    argc = argc;
    argv = argv;

    char* line = ReadInput();
    printf("Read %s", line);

    // TODO: trim leading/trailin whitespace.

    Tokenize(line, strlen(line));
    free(line);
}