#include "../inc/Header.h"

int windowScreen(SDL_Window** window, int* windowWidth, int* windowHeight) {
    *window = SDL_CreateWindow("LOOP PLACE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *windowWidth, *windowHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!(*window)) {
        fprintf(stderr, "error create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* icon = IMG_Load("../gameSDL/resources/icon/icon.png");

    if (!icon) {
        printf("Unable to load image! icon Error: %s\n", IMG_GetError());
    } else {
        // Установка иконки для окна
        SDL_SetWindowIcon(*window, icon);

        // Освобождение surface после установки иконки
        SDL_FreeSurface(icon);
    }

    SDL_GetWindowSize(*window, windowWidth, windowHeight);
    return 0;
}
