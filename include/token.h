#pragma once

#include <stdint.h>

enum {
    UNKNOWN, RPARENS, LPARENS, OPERATOR,
};

/* Struct used to reference data passed to a command. */
typedef struct Data {
    union {
        char* text;
        uint64_t number;
    };
} Data;

typedef struct Token {
    char* value;
    uint32_t type;

    /* Keep track of an array of the arguments. */
    Data** arguments;
} Token;

typedef struct TokenList {
    Token** tokens;
    size_t count;
} TokenList;