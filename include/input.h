#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK_SIZE (1024)

char* ReadInput(void);
char* Trim(char* str);