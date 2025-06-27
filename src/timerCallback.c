#include "../inc/Header.h"

Uint32 timerCallbackStateGame(Uint32 interval, void *param) {
    *(enum GameState*)param = GAME;
    return 0;
}

Uint32 timerCallbackStateGameWait(Uint32 interval, void *param) {
    *(enum GameState*)param = GAME_WAIT;
    return 0;
}

Uint32 timerCallbackStateMenu(Uint32 interval, void *param) {
    *(enum GameState*)param = MENU;
    return 0;
}

Uint32 timerCallbackStateEffectMusic(Uint32 interval, void *param) {
    isMusicPlaying = false;
    stopSoundEffect(effect);
    return 0;
}

Uint32 timerCallbackStateEffectMusicTrue(Uint32 interval, void *param) {
    timer2Active = true;
    isMusicPlaying = true;
    if (soundEnabled) {
        playSoundEffect(effect);
    }
    return 0;
}

Uint32 timerCallbackStateEffect(Uint32 interval, void *param) {
    effectActive = false;
    return 0;
}

Uint32 timerCallbackStateTrue(Uint32 interval, void *param) {
    timer1Active = true;
    effectActive = true;
    return 0;
}

Uint32 volumeTimerCallback(Uint32 interval, void *param) {
    volumeTimerID = 0;
    return 0;
}
