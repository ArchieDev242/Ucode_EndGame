#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL_thread.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

// start game
int quit;
extern float resizeObject;
//game stage
enum GameState {
    MENU,
    GAME,
    GAME_WAIT,
    GAME_LIFT
};
enum GameState currentState;
/*
1 = door
2 = vedro kapayet
3 = window
4 = rubishbin
5 = ognik
*/
// obj status
int ObjStatus[5];
int ObjFrame[5];

SDL_Texture* door1Texture;

//button 
typedef struct Button {
    SDL_Rect rect;
    SDL_Texture* texture;
    int status;
    SDL_TimerID timerID;
} Button;

//stucture for music
typedef struct {
    Mix_Chunk* sound;
    int channel;
} SoundEffect;

// structure FPS
typedef struct {
    int FPS;                
    char fps_text[32];      
    Uint32 frameStart;      // start FPS
    int frameTime;          // frameTime FPS
    int frameCount;         // count FPS
    int lastFrame;          // last FPS
} FPSCounter;
FPSCounter fpsCounter;

//flags for music mute or not
int soundEnabled;

// play or not
bool isMusicPlaying;
bool triggerState;

//music
SoundEffect* effect;
SoundEffect* run;
SoundEffect* backgroundMusic;
SoundEffect* hoverSound;
SoundEffect* buttonPressed;
int volumeMusic;
char VolumeText[32];
char AnomalyText[32];
char LiftText[32];
SDL_TimerID volumeTimerID;

//size window and settings
int windowWidth;
int windowHeight;
SDL_Renderer* renderer;
SDL_Window* window;

SDL_Color textColor;

int SPEED;//speed hero

// possition hero
int x;
int y;

// collision legs interva
int collisionIntervalX;
int collisionIntervalY;

//time for animation
SDL_TimerID timerID;
SDL_TimerID timerID1;
SDL_TimerID timerID2;

//for button
bool isHovered;

// timer status
bool timer1Active;
bool timer2Active;

//start texture
SDL_Texture* currentTexture ;
SDL_Texture* vignetteTexture; // vignette
SDL_Texture* textTexture ;

//frames for animation sprite and Vignett
int currentFrame ;
int currentFrameVignett;

//flags
bool nothingFrame ;
bool effectActive ;


Uint32 effectStartTime; // flag for effect

char countText[32];

Button sizeButtonPause;  
Button sizeButtonStart;   
Button sizeButtonPlay;    
Button sizeButtonOptions;  
Button sizeButtonExit;    
Button sizeButtonExit2;  
Button sizeTest;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
TTF_Font* loadFont(const char* fontPath, int fontSize);
int init(void);
void renderText(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture** textTexture, const char* text, int x, int y, SDL_Color textColor);
void renderTextSize(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture** textTexture, const char* text, int x, int y, SDL_Color textColor, float scale);
int windowScreen(SDL_Window** window, int* windowWidth, int* windowHeight);
void drawCollision(SDL_Renderer* renderer, SDL_Rect* collisionRect, int color);
void animateSpriteAAA(SDL_Texture** spriteAnimation, int numSpriteFrames,
int frameRate, int time,SDL_Texture** currentTexture, Uint32* startTime,int* currentFrame);
void reverseAnimateSpriteAAA(SDL_Texture** spriteAnimation, int numSpriteFrames,
int frameRate, int time,SDL_Texture** currentTexture, Uint32* startTime,int* currentFrame);
void vignetteFilterAnimation(SDL_Renderer* renderer, SDL_Texture** spriteAnimation, int numSpriteFrames, int frameRate, int* quit, SDL_Texture** vignetteTexture, Uint32* startTime, int* currentFrame, int* windowWidth, int* windowHeight);
int checkTriggerCollision(SDL_Rect* collisionRectSprite, SDL_Rect* collisionRect);
void checkCollisionAndMoveSprite(SDL_Rect* cameraPOS, SDL_Rect* spriteRect, SDL_Rect* collisionRectSprite, 
                SDL_Rect* collisionRect, const Uint8* keyboardState, int* FPS, int* speed, int x, int y);
SDL_Texture** loadFrames(SDL_Renderer* renderer, const char* folderPath, int numFrames);
void handleButtonPress(SDL_Event* e, Mix_Music* music, SDL_Rect* startButtonRect, SDL_Rect* pauseButtonRect);
int isMouseOverButton(SDL_Event* e, Button* button);
int isMouseOverRect(SDL_Event* e, SDL_Rect* rect);
Uint8 xorshift(void);
void renderGlitch(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, int intensity);
void renderGlitch1(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect Rect, int intensity);
void renderColorChannelGlitch(SDL_Renderer* renderer, SDL_Texture* texture, int screenWidth, int screenHeight, int intensity, Uint8 alpha, SDL_Rect rect);
void inversionColor(SDL_Renderer* renderer, SDL_Texture* texture, int screenWidth, int screenHeight, int intensity, Uint8 alpha, SDL_Rect rect);
void renderNoiseAnimation(SDL_Renderer* renderer, SDL_Texture** spriteAnimation, 
int numSpriteFrames, int frameRate,SDL_Texture** vignetteTexture, 
Uint32* startTime, int* currentFrame, int* windowWidth, int* windowHeight, Uint8 alpha);
Uint32* generateNoise(int screenWidth, int screenHeight, Uint8 alpha);
void renderNoise(SDL_Renderer* renderer, SDL_Texture* noiseTexture, int screenWidth, int screenHeight, Uint8 alpha);
SoundEffect* loadSoundEffect(const char* filePath, int volume);
void playSoundEffect(SoundEffect* effect);
void stopSoundEffect(SoundEffect* effect);
void freeSoundEffect(SoundEffect* effect);
Uint32 timerCallbackStateGame(Uint32 interval, void *param);
Uint32 timerCallbackStateGameWait(Uint32 interval, void *param);
Uint32 timerCallbackStateMenu(Uint32 interval, void *param);
Uint32 timerCallbackStateOption(Uint32 interval, void *param);
Uint32 timerCallbackButtonMouse(Uint32 interval, void *param);
Uint32 timerCallbackStateEffect(Uint32 interval, void *param);
Uint32 timerCallbackStateTrue(Uint32 interval, void *param);
Uint32 timerCallbackStateEffectMusic(Uint32 interval, void *param);
Uint32 timerCallbackStateEffectMusicTrue(Uint32 interval, void *param);
Uint32 volumeTimerCallback(Uint32 interval, void *param);
void animationButton(SDL_Renderer* renderer, SDL_Texture** spriteAnimation, 
int numSpriteFrames, int frameRate, int* quit, SDL_Texture** vignetteTexture, 
Uint32* startTime, int* currentFrame,SDL_Rect* vignetteRect);
