#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "token.h"

#define DEFAULT_COUNT (64)

TokenList Tokenize(char* string);
size_t GetNextEndIndex(char* string, size_t start, size_t len);