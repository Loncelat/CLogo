#include "parser.h"

int Parse(token_t *token) {
    
    switch(token->hash) {
        
        case HASH_FD:
            MoveTurtle(token->arg[0]->number);
            break;

        case HASH_BK:
            MoveTurtle(-token->arg[0]->number);
            break;

        case HASH_RT:
            RotateTurtle(-token->arg[0]->number);
            break;

        case HASH_LT:
            RotateTurtle(token->arg[0]->number);
            break;

        case HASH_PD:
            _turtle.pd = 1;
            break;

        case HASH_PU:
            _turtle.pd = 0;
            break;

        case HASH_PI:
            _turtle.pd = !_turtle.pd;
            break;

        case HASH_ST:
            _turtle.visible = 1;
            break;

        case HASH_HT:
            _turtle.visible = 0;
            break;

        case HASH_CS:
            ClearGraphics(_renderer);
            break;

        case HASH_SETPOS:
            SetTurtlePosition(token->arg[0]->number, token->arg[1]->number);
            break;

        case HASH_SETPC:
            SetForeground(token->arg[0]->number, token->arg[1]->number, token->arg[2]->number);
            break;

        case HASH_SETBC:
            SetBackground(token->arg[0]->number, token->arg[1]->number, token->arg[2]->number);
            break;

        default:
            return 1;
    }

    return 0;
}