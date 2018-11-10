#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "token.h"
#include "commands.h"

#define DEFAULT_COUNT (64)

tokenlist_t Tokenize(char* str);
size_t GetNextEndIndex(char* str, size_t start, size_t len);
data_t* GetNextData(char* str, size_t* iptr, size_t len, uint32_t type);
uint64_t GetHashCode(char* str);