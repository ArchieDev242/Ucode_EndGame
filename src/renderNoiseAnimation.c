#include "../inc/Header.h"
void renderNoiseAnimation(SDL_Renderer* renderer, SDL_Texture** spriteAnimation, 
int numSpriteFrames, int frameRate,SDL_Texture** vignetteTexture, 
Uint32* startTime, int* currentFrame, int* windowWidth, int* windowHeight, Uint8 alpha)
{
    Uint32 endTime = SDL_GetTicks();
    if(endTime - *startTime >= 1000 / frameRate)
    {
        // Update the vignette texture for the next animation frame
        *vignetteTexture = spriteAnimation[*currentFrame % numSpriteFrames];
        *currentFrame = (*currentFrame + 1) % numSpriteFrames;
        *startTime = endTime;
    }
    // Set the texture's alpha
    SDL_SetTextureBlendMode(*vignetteTexture,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(*vignetteTexture, alpha);
    // Display the vignette on the screen
    SDL_Rect vignetteRect = {0, 0, *windowWidth, *windowHeight};
    SDL_RenderCopy(renderer, *vignetteTexture, NULL, &vignetteRect);
}
