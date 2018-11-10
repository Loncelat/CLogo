#pragma once

#include <stdint.h>
#include "SDL2/SDL.h"

#define DATA_TEXT (0)
#define DATA_NUM (1)

typedef struct turtle {
    double x;
    double y;

    /* Angle in radians */
    double angle;

    int32_t w;
    int32_t h;

    SDL_Texture *texture;
    uint8_t rotation;

    SDL_Rect dstrect;

    /* Pen up/Pen down */
    uint32_t pd : 1;
    uint32_t visible : 1;

} turtle_t;

typedef struct colour {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour_t;

/* Struct used to reference data passed to a command. */
typedef struct data {
    union {
        char* text;
        double number;
    };

    uint32_t type : 1;
} data_t;

typedef struct token {
    char* value;
    uint64_t hash;

    /* Keep track of an array of the arguments. */
    data_t** arg;
    size_t argc;
} token_t;

typedef struct tokenlist {
    token_t** tokens;
    size_t count;
} tokenlist_t;