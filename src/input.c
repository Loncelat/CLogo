#include "input.h"

char* ReadInput(void) {
    char chunk[CHUNK_SIZE];
    char* text = calloc(CHUNK_SIZE * sizeof(char), sizeof(char));

    size_t length = 0;
    size_t len = 0;

    do {
        fgets(chunk, sizeof(chunk), stdin);
        len = strlen(chunk);

        // TODO: check for SIZE_MAX

        // Use a second pointer to avoid leaking text if an error occurs.
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

char* Trim(char* str) {

    if (str == NULL) { return NULL; }
    if (str[0] == '\0') { return str; }

    size_t len = strlen(str);
    char* front = str;
    char* end = front + len;

    while (isspace(*front)) { front += 1; }
    if (front != end) {
        while (isspace(*(--end)) && end != front) { }
    }

    // If there was trailing whitespace.
    if (str + len - 1 != end) {
        *(end + 1) = '\0';
    }

    char* index = str;

    // If there was leading whitespace.
    if (front != str) {

        // Loop until null byte.
        while (*front) {
            *index = *front;
            index += 1;
            front += 1;
        }
        *index = '\0';
    }

    return str;
}