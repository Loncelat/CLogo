#include "main.h"

uint32_t shutdownRequested = 0;

int main(int argc, char** argv) {

    // Temporary stuff.
    argc = argc;
    argv = argv;

    if (InitGraphics()) {
        return 1;
    }

    while (!shutdownRequested) {

        tokenlist_t tokens = {NULL, 0};

        while (tokens.tokens == NULL) {
            char* line = ReadInput();
            line = Trim(line);

            #ifdef DEBUG
            printf("Got input [%s]\n", line);
            #endif

            tokens = Tokenize(line);
            free(line);
        }

        /* Count how many actions have been performed. */
        size_t operationCount = 0;

        // TODO: handle events in main loop.

        /* Loop over the tokens */
        for (size_t i = 0; i < tokens.count; ++i) {
            
            if (Parse(tokens.tokens[i])) {
                /* Something went wrong */
                printf("Unknown token: [%s]\n", tokens.tokens[i]->value);
                Draw();
                break;
            }

            if (operationCount >= OPS_PER_FRAME) {
                Draw();
                operationCount = 0;
            }

        }

        Draw();
        
        for (size_t i = 0; i < tokens.count; i++) {
            free(tokens.tokens[i]->value);

            // Free all data.
            for (size_t k = 0; k < tokens.tokens[i]->argc; k++) {
                free(tokens.tokens[i]->arg[k]);
            }
            free(tokens.tokens[i]->arg);
            
            free(tokens.tokens[i]);
        }
        free(tokens.tokens);


    }

    return 0;
}