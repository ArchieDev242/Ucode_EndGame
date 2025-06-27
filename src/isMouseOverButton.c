#include "../inc/Header.h"

int isMouseOverButton(SDL_Event* e, Button* button){
    if (e->type == SDL_MOUSEBUTTONDOWN && button->status == 0)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };
        if (SDL_HasIntersection(&mouseRect, &button->rect))
        {
            button->status = 1;
            button->timerID = SDL_AddTimer(100, timerCallbackButtonMouse, &button->status);
        }
    }
    return button->status;
}

int isMouseOverRect(SDL_Event* e, SDL_Rect* rect) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };
        if (SDL_HasIntersection(&mouseRect, rect)) {
            return 1;
        }
    }
    return 0;
}


Uint32 timerCallbackButtonMouse(Uint32 interval, void *param) {
    int* status = (int*)param;
    *status = 0;
    return 0;
}
