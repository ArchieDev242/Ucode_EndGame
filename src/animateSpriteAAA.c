#include "../inc/Header.h"
void animateSpriteAAA(SDL_Texture** spriteAnimation, int numSpriteFrames,
                      int frameRate, int time, SDL_Texture** currentTexture,
                      Uint32* startTime, int* currentFrame) {
    Uint32 endTime = SDL_GetTicks();
    if (endTime - *startTime >= time / frameRate) {
        *currentTexture = spriteAnimation[*currentFrame % numSpriteFrames];
        *currentFrame = (*currentFrame + 1) % numSpriteFrames;
        *startTime = endTime;
    }
}

void reverseAnimateSpriteAAA(SDL_Texture** spriteAnimation, int numSpriteFrames,
                      int frameRate, int time, SDL_Texture** currentTexture,
                      Uint32* startTime, int* currentFrame) {
    SDL_PumpEvents();
    Uint32 endTime = SDL_GetTicks();
    if (endTime - *startTime >= time / frameRate) {
        *currentFrame = (*currentFrame - 1 + numSpriteFrames) % numSpriteFrames;
        *currentTexture = spriteAnimation[*currentFrame];
        *startTime = endTime;
    }
}
