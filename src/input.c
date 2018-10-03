#include "input.h"

char* ReadInput(void) {
    char chunk[CHUNK_SIZE];
    char* text = calloc(DEF_SIZE * sizeof(char), sizeof(char));

    size_t length = 0;
    size_t len = 0;

    do {
        fgets(chunk, sizeof(chunk), stdin);
        len = strlen(chunk);

        printf("Read chunk: %s\n", chunk);

        // TODO: check for SIZE_MAX

        char* tmp = realloc(text, length + len + 1);
        if (tmp == NULL) {
            break;
        }
        text = tmp;

        strcpy(text + length, chunk);
        length += len;

        if (feof(stdin) || chunk[len - 1] == '\n') {
            return text;
        }
    } while (len > 0);

    free(text);
    return NULL;
}