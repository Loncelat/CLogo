#include "graphics.h"

turtle_t _turtle;

colour_t bgClr = {0, 255, 255};
colour_t fgClr = {0, 0, 0};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *background = NULL;
SDL_Texture *canvas = NULL;

SDL_Event event;

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

    if (InitTurtle(&_turtle)) {
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

    turtle->texture = LoadImage("graphics/turtle.png");

    if (turtle->texture == NULL) {
        return 1;
    }

    SDL_SetTextureBlendMode(turtle->texture, SDL_BLENDMODE_BLEND);
    if (SDL_QueryTexture(turtle->texture, NULL, NULL, &turtle->w, &turtle->h) != 0) {
        return 1;
    }

    turtle->w /= TURTLE_DIRECTIONS;

    ResetTurtle(turtle);

    turtle->dstrect = (SDL_Rect) {turtle->x - turtle->w / 2.0, turtle->y - turtle->h, turtle->w, turtle->h};

    return 0;
}

void ResetTurtle(turtle_t *turtle) {
    turtle->x = INIT_TURTLE_X;
    turtle->y = INIT_TURTLE_Y;
    turtle->angle = M_PI / 2.0;
    turtle->rotation = 0;
    turtle->pd = 1;
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

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shutdownRequested = 1;
        }
    }

    if (VSYNC_SHOULD_WAIT) {
        VSYNC_WAIT;
    }

    /* Set render target to the window. */
    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderClear(renderer);

    /* Draw the background, canvas and turtle. */
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, canvas, NULL, NULL);
    DrawTurtle(renderer, &_turtle);

    SDL_RenderPresent(renderer);

    /* Restore the render target to the canvas. */
    SDL_SetRenderTarget(renderer, canvas);

    vsyncStartTime = SDL_GetPerformanceCounter();
}

void DrawTurtle(SDL_Renderer *renderer, turtle_t *turtle) {

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

    SDL_RenderDrawLine(renderer, oldX, oldY, (int) _turtle.x, (int) _turtle.y);
}

void RotateTurtle(double angle) {
    _turtle.angle += angle * (M_PI / 180.0);
    _turtle.angle = fmod(_turtle.angle, 2 * M_PI);
}

