#include "../inc/Header.h"

TTF_Font* loadFont(const char* fontPath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (font == NULL) {
        fprintf(stderr, "error load font: %s\n", TTF_GetError());
    }


    return font;
}
