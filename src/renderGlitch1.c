#include "../inc/Header.h"

// hyeta polnaya
void renderGlitch1(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect Rect, int intensity) {
    // Получаем ширину и высоту текстуры
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Создаем массивы для хранения смещений по x и y для каждого канала цвета
    int xOffsets[3];
    // Генерируем случайные смещения в диапазоне от -10 до 10 пикселей
    for (int i = 0; i < 3; i++) {
        xOffsets[i] = xorshift() % (2 * intensity + 1) - intensity;
    }

    // Применяем глитч-эффект к каждому каналу цвета
    for (int i = 0; i < 3; i++) {
        // Выбираем цвет канала
        Uint32 color;
        switch (i) {
            case 0: color = 0xFF0000FF; break; // Красный
            case 1: color = 0x00FF00FF; break; // Зеленый
            case 2: color = 0x0000FFFF; break; // Синий
        }

        // Создаем поверхность для хранения канала цвета
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        if (surface == NULL) {
            printf("Unable to create surface! SDL Error: %s\n", SDL_GetError());
            return;
        }

        // Заполняем поверхность цветом
        SDL_FillRect(surface, NULL, color);

        // Создаем текстуру из поверхности
        SDL_Texture* channel = SDL_CreateTextureFromSurface(renderer, surface);
        if (channel == NULL) {
            printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
            return;
        }

        // Освобождаем поверхность
        SDL_FreeSurface(surface);

        // Устанавливаем режим наложения для текстуры
        SDL_SetTextureBlendMode(channel, SDL_BLENDMODE_MOD);

        // Создаем прямоугольник для отрисовки текстуры с учетом смещения
        SDL_Rect channelRect;
        channelRect.x = Rect.x + xOffsets[i];
        channelRect.y = Rect.y;
        channelRect.w = Rect.w;
        channelRect.h = Rect.h;

        // Копируем текстуру на рендерер поверх исходной текстуры
        SDL_RenderCopy(renderer, channel, NULL, &channelRect);

        // Уничтожаем текстуру
        SDL_DestroyTexture(channel);
    }
}

