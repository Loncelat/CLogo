#include "main.h"

int main(int argc, char** argv) {

    // Temporary stuff.
    argc = argc;
    argv = argv;

    if (InitGraphics()) {
        return 1;
    }

    while (1) {

        char* line = ReadInput();
        line = Trim(line);

        #ifdef DEBUG
        printf("Got input [%s]\n", line);
        #endif

        TokenList tokens = Tokenize(line);
        free(line);

        /* Count how many actions have been performed. */
        size_t operationCount = 0;

        // TODO: handle events in main loop.

        /* Loop over the tokens */
        for (size_t i = 0; i < tokens.count; ++i) {
            
            if (Parse(tokens.tokens[i])) {
                /* Something went wrong */
                printf("Unknown token: %s\n", tokens.tokens[i]->value);
                Draw();
                break;
            }

            if (operationCount >= OPS_PER_FRAME) {
                Draw();
                operationCount = 0;
            }

        }

        Draw();

    }

    return 0;
}