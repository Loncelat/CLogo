#pragma once

#include <stdint.h>
#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define WIDTH  (400)
#define HEIGHT (400)

#define INIT_TURTLE_X (WIDTH / 2.0)
#define INIT_TURTLE_Y (HEIGHT / 2.0)
#define TURTLE_DIRECTIONS (8)

typedef struct Turtle {
    double x;
    double y;
    double angle;

    int width;
    int height;

    SDL_Texture *texture;
    uint8_t rotation;

    SDL_Rect dstrect;

} Turtle_t;

int InitGraphics(void);
int InitTurtle(Turtle_t *turtle);
void ResetTurtle(Turtle_t *turtle);

void DrawTurtle(SDL_Renderer *renderer, Turtle_t *turtle);