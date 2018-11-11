#pragma once

#include <stdint.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "types.h"
#include "graphics.h"
#include "SDL2/SDL.h"

#define TURTLE_DIRECTIONS (8)

extern turtle_t _turtle;

void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle);

void MoveTurtle(double distance);
void RotateTurtle(double angle);
void SetTurtlePosition(double x, double y);