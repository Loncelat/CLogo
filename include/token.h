#pragma once

#include <stdint.h>

enum {
    UNKNOWN, RPARENS, LPARENS, OPERATOR,
};

typedef struct Token {
    char* value;
    uint32_t type;
} Token;

typedef struct TokenList {
    Token** tokens;
    size_t count;
} TokenList;