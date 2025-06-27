#include "../inc/Header.h"

void inversionColor(SDL_Renderer* renderer, SDL_Texture* texture, int screenWidth, int screenHeight, int intensity, Uint8 alpha, SDL_Rect rect) {
    Uint32 format;
    int width, height;
    SDL_QueryTexture(texture, &format, NULL, &width, &height);

    Uint32* pixels = (Uint32*)malloc(width * height * sizeof(Uint32));

    SDL_Texture* glitchTextures[3];
    for (int i = 0; i < 3; i++) {
        glitchTextures[i] = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, width, height);
    }

    SDL_PixelFormat* pixelFormat = SDL_AllocFormat(format);

    Uint8 colors[3][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

    for (int i = 0; i < 3; i++) {
        SDL_SetRenderTarget(renderer, glitchTextures[i]);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderReadPixels(renderer, NULL, format, pixels, width * sizeof(Uint32));

        int xOffset = xorshift() % (2 * intensity + 1) - intensity;

        for (int j = 0; j < width * height; ++j) {
            Uint8 pixelR, pixelG, pixelB, pixelA;
            SDL_GetRGBA(pixels[j], pixelFormat, &pixelB, &pixelG, &pixelR , &pixelA);
            pixels[j] = SDL_MapRGBA(pixelFormat, pixelB * colors[i][2], pixelG * colors[i][1], pixelR * colors[i][0] , pixelA);
        }

        SDL_UpdateTexture(glitchTextures[i], NULL, pixels, width * sizeof(Uint32));
        SDL_SetTextureAlphaMod(glitchTextures[i], alpha);
        SDL_SetTextureBlendMode(glitchTextures[i], SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(renderer, NULL);

        rect.x += xOffset;
        rect.w = screenWidth;
        rect.h = screenHeight;

        SDL_RenderCopy(renderer, glitchTextures[i], NULL, &rect);
        SDL_DestroyTexture(glitchTextures[i]);
    }

    SDL_FreeFormat(pixelFormat);
    free(pixels);
}
