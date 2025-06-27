#include "../inc/Header.h"
void drawCollision(SDL_Renderer* renderer, SDL_Rect* collisionRect, int color) {
    // Сохраняем текущий цвет рендера
    SDL_Color originalColor;
    SDL_GetRenderDrawColor(renderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

    // Устанавливаем цвет рендера в красный
    if (color == 1)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Рисуем прямоугольник коллизии с учетом размеров и координат
    SDL_RenderDrawRect(renderer, collisionRect);

    // Восстанавливаем оригинальный цвет рендера
    SDL_SetRenderDrawColor(renderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);
}
