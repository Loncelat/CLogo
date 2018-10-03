#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "token.h"

#define DEFAULT_COUNT (128)

Token** Tokenize(char* text, size_t len);