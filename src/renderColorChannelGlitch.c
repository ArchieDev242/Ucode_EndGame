#include "../inc/Header.h"

void renderColorChannelGlitch(SDL_Renderer* renderer, SDL_Texture* texture, int screenWidth, int screenHeight, int intensity, Uint8 alpha, SDL_Rect rect) {
    // Получаем формат и размеры текстуры
    Uint32 format;
    int width, height;
    SDL_QueryTexture(texture, &format, NULL, &width, &height);

    // Создаем новые текстуры для глитч-эффекта
    SDL_Texture* glitchTextures[3];
    for (int i = 0; i < 3; i++) {
        glitchTextures[i] = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight);
    }

    // Выделяем формат заранее
    SDL_PixelFormat* pixelFormat = SDL_AllocFormat(format);

    // Проходим по всем каналам цвета
    for (int i = 0; i < 3; i++) {
        // Устанавливаем эту текстуру как цель для рендеринга
        SDL_SetRenderTarget(renderer, glitchTextures[i]);

        // Рендерим исходную текстуру
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // Генерируем случайное смещение по оси X с учетом интенсивности
        int xOffset = xorshift() % (2 * intensity + 1) - intensity;

        // Устанавливаем модификатор цвета для текстуры
        SDL_SetTextureColorMod(glitchTextures[i], i == 0 ? 255 : 0, i == 1 ? 255 : 0, i == 2 ? 255 : 0);

        // Устанавливаем уровень прозрачности для текстуры
        SDL_SetTextureAlphaMod(glitchTextures[i], alpha);

        // Устанавливаем режим наложения для текстуры
        SDL_SetTextureBlendMode(glitchTextures[i], SDL_BLENDMODE_BLEND);

        // Возвращаем цель рендеринга обратно на экран
        SDL_SetRenderTarget(renderer, NULL);

        // Создаем прямоугольник для отрисовки текстуры с учетом смещения по оси X
        rect.x += xOffset;
        rect.w = screenWidth;
        rect.h = screenHeight;

        // Рендерим текстуру глитч-эффекта
        SDL_RenderCopy(renderer, glitchTextures[i], NULL, &rect);

        // Освобождаем ресурсы
        SDL_DestroyTexture(glitchTextures[i]);
    }

    // Освобождаем формат
    SDL_FreeFormat(pixelFormat);
}
