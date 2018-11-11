#include "turtle.h"

/* Piecewise function */
#define NORM_ANGLE(x) (x < 0 ? 2 * M_PI + (x) : (x))

turtle_t _turtle;

void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle) {

    if (!turtle->visible) {
        return;
    }

    double dividend = floor((NORM_ANGLE(turtle->angle) / M_PI_4) + 0.5);
    turtle->rotation = (uint8_t) dividend % TURTLE_DIRECTIONS;

    SDL_Rect srcrect = (SDL_Rect) {
        turtle->w * turtle->rotation,
        0,
        turtle->w,
        turtle->h,
    };

    /* update the coordinates in the dstrect */
    turtle->dstrect.x = turtle->x - turtle->w / 2.0;
    turtle->dstrect.y = turtle->y - turtle->h;

    SDL_RenderCopy(renderer, turtle->texture, &srcrect, &turtle->dstrect);

}

void MoveTurtle(double distance) {
    int oldX = (int) _turtle.x;
    int oldY = (int) _turtle.y;

    _turtle.x += cos(_turtle.angle) * distance;
    _turtle.y -= sin(_turtle.angle) * distance;

    if (_turtle.pd) {
        SDL_RenderDrawLine(_renderer, oldX, oldY, (int) _turtle.x, (int) _turtle.y);
    }
}

void RotateTurtle(double angle) {
    _turtle.angle += angle * (M_PI / 180.0);
}

void SetTurtlePosition(double x, double y) {
    _turtle.x = x;
    _turtle.y = y;
}