#include "../inc/Header.h"
void checkCollisionAndMoveSprite(SDL_Rect* cameraPOS, SDL_Rect* spriteRect, SDL_Rect* collisionRectSprite, 
                SDL_Rect* collisionRect, const Uint8* keyboardState, int* FPS, int* speed, int x, int y) {
    SDL_PumpEvents();

    // Условные границы
    float one_five = windowWidth / 4;

    if (!(keyboardState[SDL_SCANCODE_A] && keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_LEFT] && keyboardState[SDL_SCANCODE_RIGHT] ||
        keyboardState[SDL_SCANCODE_D] && keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A] && keyboardState[SDL_SCANCODE_RIGHT])) {

        if (collisionRectSprite->x + collisionRectSprite->w > windowWidth - one_five - *speed * 3 / *FPS &&
            collisionRectSprite->x + collisionRectSprite->w < windowWidth - one_five + *speed * 3 / *FPS &&
            (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) && cameraPOS->x + *speed * 3 / *FPS <= 0) {
                cameraPOS->x += *speed / *FPS;
        }

        else if (collisionRectSprite->x > one_five - *speed * 3 / *FPS &&
            collisionRectSprite->x < one_five + *speed * 3 / *FPS &&
            (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) && cameraPOS->x - *speed * 3 / *FPS >= -1 * resizeObject * 1229) {
                cameraPOS->x -= *speed / *FPS;
        }

        else if (collisionRectSprite->x + collisionRectSprite->w < windowWidth - one_five && (nothingFrame == true || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) && cameraPOS->x + *speed * 3 / *FPS <= 0) {
            collisionRectSprite->x += *speed * 3 / *FPS;
            cameraPOS->x += *speed * 3 / *FPS;
            if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT])
                collisionRectSprite->x -= *speed / *FPS;
        }

        else if (collisionRectSprite->x > one_five && (nothingFrame == false || keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) && cameraPOS->x - *speed * 3 / *FPS >= -1 * resizeObject * 1229) {
            collisionRectSprite->x -= *speed * 3 / *FPS;
            cameraPOS->x -= *speed * 3 / *FPS;
            if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT])
                collisionRectSprite->x += *speed / *FPS;
        }

        else{
            if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) {
                collisionRectSprite->x += *speed / *FPS;
            }
            if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) {
                collisionRectSprite->x -= *speed / *FPS;
            }
        }
    }

    if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP]) {
        collisionRectSprite->y -= *speed / *FPS;
    }
    if (keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN]) {
        collisionRectSprite->y += *speed / *FPS;
    }

    // Проверяем, происходит ли коллизия
    if (collisionRectSprite->x < collisionRect->x + collisionRect->w &&
        collisionRectSprite->x + collisionRectSprite->w > collisionRect->x &&
        collisionRectSprite->y < collisionRect->y + collisionRect->h &&
        collisionRectSprite->y + collisionRectSprite->h > collisionRect->y) {

        // Определяем наименьшее перекрытие по каждой оси
        int overlapX = 0;
        int overlapY = 0;

        if (collisionRectSprite->x < collisionRect->x) {
            overlapX = collisionRectSprite->x + collisionRectSprite->w - collisionRect->x;
        } else {
            overlapX = collisionRect->x + collisionRect->w - collisionRectSprite->x;
        }

        if (collisionRectSprite->y < collisionRect->y) {
            overlapY = collisionRectSprite->y + collisionRectSprite->h - collisionRect->y;
        } else {
            overlapY = collisionRect->y + collisionRect->h - collisionRectSprite->y;
        }

        // Корректируем позицию спрайта в зависимости от наименьшего перекрытия
        if (overlapX < overlapY) {
            if (collisionRectSprite->x < collisionRect->x) {
                collisionRectSprite->x -= overlapX;
            } else {
                collisionRectSprite->x += overlapX;
            }
        } else {
            if (collisionRectSprite->y < collisionRect->y) {
                collisionRectSprite->y -= overlapY;
            } else {
                collisionRectSprite->y += overlapY;
            }
        }
    }
    // Устанавливаем новые координаты спрайта с учетом оригинальных координат
    spriteRect->x = collisionRectSprite->x - x;
    spriteRect->y = collisionRectSprite->y - y;
}
