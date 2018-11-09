#pragma once

#include <stdint.h>
#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define WIDTH  (400)
#define HEIGHT (400)

#define RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE)

#define INIT_TURTLE_X (WIDTH / 2.0)
#define INIT_TURTLE_Y (HEIGHT / 2.0)
#define TURTLE_DIRECTIONS (8)

#define FRAMES_PER_SECOND (60)
#define FRAME_FREQUENCY (1000.0 / FRAMES_PER_SECOND)

#define VSYNC_SHOULD_WAIT ((SDL_GetPerformanceCounter() - vsyncStartTime) * freqMultiplier < FRAME_FREQUENCY)
#define VSYNC_WAIT (SDL_Delay((FRAME_FREQUENCY) - (SDL_GetPerformanceCounter() - vsyncStartTime) * freqMultiplier))

typedef struct Turtle {
    double x;
    double y;
    double angle;

    int width;
    int height;

    SDL_Texture *texture;
    uint8_t rotation;

    SDL_Rect dstrect;

} turtle_t;

typedef struct Colour {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour_t;

int InitGraphics(void);
int InitTurtle(turtle_t *turtle);
void ResetTurtle(turtle_t *turtle);

void ClearGraphics(SDL_Renderer *renderer);

void Draw(void);
void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle);