#include "../inc/Header.h"

void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture** textTexture, const char* text, int x, int y, SDL_Color textColor) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface) {
        fprintf(stderr, "Error creating text surface: %s\n", TTF_GetError());
        return;
    }

    if (*textTexture) {
        SDL_DestroyTexture(*textTexture);
    }

    *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!*textTexture) {
        fprintf(stderr, "Error creating texture from text surface: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect destRect = { x, y, textSurface->w, textSurface->h };

    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, *textTexture, NULL, &destRect);
}

void renderTextSize(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture** textTexture, const char* text, int x, int y, SDL_Color textColor, float scale) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface) {
        fprintf(stderr, "Error creating text surface: %s\n", TTF_GetError());
        return;
    }

    if (*textTexture) {
        SDL_DestroyTexture(*textTexture);
    }

    *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!*textTexture) {
        fprintf(stderr, "Error creating texture from text surface: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    int scaledWidth = textSurface->w * scale;
    int scaledHeight = textSurface->h * scale;

    int adjustedX = x - scaledWidth / 2;
    int adjustedY = y - scaledHeight / 2;

    SDL_Rect destRect = { adjustedX, adjustedY, scaledWidth, scaledHeight };

    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, *textTexture, NULL, &destRect);
}

