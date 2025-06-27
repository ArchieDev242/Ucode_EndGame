#include "../inc/Header.h"

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "error initialization SDL: %s\n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG; // format pic

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fprintf(stderr, "error initialization SDL_Image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    return 0;
}
