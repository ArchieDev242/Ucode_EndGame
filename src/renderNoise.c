#include "../inc/Header.h"
Uint32* generateNoise(int screenWidth, int screenHeight, Uint8 alpha) {

    Uint32* pixels = (Uint32*)malloc(screenWidth * screenHeight * sizeof(Uint32));

    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    for (int i = 0; i < screenWidth * screenHeight; ++i) {
        Uint8 randomValue = xorshift();
        pixels[i] = SDL_MapRGBA(format, randomValue, randomValue, randomValue, alpha);
    }

    SDL_FreeFormat(format);

    return pixels;
}

void renderNoise(SDL_Renderer* renderer, SDL_Texture* noiseTexture, int screenWidth, int screenHeight, Uint8 alpha) {
    SDL_SetTextureBlendMode(noiseTexture, SDL_BLENDMODE_BLEND);

        // Генерируем шум
        Uint32* pixels = generateNoise(screenWidth, screenHeight, alpha);

        // Обновляем текстуру шума
        SDL_UpdateTexture(noiseTexture, NULL, pixels, screenWidth * sizeof(Uint32));

        // Рендерим текстуру шума
        SDL_RenderCopy(renderer, noiseTexture, NULL, NULL);

        // Освобождаем память
        free(pixels);
}
