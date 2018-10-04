#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "token.h"

#define DEFAULT_COUNT (64)

TokenList Tokenize(char* text, size_t len);