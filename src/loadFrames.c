#include "../inc/Header.h"

SDL_Texture** loadFrames(SDL_Renderer* renderer, const char* folderPath, int numFrames) {
    SDL_Texture** frames = (SDL_Texture**)malloc(numFrames * sizeof(SDL_Texture*));
    char filePath[256]; // path on file
    for (int i = 0; i < numFrames; ++i) {
        snprintf(filePath, sizeof(filePath), "%sframe_%d.png", folderPath, i + 1); // changing path file
        frames[i] = loadTexture(renderer, filePath);// load texture
    }
    return frames; // return new frame
}
