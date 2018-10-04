#include "main.h"

int main(int argc, char** argv) {

    // Temporary stuff.
    argc = argc;
    argv = argv;

    char* line = ReadInput();
    line = Trim(line);

    #ifdef DEBUG
    printf("Got input [%s]\n", line);
    #endif


    TokenList tokens = Tokenize(line);
    free(line);
}