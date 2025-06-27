#include "../inc/Header.h"


SoundEffect* loadSoundEffect(const char* filePath, int volume) {
    SoundEffect* effect = (SoundEffect*)malloc(sizeof(SoundEffect));
    effect->sound = Mix_LoadWAV(filePath);
    if (!effect->sound) {
        printf("Error load sound: %s\n", Mix_GetError());
        free(effect);
        return NULL;
    }
    Mix_VolumeChunk(effect->sound, volume);
    effect->channel = -1;
    return effect;
}

void playSoundEffect(SoundEffect* effect) {
    if (effect->channel != -1 && Mix_Playing(effect->channel)) {
        Mix_HaltChannel(effect->channel);
    }
    effect->channel = Mix_PlayChannel(-1, effect->sound, 0);
    if (effect->channel == -1) {
        printf("Failed to play sound: %s\n", Mix_GetError());
    }
}

void stopSoundEffect(SoundEffect* effect) {
    if (effect != NULL && effect->channel != -1) {
        Mix_HaltChannel(effect->channel);
        effect->channel = -1;
    }
}

void freeSoundEffect(SoundEffect* effect) {
    Mix_FreeChunk(effect->sound);
    free(effect);
}
