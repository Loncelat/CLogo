#pragma once

#include <stdint.h>

enum {
    UNKNOWN, RPARENS, LPARENS,
};

typedef struct Token {
    char* value;
    uint32_t type;
} Token;