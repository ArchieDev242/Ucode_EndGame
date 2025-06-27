#include "../inc/Header.h"

void renderGlitch(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, int intensity) {
    // Получаем ширину и высоту текстуры
    int width ,height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Создаем прямоугольник для отрисовки каждой строки текстуры
    SDL_Rect srcRect, dstRect;
    srcRect.x = 0;
    srcRect.w = width;
    dstRect.w = rect.w; // Используем ширину из rect
    dstRect.h = rect.h / height; // Используем высоту из rect, деленную на количество строк

    for (int y = 0; y < height; ++y) {
        // Генерируем случайное смещение в диапазоне от -intensity до intensity пикселей
        int xOffset = xorshift() % (2 * intensity + 1) - intensity;
        srcRect.y = y;
        srcRect.h = 1; // Высота исходной строки всегда 1
        dstRect.x = rect.x + xOffset; // Используем x-координату из rect
        dstRect.y = rect.y + y * dstRect.h; // Используем y-координату из rect, умноженную на высоту строки

        // Копируем строку текстуры на рендерер с учетом смещения
        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    }
}

