#include "parser.h"

int Parse(token_t *token) {
    
    switch(token->hash) {
        
        case HASH_FD:
            MoveTurtle(10);
            break;

        case HASH_BK:
            MoveTurtle(-10);
            break;

        case HASH_RT:
            RotateTurtle(-10);
            break;

        case HASH_LT:
            RotateTurtle(10);
            break;
        default:
            return 1;
    }

    return 0;
}