#include "../inc/Header.h"

void handleButtonPress(SDL_Event* e, Mix_Music* music, SDL_Rect* startButtonRect, SDL_Rect* pauseButtonRect) {
    // Checking whether the mouse button event occurred
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        // get coordinates
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Create a rectangle at the click location
        SDL_Rect mouseRect = { x, y, 1, 1 };

        // Checking start button
        if (SDL_HasIntersection(&mouseRect, startButtonRect)) {
            // play music
            Mix_PlayMusic(music, -1);
        }

        // Checking pause button
        if (SDL_HasIntersection(&mouseRect, pauseButtonRect)) {
            // stop music
            Mix_PauseMusic();
        }
    }
}
