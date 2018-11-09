#include "graphics.h"

turtle_t turtle;

colour_t bgClr = {0, 255, 255};
colour_t fgClr = {0, 0, 0};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *background = NULL;
SDL_Texture *canvas = NULL;

uint64_t vsyncStartTime = 0;
double freqMultiplier = 0;

int InitGraphics(void) {
    window = SDL_CreateWindow(
        "CLogo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        0
    );

    if (window == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);

    if (renderer == NULL) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    /* Create the textures. */
    background = SDL_CreateTexture(        
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_TARGET,
        WIDTH,
        HEIGHT
    );

    canvas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_TARGET,
        WIDTH,
        HEIGHT
    );

    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);

    if (InitTurtle(&turtle)) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    freqMultiplier = 1000.0 / SDL_GetPerformanceFrequency();

    SDL_SetRenderTarget(renderer, canvas);
    ClearGraphics(renderer);

    Draw();

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

int InitTurtle(turtle_t *turtle) {

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

void ResetTurtle(turtle_t *turtle) {
    turtle->x = INIT_TURTLE_X;
    turtle->y = INIT_TURTLE_Y;
    turtle->angle = 0;
    turtle->rotation = 0;
}

void ClearGraphics(SDL_Renderer *renderer) {

    /* Reset background colour to white */
    bgClr = (colour_t) {255, 255, 255};
    SDL_SetRenderDrawColor(renderer, 0, bgClr.g, bgClr.b, SDL_ALPHA_OPAQUE);

    /* Clear the background */
    SDL_SetRenderTarget(renderer, background);
    SDL_RenderClear(renderer);

    /* Clear the canvas (transparent) */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, canvas);
    SDL_RenderClear(renderer);

    /* Restore the colour to the foreground colour */
    SDL_SetRenderDrawColor(renderer, fgClr.r, fgClr.g, fgClr.b, SDL_ALPHA_OPAQUE);

}

void Draw(void) {
    if (VSYNC_SHOULD_WAIT) {
        VSYNC_WAIT;
    }

    /* Set render target to the window. */
    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderClear(renderer);

    /* Draw the background, canvas and turtle. */
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, canvas, NULL, NULL);
    DrawTurtle(renderer, &turtle);

    SDL_RenderPresent(renderer);

    /* Restore the render target to the canvas. */
    SDL_SetRenderTarget(renderer, canvas);

    vsyncStartTime = SDL_GetPerformanceCounter();
}

void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle) {

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