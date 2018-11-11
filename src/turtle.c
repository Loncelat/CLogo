#include "turtle.h"

turtle_t _turtle;

void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle) {

    if (!turtle->visible) {
        return;
    }

    turtle->rotation = (uint8_t) ( (turtle->angle * 4 / M_PI) + 0.5) % TURTLE_DIRECTIONS;

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
    _turtle.angle = fmod(_turtle.angle, 2 * M_PI);
}

void SetTurtlePosition(double x, double y) {
    _turtle.x = x;
    _turtle.y = y;
}