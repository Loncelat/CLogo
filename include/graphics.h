#pragma once

#include <stdint.h>
#include <stdio.h>

#include "types.h"
#include "turtle.h"
#include "main.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define WIDTH  (400)
#define HEIGHT (400)

#define RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE)

#define INIT_TURTLE_X (WIDTH / 2.0)
#define INIT_TURTLE_Y (HEIGHT / 2.0)

#define FRAMES_PER_SECOND (60)
#define FRAME_FREQUENCY (1000.0 / FRAMES_PER_SECOND)

#define VSYNC_SHOULD_WAIT ((SDL_GetPerformanceCounter() - vsyncStartTime) * freqMultiplier < FRAME_FREQUENCY)
#define VSYNC_WAIT (SDL_Delay((FRAME_FREQUENCY) - (SDL_GetPerformanceCounter() - vsyncStartTime) * freqMultiplier))

extern SDL_Renderer *_renderer;

int InitGraphics(void);
int InitTurtle(turtle_t *turtle);
void ResetTurtle(turtle_t *turtle);

void ClearGraphics(SDL_Renderer *renderer);

void SetForeground(double r, double g, double b);
void SetBackground(double r, double g, double b);

void Draw(void);