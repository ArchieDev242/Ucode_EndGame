#include "../inc/Header.h"
int checkTriggerCollision(SDL_Rect* collisionRectSprite, SDL_Rect* collisionRect) {
    // Проверяем, происходит ли коллизия
    if (collisionRectSprite->x < collisionRect->x + collisionRect->w &&
        collisionRectSprite->x + collisionRectSprite->w > collisionRect->x &&
        collisionRectSprite->y < collisionRect->y + collisionRect->h &&
        collisionRectSprite->y + collisionRectSprite->h > collisionRect->y) {
        return 1;
    }
    else {
        return 0;
    }
}
