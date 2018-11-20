#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "SDL2/SDL.h"
#include "types.h"
#include "input.h"
#include "tokenizer.h"
#include "parser.h"
#include "graphics.h"

#define OPS_PER_FRAME (1024)

extern uint32_t shutdownRequested;