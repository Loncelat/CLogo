#include "graphics.h"

colour_t bgClr = {0, 255, 255};
colour_t fgClr = {0, 0, 0};

SDL_Window *_window = NULL;
SDL_Renderer *_renderer = NULL;
SDL_Texture *_background = NULL;
SDL_Texture *_canvas = NULL;

SDL_Event event;

uint64_t vsyncStartTime = 0;
double freqMultiplier = 0;

int InitGraphics(void) {
    _window = SDL_CreateWindow(
        "CLogo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        0
    );

    if (_window == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    _renderer = SDL_CreateRenderer(_window, -1, RENDERER_FLAGS);

    if (_renderer == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    /* Create the textures. */
    _canvas = SDL_CreateTexture(
        _renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_TARGET,
        WIDTH,
        HEIGHT
    );

    SDL_SetTextureBlendMode(_canvas, SDL_BLENDMODE_BLEND);

    if (InitTurtle(&_turtle)) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    freqMultiplier = 1000.0 / SDL_GetPerformanceFrequency();

    SDL_SetRenderTarget(_renderer, _canvas);
    ClearGraphics(_renderer);

    Draw();

    return 0;
}

SDL_Texture* LoadImage(char* file) {
    SDL_Surface *image = IMG_Load(file);

    if (image == NULL) {
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, image);

    if (texture == NULL) {
        return NULL;
    }

    SDL_FreeSurface(image);
    return texture;
}

int InitTurtle(turtle_t *turtle) {

    turtle->texture = LoadImage("graphics/turtle.png");

    if (turtle->texture == NULL) {
        return 1;
    }

    SDL_SetTextureBlendMode(turtle->texture, SDL_BLENDMODE_BLEND);
    if (SDL_QueryTexture(turtle->texture, NULL, NULL, &turtle->w, &turtle->h) != 0) {
        return 1;
    }

    turtle->w /= TURTLE_DIRECTIONS;

    turtle->dstrect = (SDL_Rect) {0, 0, turtle->w, turtle->h};

    return 0;
}

void ResetTurtle(turtle_t *turtle) {
    turtle->x = INIT_TURTLE_X;
    turtle->y = INIT_TURTLE_Y;
    turtle->angle = M_PI / 2.0;
    turtle->rotation = 0;
    turtle->pd = 1;
    turtle->visible = 1;
}

void ClearGraphics(SDL_Renderer *renderer) {

    ResetTurtle(&_turtle);

    /* Reset background colour to white */
    bgClr = (colour_t) {255, 255, 255};
    SDL_SetRenderDrawColor(renderer, bgClr.r, bgClr.g, bgClr.b, SDL_ALPHA_OPAQUE);

    /* Clear the background */
    SDL_RenderClear(renderer);

    /* Clear the canvas (transparent) */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, _canvas);
    SDL_RenderClear(renderer);

    /* Restore the colour to the foreground colour */
    SDL_SetRenderDrawColor(renderer, fgClr.r, fgClr.g, fgClr.b, SDL_ALPHA_OPAQUE);

}

void Draw(void) {

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shutdownRequested = 1;
        }
    }

    if (VSYNC_SHOULD_WAIT) {
        VSYNC_WAIT;
    }

    /* Set render target to the window. */
    SDL_SetRenderTarget(_renderer, NULL);

    /* Clear the background */
    SDL_SetRenderDrawColor(_renderer, bgClr.r, bgClr.g, bgClr.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);

    /* Draw the canvas and turtle. */
    SDL_RenderCopy(_renderer, _canvas, NULL, NULL);
    DrawTurtle(_renderer, &_turtle);

    SDL_RenderPresent(_renderer);

    /* Restore the render target to the canvas. */
    SDL_SetRenderTarget(_renderer, _canvas);
    SDL_SetRenderDrawColor(_renderer, fgClr.r, fgClr.g, fgClr.b, SDL_ALPHA_OPAQUE);

    vsyncStartTime = SDL_GetPerformanceCounter();
}

void SetForeground(double r, double g, double b) {
    fgClr = (colour_t) {(int) r % 256, (int) g % 256, (int) b % 256};
    SDL_SetRenderDrawColor(_renderer, fgClr.r, fgClr.g, fgClr.b, SDL_ALPHA_OPAQUE);
}
void SetBackground(double r, double g, double b) {
    bgClr = (colour_t) {(int) r % 256, (int) g % 256, (int) b % 256};
}