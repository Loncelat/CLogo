#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "input.h"
#include "tokenizer.h"
#include "parser.h"
#include "graphics.h"

#define OPS_PER_FRAME (1024)

extern uint32_t shutdownRequested;