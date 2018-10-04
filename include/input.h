#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK_SIZE (128)
#define DEF_SIZE (128)

char* ReadInput(void);
char* Trim(char* string);