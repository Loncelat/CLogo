#include "commands.h"

int32_t GetArgumentCount(uint64_t hash) {
    switch(hash) {
        
        case HASH_ST:
        case HASH_HT:
        case HASH_CS:
            return 0;
        
        case HASH_FD:
        case HASH_BK:
        case HASH_RT:
        case HASH_LT:
            return 1;

        case HASH_SETPOS:
            return 2;

        case HASH_SETPC:
        case HASH_SETBC:
            return 3;

    }

    return 0;
}