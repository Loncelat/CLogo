#pragma once

#include <stdint.h>

typedef struct Token {
    char* value;
    uint32_t type;
} Token;