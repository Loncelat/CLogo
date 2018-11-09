#pragma once

#include <stdint.h>

/* Struct used to reference data passed to a command. */
typedef struct data {
    union {
        char* text;
        uint64_t number;
    };
} data_t;

typedef struct token {
    char* value;
    uint64_t hash;

    /* Keep track of an array of the arguments. */
    data_t** arguments;
} token_t;

typedef struct tokenlist {
    token_t** tokens;
    size_t count;
} tokenlist_t;