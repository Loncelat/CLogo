#include "graphics.h"

Turtle_t turtle;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *canvas = NULL;

int InitGraphics(void) {
    window = SDL_CreateWindow(
            "CLogo",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,
            HEIGHT,
            0);

    if (window == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    canvas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT);

    if (InitTurtle(&turtle)) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(renderer);
    DrawTurtle(renderer, &turtle);
    
    SDL_RenderPresent(renderer);

    return 0;
}

SDL_Texture* LoadImage(char* file) {
    SDL_Surface *image = IMG_Load(file);

    if (image == NULL) {
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    if (texture == NULL) {
        return NULL;
    }

    SDL_FreeSurface(image);
    return texture;
}

int InitTurtle(Turtle_t *turtle) {

    ResetTurtle(turtle);
    turtle->texture = LoadImage("graphics/turtle.png");

    if (turtle->texture == NULL) {
        return 1;
    }

    if (SDL_QueryTexture(turtle->texture, NULL, NULL, &turtle->width, &turtle->height) != 0) {
        return 1;
    }

    turtle->width /= TURTLE_DIRECTIONS;

    turtle->dstrect = (SDL_Rect) { turtle->x, turtle->y, turtle->width, turtle->height, };

    return 0;
}

void ResetTurtle(Turtle_t *turtle) {
    turtle->x = INIT_TURTLE_X;
    turtle->y = INIT_TURTLE_Y;
    turtle->angle = 0;
    turtle->rotation = 0;
}

void DrawTurtle(SDL_Renderer *renderer, Turtle_t *turtle) {

    SDL_Rect srcrect = (SDL_Rect) {
        turtle->width * turtle->rotation,
        0,
        turtle->width,
        turtle->height,
    };

    /* update the coordinates in the dstrect */
    turtle->dstrect.x = turtle->x;
    turtle->dstrect.y = turtle->y;

    SDL_RenderCopy(renderer, turtle->texture, &srcrect, &turtle->dstrect);

}