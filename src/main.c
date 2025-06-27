#include "../inc/Header.h"

void deleteTrash(SDL_Renderer* renderer, SDL_Window* window);
SDL_DisplayMode DM;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

SDL_Color textColor = {255, 255, 255};
SDL_Color textColorGame = {0, 0, 0};
SDL_Color textColorAnomiles = {0, 255, 0};
int SPEED = 380;//speed hero 375

float resizeObject;

#define MAX_ANOMALIES 30

typedef struct {
    char* name;
} Anomaly;

Anomaly anomalies[MAX_ANOMALIES];
int anomalyCount = 0; 

int countLift = 0;

int main(int argc, char* argv[]) {
/*
1 = door
2 = vedro kapayet
3 = windowes
4 = rubishbin
5 = ognik
6 = transition
7 = locker1
8 = locker2
9 = locker3
10 = locker4
11 = locker5
12 = locker6
13 = locker7
14 = locker8
15 = locker9
16 = rubishbin2
17 = tablichka1
18 = tablichka2
19 = windows2
21 = windows3
22 = Lift
*/
    // array objects    // array objects
    int randomStatus[22] = {0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0, 0};
    int ObjStatus[22] = {0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0, 0};
    int ObjFrame[22]  = {0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0, 0};

    srand(time(0));

    int numberOfTwos = rand() % (3 + 1);
    // Заполняем массив случайным образом
    for (int i = 0; i < 18; i++) {
        if (numberOfTwos > 0 && rand() % 2 == 0) {
            randomStatus[i] = 3; // С вероятностью 50% устанавливаем значение 2
            numberOfTwos--;
        } else {
            randomStatus[i] = 1; // В остальных случаях устанавливаем значение 1
        }
    }

    randomStatus[8] = 3;
    fpsCounter.FPS = 61;
    init();

    windowScreen(&window, &windowWidth, &windowHeight);
    SDL_GetCurrentDisplayMode(0, &DM);

    //size window and settings
    int windowWidth = DM.w;
    int windowHeight = DM.h;

    printf("%d", windowHeight);
    resizeObject = windowHeight / 150;

    // possition hero
    int x = 13 * resizeObject; // 60
    int y = 123 * resizeObject; // 590
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        fprintf(stderr, "error create render: %s\n", SDL_GetError());
        deleteTrash(renderer, window);
        return 1;
    }

    enum GameState currentState = MENU;

    if (TTF_Init() == -1) {
        fprintf(stderr, "error: SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }


    volumeMusic = 7;
    SDL_Texture* volumeTextTexture = NULL;
    SDL_Texture* TextTextureLift = NULL;
    SDL_Texture* TextTextureLift123 = NULL;

    backgroundMusic = loadSoundEffect("../gameSDL/resources/songs/menu.wav", volumeMusic * 10);
    run = loadSoundEffect("../gameSDL/resources/songs/run1.wav", volumeMusic * 10);

    hoverSound = loadSoundEffect("../gameSDL/resources/songs/buttonSound/aimedButton.wav",90);
    buttonPressed = loadSoundEffect("../gameSDL/resources/songs/buttonSound/buttonPressed.wav",100);

    if (!hoverSound) {
        printf("Failed to load hover sound: %s\n", Mix_GetError());
    }

    if (!buttonPressed) {
        printf("Failed to load pressed sound: %s\n", Mix_GetError());
    }

    TTF_Font* font = loadFont("../gameSDL/resources/font/text2.ttf", 30);

    TTF_Font* musicTextVolume = loadFont("../gameSDL/resources/font/text2.ttf", 20);

    TTF_Font* countFont = loadFont("../gameSDL/resources/font/text2.ttf", 25);

    TTF_Font* countLiftFont = loadFont("../gameSDL/resources/font/text2.ttf", 55);
    // dynamic textures
    const int numVignetteFrames = 25; // vignette filter frames
    SDL_Texture** vignetteFilter = loadFrames(renderer, "../gameSDL/resources/png/VignettFilter/", numVignetteFrames);
    SDL_Texture* vignetteTexture = NULL; // vignette

    const int numNoise = 12; // noise filter frames
    SDL_Texture** noise = loadFrames(renderer, "../gameSDL/resources/png/Noise/", numNoise);

    const int numLeftFrames = 4;
    SDL_Texture** leftSpriteFrames = loadFrames(renderer, "../gameSDL/resources/png/LeftFrames/", numLeftFrames);

    const int numRightFrames = 4;
    SDL_Texture** rightSpriteFrames = loadFrames(renderer, "../gameSDL/resources/png/RightFremes/", numRightFrames);

    const int numNothingFrames = 1;
    SDL_Texture** nothingFrames = loadFrames(renderer, "../gameSDL/resources/png/NothingFrames/", numNothingFrames);

    const int numNothingFramesReverse = 1;
    SDL_Texture** nothingFramesReverse = loadFrames(renderer, "../gameSDL/resources/png/NothingFramesReverse/", numNothingFrames);

    const int numDoorFrames = 3;
    SDL_Texture** doorAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/door/", numDoorFrames);
    SDL_Texture* door1Texture = NULL;

    const int numBucketFrames = 27;
    SDL_Texture** BucketAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/bucket/", numBucketFrames);
    SDL_Texture* BucketTexture1 = NULL;

    const int numElevatorFrames = 9;
    SDL_Texture** ElevatorAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/elevator/", numElevatorFrames);
    SDL_Texture* ElevatorTexture = NULL;

    const int numLockerFrames = 3;
    SDL_Texture** LockerAnimFrames1 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker1/", numLockerFrames);
    SDL_Texture** LockerAnimFrames2 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker2/", numLockerFrames);
    SDL_Texture** LockerAnimFrames3 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker3/", numLockerFrames);
    SDL_Texture** LockerAnimFrames4 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker4/", numLockerFrames);
    SDL_Texture** LockerAnimFrames5 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker5/", numLockerFrames);
    SDL_Texture** LockerAnimFrames6 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker6/", numLockerFrames);
    SDL_Texture** LockerAnimFrames7 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker7/", numLockerFrames);
    SDL_Texture** LockerAnimFrames8 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker8/", numLockerFrames);
    SDL_Texture** LockerAnimFrames9 = loadFrames(renderer, "../gameSDL/resources/png/scene/locker9/", numLockerFrames);
    SDL_Texture* LockerTexture1 = NULL;
    SDL_Texture* LockerTexture2 = NULL;
    SDL_Texture* LockerTexture3 = NULL;
    SDL_Texture* LockerTexture4 = NULL;
    SDL_Texture* LockerTexture5 = NULL;
    SDL_Texture* LockerTexture6 = NULL;
    SDL_Texture* LockerTexture7 = NULL;
    SDL_Texture* LockerTexture8 = NULL;
    SDL_Texture* LockerTexture9 = NULL;


    const int numOgnetushitelFrames = 6;
    SDL_Texture** OgnetushitelAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/ognetushitel/", numOgnetushitelFrames);
    SDL_Texture* OgnetushitelTexture = NULL;

    const int numRubbishBinFrames = 5;
    SDL_Texture** RubbishBinAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/rubbishBin/", numRubbishBinFrames);
    SDL_Texture* RubbishBinTexture = NULL;
    SDL_Texture* RubbishBinTexture1 = NULL;

    const int numWindowFrames = 18;
    SDL_Texture** WindowAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/window/", numWindowFrames);
    SDL_Texture** Window_NormAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/scene/window_norm/", numWindowFrames);
    SDL_Texture* WindowAnimTexture = NULL;
    SDL_Texture* WindowAnimTexture1 = NULL;
    SDL_Texture* WindowAnimTexture2 = NULL;

    SDL_Texture* warning_Texture1  = NULL;
    SDL_Texture* warning_Texture2 = NULL;

    const int numTransitionFrames = 21;
    SDL_Texture** TransitionAnimFrames = loadFrames(renderer, "../gameSDL/resources/png/transition/", numTransitionFrames);
    SDL_Texture* TransitionAnimTexture = NULL;
    SDL_Texture* TransitionAnimTexture1 = NULL;

    //start texture
    SDL_Texture* currentTexture = NULL;
    SDL_Texture* currentTextureForTipochek = NULL;
    //SDL_Texture* noiseTexture = NULL; // noise
    SDL_Texture* textTexture = NULL;
    SDL_Texture* textTextureForInformation = NULL;
    SDL_Texture* countTexture = NULL;
    SDL_Texture* countAnomaly = NULL;
    //frames for animation sprite and Vignett
    int currentFrame = 0;
    int currentFrameTransition = 0;
    int currentFrameVignett = 0;
    int currentFrameStart = 0;
    SDL_Texture* noiseTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

    //flags
    nothingFrame = false;
    effectActive = false;
    Uint32 effectStartTime; // flag for effect

   // static textures
    SDL_Texture* backgroundMenuTexture        = loadTexture(renderer, "../gameSDL/resources/png/background_menu.png");

    SDL_Texture* TipochekRightTexture             = loadTexture(renderer, "../gameSDL/resources/png/test/tipochekRight.png");
    SDL_Texture* TipochekLeftTexture              = loadTexture(renderer, "../gameSDL/resources/png/test/tipochekLeft.png");

    SDL_Texture* playTexture                  = loadTexture(renderer, "../gameSDL/resources/button/start/play.png");

    SDL_Texture* quitButtonTexture            = loadTexture(renderer, "../gameSDL/resources/button/quit/exit.png");
    

    SDL_Texture* PlusMusicVolumeTexture       = loadTexture(renderer, "../gameSDL/resources/button/plus/plus.png");
    SDL_Texture* MinusMusicVolumeTexture      = loadTexture(renderer, "../gameSDL/resources/button/minus/minus.png");

    SDL_Texture* sceneTexture                                 = loadTexture(renderer, "../gameSDL/resources/png/scene/background.png");

    SDL_Texture* LiftWallTexture                              = loadTexture(renderer, "../gameSDL/resources/png/scene/brickwallLift.png");
    SDL_Texture* MainButtonLift                              = loadTexture(renderer, "../gameSDL/resources/png/scene/mainbtn.png");

    SDL_Texture* UpButtonLift                                = loadTexture(renderer, "../gameSDL/resources/png/LiftUp/frame_1.png");
    SDL_Texture* DownButtonLift                              = loadTexture(renderer, "../gameSDL/resources/png/LiftDown/frame_1.png");

    SDL_Texture* UpButtonLiftPressed                             = loadTexture(renderer, "../gameSDL/resources/png/LiftUp/frame_2.png");
    SDL_Texture* DownButtonLiftPressed                             = loadTexture(renderer, "../gameSDL/resources/png/LiftDown/frame_2.png");

    SDL_Texture* board_1Texture                               = loadTexture(renderer, "../gameSDL/resources/png/scene/board_1.png");
    SDL_Texture* backpackTexture                              = loadTexture(renderer, "../gameSDL/resources/png/scene/backpack.png");
    SDL_Texture* boardBigTexture                              = loadTexture(renderer, "../gameSDL/resources/png/scene/board_big_1.png");
    SDL_Texture* brickwallTexture                             = loadTexture(renderer, "../gameSDL/resources/png/scene/brickwall.png");
    SDL_Texture* bucketAnomalyTexture                         = loadTexture(renderer, "../gameSDL/resources/png/scene/bucket_anomaly.png");
    SDL_Texture* bucketTexture                                = loadTexture(renderer, "../gameSDL/resources/png/scene/bucket.png");
    SDL_Texture* classnumber_1Texture                         = loadTexture(renderer, "../gameSDL/resources/png/scene/classnumber_1.png");
    SDL_Texture* classnumber_2Texture                         = loadTexture(renderer, "../gameSDL/resources/png/scene/classnumber_2.png");
    SDL_Texture* clocksTexture                                = loadTexture(renderer, "../gameSDL/resources/png/scene/clocks.png");
    SDL_Texture* crumpledpapersTexture                        = loadTexture(renderer, "../gameSDL/resources/png/scene/crumpledpapers.png");
    SDL_Texture* doorTexture                                  = loadTexture(renderer, "../gameSDL/resources/png/scene/door_class_1.png");
    SDL_Texture* firefighterTexture                           = loadTexture(renderer, "../gameSDL/resources/png/scene/firefighter.png");
    SDL_Texture* flowerTexture                                = loadTexture(renderer, "../gameSDL/resources/png/scene/flower.png");
    SDL_Texture* laddersTexture                               = loadTexture(renderer, "../gameSDL/resources/png/scene/ladders.png");

    SDL_Texture* lockers_mini_1Texture                        = loadTexture(renderer, "../gameSDL/resources/png/scene/lockers_mini_1.png");
    SDL_Texture* lockers_mini_3Texture                        = loadTexture(renderer, "../gameSDL/resources/png/scene/lockers_mini_3.png");
    SDL_Texture* pencilTexture                                = loadTexture(renderer, "../gameSDL/resources/png/scene/pencil.png");
    SDL_Texture* puddleTexture                                = loadTexture(renderer, "../gameSDL/resources/png/scene/puddle.png");
    SDL_Texture* stackofpapers_bigTexture                     = loadTexture(renderer, "../gameSDL/resources/png/scene/stackofpapers_big.png");
    SDL_Texture* stackofpapers_smallTexture                   = loadTexture(renderer, "../gameSDL/resources/png/scene/stackofpapers_small.png");
    SDL_Texture* swabTexture                                  = loadTexture(renderer, "../gameSDL/resources/png/scene/swab.png");
    SDL_Texture* tileTexture                                  = loadTexture(renderer, "../gameSDL/resources/png/scene/tile.png");
    SDL_Texture* toilet_female_anomalyTexture                 = loadTexture(renderer, "../gameSDL/resources/png/scene/toilet_female_anomaly.png");
    SDL_Texture* toilet_female_nomalyTexture                  = loadTexture(renderer, "../gameSDL/resources/png/scene/toilet_female_nomaly.png");
    SDL_Texture* toilet_male_anomalyTexture                   = loadTexture(renderer, "../gameSDL/resources/png/scene/toilet_male_anomaly.png");
    SDL_Texture* toilet_male_nomalyTexture                    = loadTexture(renderer, "../gameSDL/resources/png/scene/toilet_male_nomaly.png");
    SDL_Texture* toilet_perehodTexture                        = loadTexture(renderer, "../gameSDL/resources/png/scene/toilet_perehod.png");
    SDL_Texture* elevatorButtonTexture                        = loadTexture(renderer, "../gameSDL/resources/png/scene/elevator_btn2.png");
    SDL_Texture* checkerTexture                               = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
    SDL_Texture* checkerTexture1                              = loadTexture(renderer, "../gameSDL/resources/png/scene/firefighter_big.png");
    SDL_Texture* checkerTexture2                              = loadTexture(renderer, "../gameSDL/resources/png/scene/door/frame_3.png");

    SDL_Event e;
    Uint32 startTime, startTimeDoor,reverseStartTimeDoor,startbucketTime,startTimeWindow,reversestartTimeWindow,reversestartTimeWindow1,startTimeWindow1,
    reversestartTimeWindow2,startTimeWindow2,startBucketAnim,reversestartBucketAnim,startrubbishbinAnim,reversestartrubbishbinAnim,startrubbishbin1Anim,reversestartrubbishbin1Anim,
    startOgnetushitelAnim,startTransition,startTransitionEnd, reversestartOgnetushitelAnim, startLocker1Anim, reversestartLocker1Anim,
    startLocker2Anim, reversestartLocker2Anim,  startLocker3Anim, reversestartLocker3Anim,  startLocker4Anim, reversestartLocker4Anim,
      startLocker5Anim, reversestartLocker5Anim,
    startLocker6Anim, reversestartLocker6Anim,  startLocker7Anim, reversestartLocker7Anim, startLocker8Anim, reversestartLocker8Anim,
      startLocker9Anim, reversestartLocker9Anim,startTimeLift,reversestartTimeLift,
    startTimeVignett = SDL_GetTicks();

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    Uint64 start = SDL_GetPerformanceCounter();

    SDL_Rect cameraPOS              = { 0, 0, 0, 0 };

    Uint32 lastEffectTime = SDL_GetTicks() - 20000;

    quit = 0;

    soundEnabled = 0;

    playSoundEffect(backgroundMusic);

    isMusicPlaying = false;
    triggerState = false;

    timer1Active = false;
    timer2Active = false;

    int plusButtonPressed = 0;
    int minusButtonPressed = 0;
    int ObjectsButtonPressed = 0;
    SDL_Point mousePos;
    bool isHovered = false;

    bool isHoveredTest = false;

    SDL_Rect spriteRectCollision       = { x, y, 23 * resizeObject, 5 * resizeObject };
    Button ButtonMainLift              = { (windowWidth / 2) - 130, (windowHeight / 2) - 260 , 40 * resizeObject, 67 * resizeObject};
    Button ButtonUpLift                = { (windowWidth / 2) - 30, (windowHeight / 2) , (79 / resizeObject) * resizeObject, (73 / resizeObject) * resizeObject};
    Button ButtonDownLift              = { (windowWidth / 2) - 30, (windowHeight / 2) + 80 , (79 / resizeObject) * resizeObject, (73 / resizeObject) * resizeObject};
    while (!quit) {

        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        // collision legs interval
        int collisionIntervalX = 6 * resizeObject;
        int collisionIntervalY = 63 * resizeObject;

        SDL_Rect spriteRect      = {x + collisionIntervalX, y + collisionIntervalY, 40 * resizeObject, 70 * resizeObject };

        Button playButton        = { { (windowWidth  / 2) - 60, (windowHeight / 2) + 30, 170, 50 }, playTexture, 0, 0 };
        Button QuitButton        = { { windowWidth - 170, windowHeight - 90, 150, 50 }, quitButtonTexture,0, 0 };

        Button PlusMusicVolume   = { { windowWidth / 2 + 125, windowHeight / 2 + 85, 50, 45 }, PlusMusicVolumeTexture, 0, 0 };
        Button MinusMusicVolume  = { { windowWidth / 2 - 140, windowHeight / 2 + 85, 50, 45 }, MinusMusicVolumeTexture, 0, 0 };
        Button backpackButton    = { { 80 * resizeObject + cameraPOS.x, 20 * resizeObject , 25 * resizeObject, 24 * resizeObject}, backpackTexture,0,0 };

        SDL_Rect FlashlightRect            = {spriteRectCollision.x - resizeObject * 300, spriteRectCollision.y - resizeObject * 180, resizeObject * 700, resizeObject * 300 };

        SDL_Rect sceneRect                 = { 0  + cameraPOS.x, 0   + cameraPOS.y, 1500 * resizeObject, 150 * resizeObject};

        Button lockers_1Rect             = { 43 * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_2Rect             = { (43+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_3Rect             = { (43+22+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_4Rect             = { (43+22+22+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_5Rect             = { 687 * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_6Rect             = { (687+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_7Rect             = { (687+22+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_8Rect             = { 817 * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        Button lockers_9Rect             = { (817+22) * resizeObject + cameraPOS.x, 38 * resizeObject + cameraPOS.y, 36 * resizeObject, 94 * resizeObject};
        
        Button flowerRect                = { 154 * resizeObject + cameraPOS.x, 83 * resizeObject + cameraPOS.y, 23 * resizeObject, 43 * resizeObject};
        Button board_1Rect               = { 139 * resizeObject + cameraPOS.x, 42 * resizeObject + cameraPOS.y, 51 * resizeObject, 32 * resizeObject};
        Button backpackRect              = { 80 * resizeObject + cameraPOS.x, 20 * resizeObject  + cameraPOS.y, 25 * resizeObject, 24 * resizeObject};
        Button door1Rect                 = { 193 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button windowsRect               = { 194 * resizeObject + cameraPOS.x, 15 * resizeObject + cameraPOS.y, 124 * resizeObject, 27 * resizeObject};
        Button lockers_mini_1Rect        = { 238 * resizeObject + cameraPOS.x, 81 * resizeObject + cameraPOS.y, 88 * resizeObject, 46 * resizeObject};
        Button boardBigRect              = { 238 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 84 * resizeObject, 38 * resizeObject};
        Button classnumber_1Rect         = { 318 * resizeObject + cameraPOS.x, 22 * resizeObject + cameraPOS.y, 24 * resizeObject, 37 * resizeObject};
        Button rubbishbinRect            = { 331 * resizeObject + cameraPOS.x, 94 * resizeObject + cameraPOS.y, 22 * resizeObject, 31 * resizeObject};
        Button bucketRect                = { 365 * resizeObject + cameraPOS.x, 94 * resizeObject + cameraPOS.y, 27 * resizeObject, 32 * resizeObject};
        Button laddersRect               = { 403 * resizeObject + cameraPOS.x, 0 * resizeObject + cameraPOS.y, 128 * resizeObject, 126 * resizeObject};
        Button clocksRect                = { 520 * resizeObject + cameraPOS.x, 23 * resizeObject + cameraPOS.y, 17 * resizeObject, 22 * resizeObject};
        Button firefighterRect           = { 531 * resizeObject + cameraPOS.x, 91 * resizeObject + cameraPOS.y, 25 * resizeObject, 34 * resizeObject};
        Button door2Rect                 = { 557 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button lockers_mini_2Rect        = { 602 * resizeObject + cameraPOS.x, 81 * resizeObject + cameraPOS.y, 88 * resizeObject, 46 * resizeObject};
        Button boardBig2Rect             = { 602 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 84 * resizeObject, 38 * resizeObject};
        Button windows2Rect              = { 558 * resizeObject + cameraPOS.x, 16 * resizeObject + cameraPOS.y, 124 * resizeObject, 27 * resizeObject};
        Button classnumber_2Rect         = { 683 * resizeObject + cameraPOS.x, 23 * resizeObject + cameraPOS.y, 24 * resizeObject, 37 * resizeObject};
        Button warning_Rect1             = { 616 * resizeObject + cameraPOS.x, 123 * resizeObject + cameraPOS.y, 16 * resizeObject, 18 * resizeObject};
        Button door3Rect                 = { 767 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button toilet_male_nomalyRect    = { 877 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button toilet_female_nomalyRect  = { 924 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button rubbishbin2Rect           = { 981 * resizeObject + cameraPOS.x, 94 * resizeObject + cameraPOS.y, 22 * resizeObject, 31 * resizeObject};
        Button ladders2Rect              = { 1003 * resizeObject + cameraPOS.x, 0 * resizeObject + cameraPOS.y, 128 * resizeObject, 126 * resizeObject};
        Button clocks1Rect               = { 1120 * resizeObject + cameraPOS.x, 23 * resizeObject + cameraPOS.y, 17 * resizeObject, 22 * resizeObject};
        Button door4Rect                 = { 1138 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button board_2Rect               = { 1183 * resizeObject + cameraPOS.x, 42 * resizeObject + cameraPOS.y, 51 * resizeObject, 32 * resizeObject};
        Button lockers_mini_3Rect        = { 1187 * resizeObject + cameraPOS.x, 80 * resizeObject + cameraPOS.y, 48 * resizeObject, 46 * resizeObject};
        Button door5Rect                 = { 1238 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 45 * resizeObject, 76 * resizeObject};
        Button boardBigRect2             = { 1283 * resizeObject + cameraPOS.x, 43 * resizeObject + cameraPOS.y, 84 * resizeObject, 38 * resizeObject};
        Button lockers_mini_4Rect        = { 1283 * resizeObject + cameraPOS.x, 81 * resizeObject + cameraPOS.y, 88 * resizeObject, 46 * resizeObject};
        Button windows3Rect              = { 1238 * resizeObject + cameraPOS.x, 15 * resizeObject + cameraPOS.y, 124 * resizeObject, 27 * resizeObject};
        Button classnumber_3Rect         = { 1362 * resizeObject + cameraPOS.x, 22 * resizeObject + cameraPOS.y, 24 * resizeObject, 37 * resizeObject};
        Button swabRect                  = { 1367 * resizeObject + cameraPOS.x, 62 * resizeObject + cameraPOS.y, 28 * resizeObject, 64 * resizeObject};
        Button bucket_anomalyRect        = { 1391 * resizeObject + cameraPOS.x, -16 * resizeObject + cameraPOS.y, 26 * resizeObject, 144 * resizeObject};
        Button elevatorRect              = { 1476 * resizeObject + cameraPOS.x, 51 * resizeObject + cameraPOS.y, 16 * resizeObject, 91 * resizeObject};
        Button elevatorButtonRect        = { 1470 * resizeObject + cameraPOS.x, 75 * resizeObject + cameraPOS.y, 5 * resizeObject, 24 * resizeObject};
        Button tileRect                  = { 1401 * resizeObject + cameraPOS.x, 119 * resizeObject + cameraPOS.y, 99 * resizeObject, 31 * resizeObject};
        Button brickwallRect             = { 1392 * resizeObject + cameraPOS.x, 0 * resizeObject + cameraPOS.y, 108 * resizeObject, 150 * resizeObject};
        Button warning_Rect2             = { 1356 * resizeObject + cameraPOS.x, 132 * resizeObject + cameraPOS.y, 16 * resizeObject, 18 * resizeObject};


        SDL_Rect closetAndFlower           = { 42 * resizeObject + cameraPOS.x, 34 * resizeObject, 132 * resizeObject  + cameraPOS.w, 92 * resizeObject + cameraPOS.h };
        SDL_Rect plinth                    = { 0 + cameraPOS.x, 114 * resizeObject, 1469 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect closetAndWall             = { 239 * resizeObject + cameraPOS.x, 77 * resizeObject, 191 * resizeObject + cameraPOS.w, 50 * resizeObject + cameraPOS.h };
        SDL_Rect closetAndBigCloset        = { 602 * resizeObject + cameraPOS.x, 77 * resizeObject, 159 * resizeObject + cameraPOS.w, 50 * resizeObject + cameraPOS.h };
        SDL_Rect WallAndExtinguisher       = { 504 * resizeObject + cameraPOS.x, 81 * resizeObject, 44 * resizeObject + cameraPOS.w, 44 * resizeObject + cameraPOS.h };
        SDL_Rect BigCloset                 = { 816 * resizeObject + cameraPOS.x, 37 * resizeObject, 53 * resizeObject + cameraPOS.w, 88 * resizeObject + cameraPOS.h };
        SDL_Rect TrashAndWall              = { 979 * resizeObject + cameraPOS.x, 82 * resizeObject, 50 * resizeObject + cameraPOS.w, 43 * resizeObject + cameraPOS.h };
        SDL_Rect Wall                      = { 1107 * resizeObject + cameraPOS.x, 83 * resizeObject, 24 * resizeObject + cameraPOS.w, 42 * resizeObject + cameraPOS.h };
        SDL_Rect closetSmall               = { 1185 * resizeObject + cameraPOS.x, 83 * resizeObject, 50 * resizeObject + cameraPOS.w, 42 * resizeObject + cameraPOS.h };
        SDL_Rect closetSmallAndBucket      = { 1282 * resizeObject + cameraPOS.x, 83 * resizeObject, 135 * resizeObject + cameraPOS.w, 42 * resizeObject + cameraPOS.h };

        SDL_Rect tablichka2                = { 1358 * resizeObject + cameraPOS.x, 134 * resizeObject, 11 * resizeObject + cameraPOS.w, 10 * resizeObject + cameraPOS.h };
        SDL_Rect tablichka1                = { 617 * resizeObject + cameraPOS.x, 127 * resizeObject, 11 * resizeObject + cameraPOS.w, 10 * resizeObject + cameraPOS.h };

        SDL_Rect collisionLeft1     = { 2 * resizeObject + cameraPOS.x, 120 * resizeObject, 3 * resizeObject + cameraPOS.w, 11 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft2     = { 4 * resizeObject + cameraPOS.x, 125 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft3     = { 6* resizeObject + cameraPOS.x, 128 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft4     = { 10 * resizeObject + cameraPOS.x, 133 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft5     = { 14 * resizeObject + cameraPOS.x, 137 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft6     = { 19 * resizeObject + cameraPOS.x, 141 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft7     = { 20 * resizeObject + cameraPOS.x, 144 * resizeObject, 4 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionLeft8     = { 25 * resizeObject + cameraPOS.x, 149 * resizeObject, 1472 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };

        SDL_Rect collisionRight1    = { 1494 * resizeObject + cameraPOS.x, 141 * resizeObject, 5 * resizeObject + cameraPOS.w, 20 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight2    = { 1492 * resizeObject + cameraPOS.x, 139 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight3    = { 1489 * resizeObject + cameraPOS.x, 135 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight4    = { 1486 * resizeObject + cameraPOS.x, 131 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight5    = { 1483 * resizeObject + cameraPOS.x, 127 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight6    = { 1478 * resizeObject + cameraPOS.x, 124 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight7    = { 1474 * resizeObject + cameraPOS.x, 120 * resizeObject, 5 * resizeObject + cameraPOS.w, 4 * resizeObject + cameraPOS.h };
        SDL_Rect collisionRight8    = { 1471 * resizeObject + cameraPOS.x, 119 * resizeObject, 5 * resizeObject + cameraPOS.w, 8 * resizeObject + cameraPOS.h };


        SDL_Rect collisionTrigger   = { 193 * resizeObject + cameraPOS.x, 43 * resizeObject, 45 * resizeObject + cameraPOS.w, 200 * resizeObject + cameraPOS.h };

        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (now - start) / (double)SDL_GetPerformanceFrequency();
        start = now;
        fpsCounter.frameStart = SDL_GetTicks();
        fpsCounter.frameCount++;
        if(fpsCounter.frameStart >= (fpsCounter.lastFrame + 1000)) {
            fpsCounter.lastFrame = fpsCounter.frameStart;
            sprintf(fpsCounter.fps_text, "FPS:%d", fpsCounter.frameCount);
            fpsCounter.frameCount = 0;
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
                deleteTrash(renderer,window);
                TTF_Quit();
                return 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (currentState == MENU) {
                    if (isMouseOverButton(&e,&QuitButton)){
                        quit = 1;
                        deleteTrash(renderer,window);
                        TTF_Quit();
                        return 1;
                    }
                }
            }
                if (keyboardState[SDL_SCANCODE_ESCAPE]) {
                    currentState = MENU;
                }
        }


        SDL_RenderClear(renderer);

        if (currentState == MENU || currentState == GAME_WAIT) {
            if (currentState == GAME_WAIT){
                ObjStatus[5] = 1;
            }
            SDL_RenderCopy(renderer, backgroundMenuTexture, NULL, NULL);
            SDL_RenderCopy(renderer, TransitionAnimTexture, NULL, NULL);
            SDL_RenderCopy(renderer, playButton.texture, NULL, &playButton.rect);
            SDL_RenderCopy(renderer, QuitButton.texture, NULL, &QuitButton.rect);
            SDL_RenderCopy(renderer, PlusMusicVolume.texture, NULL, &PlusMusicVolume.rect);
            SDL_RenderCopy(renderer, MinusMusicVolume.texture, NULL, &MinusMusicVolume.rect);
            if (ObjStatus[5] == 0)
            {
                TransitionAnimTexture = loadTexture(renderer, "../gameSDL/resources/png/transition/frame_1.png");
            } else if (ObjStatus[5] == 1)
            {
                animateSpriteAAA(TransitionAnimFrames,numTransitionFrames,21,1000,&TransitionAnimTexture,&startTransition,&ObjFrame[5]);
                if (ObjFrame[5] == 0)
                {
                    ObjStatus[5] = 2;
                    currentState = GAME;
                }
            }
            if (SDL_PointInRect(&mousePos, &QuitButton.rect))
            {
                SDL_RenderCopy(renderer, loadTexture(renderer, "../gameSDL/resources/button/quit/exit_aimed.png"), NULL, &QuitButton.rect);
            }
            if (SDL_PointInRect(&mousePos, &PlusMusicVolume.rect))
            {
                SDL_RenderCopy(renderer, loadTexture(renderer, "../gameSDL/resources/button/plus/plus_aimed.png"), NULL, &PlusMusicVolume.rect);
            }
            if (SDL_PointInRect(&mousePos, &MinusMusicVolume.rect))
            {
                SDL_RenderCopy(renderer, loadTexture(renderer, "../gameSDL/resources/button/minus/minus_aimed.png"), NULL, &MinusMusicVolume.rect);
            }
            
            if (SDL_PointInRect(&mousePos, &playButton.rect) || SDL_PointInRect(&mousePos, &QuitButton.rect) || SDL_PointInRect(&mousePos, &PlusMusicVolume.rect) || SDL_PointInRect(&mousePos, &MinusMusicVolume.rect))
            {   
                if (!isHovered) {
                    playSoundEffect(hoverSound);
                    isHovered = true;
                }
                    if (isMouseOverButton(&e,&playButton)) {
                    playSoundEffect(buttonPressed);
                    currentState = GAME_WAIT;
                    }

                    if (isMouseOverButton(&e,&PlusMusicVolume)) {
                    playSoundEffect(buttonPressed);
                        if (volumeMusic < 10 && plusButtonPressed == 0)
                        {
                            volumeMusic += 1;
                            plusButtonPressed = 1;
                            Mix_Volume(-1, volumeMusic * 10);
                        }
                    } else plusButtonPressed = 0;
                        if (isMouseOverButton(&e,&MinusMusicVolume)) {
                            playSoundEffect(buttonPressed);
                                if (volumeMusic > 0 && minusButtonPressed == 0)
                                    {
                                        volumeMusic -= 1;
                                        minusButtonPressed = 1;
                                        Mix_Volume(-1, volumeMusic * 10);
                                    }
                            } else minusButtonPressed = 0;
            } else {
                isHovered = false;
                }

            sprintf(VolumeText, "Volume:%d", volumeMusic * 10);
            renderText(renderer, musicTextVolume, &volumeTextTexture, VolumeText, windowWidth / 2 - 70, windowHeight / 2 + 95, textColor);
                if (SDL_PointInRect(&mousePos, &playButton.rect))
                {
                    SDL_RenderCopy(renderer, loadTexture(renderer, "../gameSDL/resources/button/start/play_aimed.png"), NULL, &playButton.rect);
                }
                SDL_RenderPresent(renderer);
        }

        if (currentState == GAME_LIFT)
        {
            SDL_RenderClear(renderer);
            sprintf(LiftText, "%d", countLift);
            SDL_RenderCopy(renderer,LiftWallTexture, NULL, NULL);
            SDL_RenderCopy(renderer,MainButtonLift, NULL, &ButtonMainLift.rect);
            SDL_RenderCopy(renderer,UpButtonLift, NULL, &ButtonUpLift.rect);
            SDL_RenderCopy(renderer,DownButtonLift, NULL, &ButtonDownLift.rect);
            renderTextSize(renderer, countLiftFont, &TextTextureLift, LiftText, windowWidth / 3 + 330, windowHeight / 3 + 60, textColorAnomiles,1.0);
           if (isMouseOverButton(&e,&ButtonUpLift))
           {
                SDL_RenderCopy(renderer,UpButtonLiftPressed, NULL, &ButtonUpLift.rect);
                if (ObjectsButtonPressed == 0){
                    ObjectsButtonPressed = 1;
                    countLift+=1;
                }
           }else
                ObjectsButtonPressed = 0;

            if (isMouseOverButton(&e,&ButtonDownLift))
           {
            SDL_RenderCopy(renderer,DownButtonLiftPressed, NULL, &ButtonDownLift.rect);
           }
           
          SDL_RenderPresent(renderer);
        }
        

        if (currentState == GAME) {
            if (ObjStatus[5] == 2)
            {
                reverseAnimateSpriteAAA(TransitionAnimFrames,numTransitionFrames,21,1000,&TransitionAnimTexture,&startTransitionEnd,&ObjFrame[5]);
                if (ObjFrame[5] == 0)
                {
                    ObjStatus[5] = 0;
                }
            }
                if (isMouseOverButton(&e,&windowsRect) && e.button.button == SDL_BUTTON_LEFT){
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "window") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "window";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[2] = randomStatus[2];
                        }
                    }
                } else if (isMouseOverButton(&e,&windowsRect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "window") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&windows2Rect) && e.button.button == SDL_BUTTON_LEFT){
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "windows2Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "windows2Rect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[19] = randomStatus[19];
                        }
                    }
                } else if (isMouseOverButton(&e,&windows2Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "windows2Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&windows3Rect) && e.button.button == SDL_BUTTON_LEFT){
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "windows3Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "windows3Rect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[20] = randomStatus[20];
                        }
                    }
                } else if (isMouseOverButton(&e,&windows3Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "windows3Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&door1Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "door1") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "door1";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[0] = randomStatus[0];
                        }
                    }
                } else if (isMouseOverButton(&e,&door1Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "door1") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&bucket_anomalyRect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "bucket_anomalyRect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "bucket_anomalyRect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[1] = randomStatus[1];
                        }
                    }
                } else if (isMouseOverButton(&e,&bucket_anomalyRect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "bucket_anomalyRect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&rubbishbinRect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "rubbishbinRect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "rubbishbinRect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[3] = randomStatus[3];
                        }
                    }
                } else if (isMouseOverButton(&e,&rubbishbinRect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "rubbishbinRect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&rubbishbin2Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "rubbishbin2Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "rubbishbin2Rect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[15] = randomStatus[15];
                        }
                    }
                } else if (isMouseOverButton(&e,&rubbishbin2Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "rubbishbin2Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }  else if (isMouseOverButton(&e,&firefighterRect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "firefighterRect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }

                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "firefighterRect";

                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;

                            ObjectsButtonPressed = 1;
                            ObjStatus[4] = randomStatus[4];
                        }
                    }

                } else if (isMouseOverButton(&e,&firefighterRect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "firefighterRect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                } else if (isMouseOverButton(&e,&lockers_1Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_1Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_1Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[6] = 1;
                        }
                    }
                } else if (isMouseOverButton(&e,&lockers_1Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_1Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_2Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_2Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_2Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[7] = randomStatus[7];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_2Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_2Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_3Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_3Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_3Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[8] = randomStatus[8];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_3Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_3Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_4Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_4Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_4Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[9] = randomStatus[9];
                        }
                    }
                } else if (isMouseOverButton(&e,&lockers_4Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_4Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_5Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_5Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_5Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[10] = randomStatus[10];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_5Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_5Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_6Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_6Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_6Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[11] = randomStatus[11];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_6Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_6Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_7Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_7Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_7Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjStatus[12] = randomStatus[12];
                            ObjectsButtonPressed = 1;
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_7Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_7Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_8Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_8Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_8Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[13] = randomStatus[13];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_8Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_8Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&lockers_9Rect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (ObjectsButtonPressed == 0 && anomalyCount < MAX_ANOMALIES) {
                        int alreadyExists = 0;
                        for (int i = 0; i < anomalyCount; i++) {
                            if (strcmp(anomalies[i].name, "lockers_9Rect") == 0) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            Anomaly newAnomaly;
                            newAnomaly.name = "lockers_9Rect";
                            anomalies[anomalyCount] = newAnomaly;
                            anomalyCount++;
                            ObjectsButtonPressed = 1;
                            ObjStatus[14] = randomStatus[14];
                        }
                    }

                } else if (isMouseOverButton(&e,&lockers_9Rect) && e.button.button == SDL_BUTTON_RIGHT)
                {
                    for (int i = 0; i < anomalyCount; i++) {
                        if (strcmp(anomalies[i].name, "lockers_9Rect") == 0) {
                            for (int j = i; j < anomalyCount - 1; j++) {
                                anomalies[j] = anomalies[j + 1];
                            }
                            anomalyCount--;
                            break;
                        }
                    }
                    ObjectsButtonPressed = 1;
                }else if (isMouseOverButton(&e,&elevatorRect) && e.button.button == SDL_BUTTON_LEFT)
                {
                    ObjStatus[21] = 1;
                }else
                    ObjectsButtonPressed = 0;
                

                if (ObjStatus[0] == 0)
                {
                    if (door1Texture == NULL)
                        door1Texture = loadTexture(renderer, "../gameSDL/resources/png/scene/door/frame_1.png");
                }
                else if (ObjStatus[0] == 1){
                    animateSpriteAAA(doorAnimFrames,numDoorFrames,10, 2300, &door1Texture,&startTimeDoor,&ObjFrame[0]);
                    if (ObjFrame[0] == 0)
                        ObjStatus[0] = 2;
                }else if (ObjStatus[0] == 2) {
                    reverseAnimateSpriteAAA(doorAnimFrames,numDoorFrames,10, 2300, &door1Texture,&reverseStartTimeDoor,&ObjFrame[0]);
                    if (ObjFrame[0] == 0)
                        ObjStatus[0] = 0;
                }else if (ObjStatus[0] == 3) {
                    if (door1Texture != checkerTexture2)
                        door1Texture = loadTexture(renderer, "../gameSDL/resources/png/scene/door/frame_3.png");
                }

                if (ObjStatus[1] == 0)
                {
                    if (BucketTexture1 == NULL)
                        BucketTexture1  = loadTexture(renderer, "../gameSDL/resources/png/scene/bucket/frame_1.png");
                } else if (ObjStatus[1] == 1)
                {
                    animateSpriteAAA(BucketAnimFrames,numBucketFrames,40,1000,&BucketTexture1,&startbucketTime,&ObjFrame[1]);
                } 

                if (ObjStatus[2] == 0)
                {
                    if (WindowAnimTexture == NULL)
                        WindowAnimTexture  = loadTexture(renderer, "../gameSDL/resources/png/scene/window/frame_1.png");
                } else if (ObjStatus[2] == 1)
                {
                    animateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture,&startTimeWindow,&ObjFrame[2]);
                    if (ObjFrame[2] == 0)
                    {
                        ObjStatus[2] = 0;
                    }
                } else if (ObjStatus[2] == 2)
                {
                    reverseAnimateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture,&reversestartTimeWindow,&ObjFrame[2]);
                    if (ObjFrame[2] == 0)
                    {
                        ObjStatus[2] = 0;
                    }
                } else if (ObjStatus[2] == 3)
                {
                    animateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture,&startTimeWindow,&ObjFrame[2]);
                    if (ObjFrame[2] == 0)
                    {
                        ObjStatus[2] = 4;
                    }
                } else if (ObjStatus[2] == 4)
                {
                    reverseAnimateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture,&reversestartTimeWindow,&ObjFrame[2]);
                    if (ObjFrame[2] == 0)
                    {
                        ObjStatus[2] = 0;
                    }
                } 

                if (ObjStatus[3] == 0)
                {
                    if (RubbishBinTexture == NULL)
                        RubbishBinTexture  = loadTexture(renderer, "../gameSDL/resources/png/scene/rubbishBin/frame_1.png");
                }
                else if (ObjStatus[3] == 1)
                {
                    animateSpriteAAA(RubbishBinAnimFrames,numRubbishBinFrames,11,1500, &RubbishBinTexture,&startrubbishbinAnim,&ObjFrame[3]);
                    if (ObjFrame[3] == 0)
                        ObjStatus[3] = 2;
                } else if (ObjStatus[3] == 2)
                {
                    reverseAnimateSpriteAAA(RubbishBinAnimFrames,numRubbishBinFrames,11,1500, &RubbishBinTexture,&reversestartrubbishbinAnim,&ObjFrame[3]);
                    if (ObjFrame[3] == 0)
                        ObjStatus[3] = 0;
                } else if (ObjStatus[3] == 3)
                {
                    RubbishBinTexture  = loadTexture(renderer, "../gameSDL/resources/png/scene/rubbishbin_big.png");
                }

                if (ObjStatus[4] == 0)
                {
                    if (OgnetushitelTexture == NULL)
                        OgnetushitelTexture = loadTexture(renderer, "../gameSDL/resources/png/scene/ognetushitel/frame_1.png");
                }
                else if (ObjStatus[4] == 1)
                {
                    animateSpriteAAA(OgnetushitelAnimFrames,numOgnetushitelFrames,6,1500, &OgnetushitelTexture,&startOgnetushitelAnim,&ObjFrame[4]);
                    if (ObjFrame[4] == 0)
                        ObjStatus[4] = 2;
                } else if (ObjStatus[4] == 2)
                {
                    reverseAnimateSpriteAAA(OgnetushitelAnimFrames,numOgnetushitelFrames,6,1500, &OgnetushitelTexture,&reversestartOgnetushitelAnim,&ObjFrame[4]);
                    if (ObjFrame[4] == 0)
                        ObjStatus[4] = 0;
                } else if (ObjStatus[4] == 3)
                    {
                        if (checkerTexture1 != OgnetushitelTexture)
                            OgnetushitelTexture = loadTexture(renderer, "../gameSDL/resources/png/scene/firefighter_big.png");
                }

                if (ObjStatus[6] == 0)
                {
                    if (LockerTexture1 == NULL)
                        LockerTexture1  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }
                else if (ObjStatus[6] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames1,numLockerFrames,10,2300, &LockerTexture1,&startLocker1Anim,&ObjFrame[6]);
                    if (ObjFrame[6] == 0)
                        ObjStatus[6] = 2;
                } else if (ObjStatus[6] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames1,numLockerFrames,10,2300, &LockerTexture1,&reversestartLocker1Anim,&ObjFrame[6]);
                    if (ObjFrame[6] == 0)
                        ObjStatus[6] = 0;
                }else if (ObjStatus[6] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[7] == 0)
                {
                    if (LockerTexture2 == NULL)
                        LockerTexture2  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker2/frame_1.png");
                }
                else if (ObjStatus[7] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames2,numLockerFrames,10,2300, &LockerTexture2,&startLocker2Anim,&ObjFrame[7]);
                    if (ObjFrame[7] == 0)
                        ObjStatus[7] = 2;
                } else if (ObjStatus[7] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames2,numLockerFrames,10,2300, &LockerTexture2,&reversestartLocker2Anim,&ObjFrame[7]);
                    if (ObjFrame[7] == 0)
                        ObjStatus[7] = 0;
                } else if (ObjStatus[7] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }else if (ObjStatus[7] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[8] == 0)
                {
                    if (LockerTexture3 == NULL)
                        LockerTexture3  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker3/frame_1.png");
                }
                else if (ObjStatus[8] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames3,numLockerFrames,10,2300, &LockerTexture3,&startLocker3Anim,&ObjFrame[8]);
                    if (ObjFrame[8] == 0)
                        ObjStatus[8] = 2;
                } else if (ObjStatus[8] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames3,numLockerFrames,10,2300, &LockerTexture3,&reversestartLocker3Anim,&ObjFrame[8]);
                    if (ObjFrame[8] == 0)
                        ObjStatus[8] = 0;
                }else if (ObjStatus[8] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[9] == 0)
                {
                    if (LockerTexture4 == NULL)
                        LockerTexture4  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker4/frame_1.png");
                }
                else if (ObjStatus[9] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames4,numLockerFrames,10,2300, &LockerTexture4,&startLocker4Anim,&ObjFrame[9]);
                    if (ObjFrame[9] == 0)
                        ObjStatus[9] = 2;
                } else if (ObjStatus[9] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames4,numLockerFrames,10,2300, &LockerTexture4,&reversestartLocker4Anim,&ObjFrame[9]);
                    if (ObjFrame[9] == 0)
                        ObjStatus[9] = 0;
                }else if (ObjStatus[9] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[10] == 0)
                {
                    if (LockerTexture5 == NULL)
                        LockerTexture5  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker5/frame_1.png");
                }
                else if (ObjStatus[10] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames5,numLockerFrames,10,2300, &LockerTexture5,&startLocker5Anim,&ObjFrame[10]);
                    if (ObjFrame[10] == 0)
                        ObjStatus[10] = 2;
                } else if (ObjStatus[10] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames5,numLockerFrames,10,2300, &LockerTexture5,&reversestartLocker5Anim,&ObjFrame[10]);
                    if (ObjFrame[10] == 0)
                        ObjStatus[10] = 0;
                }else if (ObjStatus[10] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[11] == 0)
                {
                    if (LockerTexture6 == NULL)
                        LockerTexture6  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker6/frame_1.png");
                }
                else if (ObjStatus[11] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames6,numLockerFrames,10,2300, &LockerTexture6,&startLocker6Anim,&ObjFrame[11]);
                    if (ObjFrame[11] == 0)
                        ObjStatus[11] = 2;
                } else if (ObjStatus[11] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames6,numLockerFrames,10,2300, &LockerTexture6,&reversestartLocker6Anim,&ObjFrame[11]);
                    if (ObjFrame[11] == 0)
                        ObjStatus[11] = 0;
                }else if (ObjStatus[11] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[12] == 0)
                {
                    if (LockerTexture7 == NULL)
                        LockerTexture7  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker7/frame_1.png");
                }
                else if (ObjStatus[12] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames7,numLockerFrames,10,2300, &LockerTexture7,&startLocker7Anim,&ObjFrame[12]);
                    if (ObjFrame[12] == 0)
                        ObjStatus[12] = 2;
                } else if (ObjStatus[12] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames7,numLockerFrames,10,2300, &LockerTexture7,&reversestartLocker7Anim,&ObjFrame[12]);
                    if (ObjFrame[12] == 0)
                        ObjStatus[12] = 0;
                }else if (ObjStatus[12] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[13] == 0)
                {
                    if (LockerTexture8 == NULL)
                        LockerTexture8  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker8/frame_1.png");
                }
                else if (ObjStatus[13] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames8,numLockerFrames,10,2300, &LockerTexture8,&startLocker8Anim,&ObjFrame[13]);
                    if (ObjFrame[13] == 0)
                        ObjStatus[13] = 2;
                } else if (ObjStatus[13] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames8,numLockerFrames,10,2300, &LockerTexture8,&reversestartLocker8Anim,&ObjFrame[13]);
                    if (ObjFrame[13] == 0)
                        ObjStatus[13] = 0;
                }else if (ObjStatus[13] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[14] == 0)
                {
                    if (LockerTexture9 == NULL)
                        LockerTexture9  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker9/frame_1.png");
                }
                else if (ObjStatus[14] == 1)
                {
                    animateSpriteAAA(LockerAnimFrames9,numLockerFrames,10,2300, &LockerTexture9,&startLocker9Anim,&ObjFrame[14]);
                    if (ObjFrame[14] == 0)
                        ObjStatus[14] = 2;
                } else if (ObjStatus[14] == 2)
                {
                    reverseAnimateSpriteAAA(LockerAnimFrames9,numLockerFrames,10,2300, &LockerTexture9,&reversestartLocker9Anim,&ObjFrame[14]);
                    if (ObjFrame[14] == 0)
                        ObjStatus[14] = 0;
                } else if (ObjStatus[14] == 2)
                {
                    if (LockerTexture9 == NULL)
                        LockerTexture9  = loadTexture(renderer, "../gameSDL/resources/png/scene/locker9/frame_1.png");
                }
                else if (ObjStatus[14] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[15] == 0)
                {
                    if (RubbishBinTexture1 == NULL)
                        RubbishBinTexture1  = loadTexture(renderer, "../gameSDL/resources/png/scene/rubbishBin/frame_1.png");
                }
                else if (ObjStatus[15] == 1)
                {
                    animateSpriteAAA(RubbishBinAnimFrames,numRubbishBinFrames,11,1500, &RubbishBinTexture1,&startrubbishbin1Anim,&ObjFrame[15]);
                    if (ObjFrame[15] == 0)
                        ObjStatus[15] = 2;
                } else if (ObjStatus[15] == 2)
                {
                    reverseAnimateSpriteAAA(RubbishBinAnimFrames,numRubbishBinFrames,11,1500, &RubbishBinTexture1,&reversestartrubbishbin1Anim,&ObjFrame[15]);
                    if (ObjFrame[15] == 0)
                        ObjStatus[15] = 0;
                } else if (ObjStatus[15] == 3)
                {
                    if (checkerTexture != LockerTexture2)
                        LockerTexture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/locker1/frame_1.png");
                }

                if (ObjStatus[16] == 0)
                {
                    if (warning_Texture1 == NULL)
                        warning_Texture1 = loadTexture(renderer, "../gameSDL/resources/png/scene/warning_nomaly.png");
                }
                else if (ObjStatus[16] == 1)
                {
                    if (warning_Texture1 == NULL)
                        warning_Texture1 = loadTexture(renderer, "../gameSDL/resources/png/scene/warning_anomaly.png");
                }

                if (ObjStatus[17] == 0)
                {
                    if (warning_Texture2 == NULL)
                        warning_Texture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/warning_nomaly.png");
                }
                else if (ObjStatus[17] == 1)
                {
                    if (warning_Texture2 == NULL)
                        warning_Texture2 = loadTexture(renderer, "../gameSDL/resources/png/scene/warning_anomaly.png");
                }
                if (ObjStatus[19] == 0)
                {
                    if (WindowAnimTexture1 == NULL)
                        WindowAnimTexture1  = loadTexture(renderer, "../gameSDL/resources/png/scene/window/frame_1.png");
                }
                else if (ObjStatus[19] == 1)
                {
                    animateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture1,&startTimeWindow1,&ObjFrame[19]);
                    if (ObjFrame[19] == 0)
                        ObjStatus[19] = 2;
                } else if (ObjStatus[19] == 2)
                {
                    reverseAnimateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1500, &WindowAnimTexture1,&reversestartTimeWindow1,&ObjFrame[19]);
                    if (ObjFrame[19] == 0)
                        ObjStatus[19] = 0;
                } else if (ObjStatus[2] == 3)
                {
                    animateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture1,&startTimeWindow1,&ObjFrame[19]);
                    if (ObjFrame[19] == 0)
                    {
                        ObjStatus[19] = 4;
                    }
                } else if (ObjStatus[19] == 4)
                {
                    reverseAnimateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1500, &WindowAnimTexture1,&reversestartTimeWindow1,&ObjFrame[19]);
                    if (ObjFrame[19] == 0)
                    {
                        ObjStatus[19] = 0;
                    }
                } 


                if (ObjStatus[20] == 0)
                {
                    if (WindowAnimTexture2 == NULL)
                        WindowAnimTexture2  = loadTexture(renderer, "../gameSDL/resources/png/scene/window/frame_1.png");
                }
                else if (ObjStatus[20] == 1)
                {
                    animateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture2,&startTimeWindow2,&ObjFrame[20]);
                    if (ObjFrame[20] == 0)
                        ObjStatus[20] = 2;
                } else if (ObjStatus[20] == 2)
                {
                    reverseAnimateSpriteAAA(Window_NormAnimFrames,numWindowFrames,18,1500, &WindowAnimTexture2,&reversestartTimeWindow2,&ObjFrame[20]);
                    if (ObjFrame[20] == 0)
                        ObjStatus[20] = 0;
                }else if (ObjStatus[2] == 3)
                {
                    animateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1000,&WindowAnimTexture1,&startTimeWindow1,&ObjFrame[20]);
                    if (ObjFrame[20] == 0)
                    {
                        ObjStatus[20] = 4;
                    }
                } else if (ObjStatus[19] == 4)
                {
                    reverseAnimateSpriteAAA(WindowAnimFrames,numWindowFrames,18,1500, &WindowAnimTexture1,&reversestartTimeWindow1,&ObjFrame[20]);
                    if (ObjFrame[20] == 0)
                    {
                        ObjStatus[20] = 0;
                    }
                } 


                if (ObjStatus[21] == 0)
                {
                    if (ElevatorTexture == NULL)
                        ElevatorTexture  = loadTexture(renderer, "../gameSDL/resources/png/scene/elevator/frame_1.png");
                }
                else if (ObjStatus[21] == 1)
                {
                    animateSpriteAAA(ElevatorAnimFrames,numElevatorFrames,9,1000,&ElevatorTexture,&startTimeLift,&ObjFrame[21]);
                    if (ObjFrame[21] == 0)
                        ObjStatus[21] = 2;
                } else if (ObjStatus[21] == 2)
                {
                    animateSpriteAAA(TransitionAnimFrames,numTransitionFrames,21,1000,&TransitionAnimTexture,&startTransition,&ObjFrame[21]);
                    if (ObjFrame[21] == 0)
                    {
                        ObjStatus[21] = 3;
                    }
                }else if (ObjStatus[21] == 3)
                {
                    sceneTexture = loadTexture(renderer, "../gameSDL/resources/png/transition/frame_1.png");
                    SDL_RenderCopy(renderer,sceneTexture,NULL,&sceneRect);
                }
                

            int fakeSPEED = 0;
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&closetAndFlower,keyboardState,&fpsCounter.FPS,&SPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&plinth,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&closetAndWall,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&closetAndBigCloset,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&WallAndExtinguisher,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&BigCloset,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&TrashAndWall,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&Wall,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&closetSmall,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&closetSmallAndBucket,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&tablichka2,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&tablichka1,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft1,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft2,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft3,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft4,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft5,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft6,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft7,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionLeft8,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight1,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight2,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight3,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight4,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight5,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight6,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight7,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            checkCollisionAndMoveSprite(&cameraPOS, &spriteRect,&spriteRectCollision,&collisionRight8,keyboardState,&fpsCounter.FPS,&fakeSPEED,collisionIntervalX,collisionIntervalY);
            sprintf(AnomalyText, "anomalies found List:%d", anomalyCount);

            SDL_RenderClear(renderer);
        
            SDL_RenderCopy(renderer, sceneTexture, NULL, &sceneRect);
            SDL_RenderCopy(renderer, brickwallTexture, NULL, &brickwallRect.rect);
            SDL_RenderCopy(renderer, tileTexture, NULL, &tileRect.rect);

            SDL_RenderCopy(renderer, LockerTexture9, NULL, &lockers_9Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture8, NULL, &lockers_8Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture7, NULL, &lockers_7Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture6, NULL, &lockers_6Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture5, NULL, &lockers_5Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture4, NULL, &lockers_4Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture3, NULL, &lockers_3Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture2, NULL, &lockers_2Rect.rect);
            SDL_RenderCopy(renderer, LockerTexture1, NULL, &lockers_1Rect.rect);

            SDL_RenderCopy(renderer, backpackButton.texture, NULL, &backpackRect.rect);
            SDL_RenderCopy(renderer, flowerTexture, NULL, &flowerRect.rect);
            SDL_RenderCopy(renderer, board_1Texture, NULL, &board_1Rect.rect);
            SDL_RenderCopy(renderer, door1Texture, NULL, &door1Rect.rect);
            SDL_RenderCopy(renderer, WindowAnimTexture, NULL, &windowsRect.rect);
            SDL_RenderCopy(renderer, lockers_mini_1Texture, NULL, &lockers_mini_1Rect.rect);
            SDL_RenderCopy(renderer, boardBigTexture, NULL, &boardBigRect.rect);
            SDL_RenderCopy(renderer, classnumber_1Texture, NULL, &classnumber_1Rect.rect);
            SDL_RenderCopy(renderer, RubbishBinTexture, NULL, &rubbishbinRect.rect);
            SDL_RenderCopy(renderer, bucketTexture, NULL, &bucketRect.rect);
            SDL_RenderCopy(renderer, laddersTexture, NULL, &laddersRect.rect);
            SDL_RenderCopy(renderer, clocksTexture, NULL, &clocksRect.rect);
            SDL_RenderCopy(renderer, OgnetushitelTexture, NULL, &firefighterRect.rect);
            SDL_RenderCopy(renderer, doorTexture, NULL, &door2Rect.rect);
            SDL_RenderCopy(renderer, lockers_mini_1Texture, NULL, &lockers_mini_2Rect.rect);
            SDL_RenderCopy(renderer, boardBigTexture, NULL, &boardBig2Rect.rect);
            SDL_RenderCopy(renderer, WindowAnimTexture1, NULL, &windows2Rect.rect);
            SDL_RenderCopy(renderer, classnumber_2Texture, NULL, &classnumber_2Rect.rect);
            SDL_RenderCopy(renderer, warning_Texture1, NULL, &warning_Rect1.rect);
            SDL_RenderCopy(renderer, doorTexture, NULL, &door3Rect.rect);
            SDL_RenderCopy(renderer, toilet_male_nomalyTexture, NULL, &toilet_male_nomalyRect.rect);
            SDL_RenderCopy(renderer, toilet_female_nomalyTexture, NULL, &toilet_female_nomalyRect.rect);
            SDL_RenderCopy(renderer, RubbishBinTexture1, NULL, &rubbishbin2Rect.rect);
            SDL_RenderCopy(renderer, laddersTexture, NULL, &ladders2Rect.rect);
            SDL_RenderCopy(renderer, clocksTexture, NULL, &clocks1Rect.rect);
            SDL_RenderCopy(renderer, doorTexture, NULL, &door4Rect.rect);
            SDL_RenderCopy(renderer, board_1Texture, NULL, &board_2Rect.rect);
            SDL_RenderCopy(renderer, lockers_mini_3Texture, NULL, &lockers_mini_3Rect.rect);
            SDL_RenderCopy(renderer, doorTexture, NULL, &door5Rect.rect);
            SDL_RenderCopy(renderer, boardBigTexture, NULL, &boardBigRect2.rect);
            SDL_RenderCopy(renderer, swabTexture, NULL, &swabRect.rect);
            SDL_RenderCopy(renderer, lockers_mini_1Texture, NULL, &lockers_mini_4Rect.rect);
            SDL_RenderCopy(renderer, WindowAnimTexture2, NULL, &windows3Rect.rect);    
            SDL_RenderCopy(renderer, classnumber_2Texture, NULL, &classnumber_3Rect.rect); 
            SDL_RenderCopy(renderer, BucketTexture1, NULL, &bucket_anomalyRect.rect);
            
            SDL_RenderCopy(renderer, ElevatorTexture, NULL, &elevatorRect.rect);
            SDL_RenderCopy(renderer, elevatorButtonTexture, NULL, &elevatorButtonRect.rect);
            SDL_RenderCopy(renderer, warning_Texture2, NULL, &warning_Rect2.rect);
            SDL_RenderCopy(renderer, currentTexture, NULL, &spriteRect);
            SDL_RenderCopy(renderer, TransitionAnimTexture, NULL, NULL);
            if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT])
            {
                if (!isHoveredTest) {
                    playSoundEffect(run);
                    isHoveredTest = true;
                }
                animateSpriteAAA(rightSpriteFrames,numRightFrames,5,950,&currentTexture,&startTime,&currentFrame);
                SDL_RenderCopy(renderer, TipochekRightTexture, NULL, &FlashlightRect);
                nothingFrame = false;
                
            }
            else if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT])
            {
                if (!isHoveredTest) {
                    playSoundEffect(run);
                    isHoveredTest = true;
                }
                animateSpriteAAA(leftSpriteFrames,numLeftFrames,5,950,&currentTexture,&startTime,&currentFrame);
                FlashlightRect.x -= resizeObject * 75;
                SDL_RenderCopy(renderer, TipochekLeftTexture, NULL, &FlashlightRect);
                nothingFrame = true;
            }
            else if (nothingFrame == false)
            {
                SDL_RenderCopy(renderer, TipochekRightTexture, NULL, &FlashlightRect);
                animateSpriteAAA(nothingFrames,numNothingFrames,10,950,&currentTexture,&startTime,&currentFrame);
                stopSoundEffect(run);
                isHoveredTest = false;
            }
            else {
                FlashlightRect.x -= resizeObject * 75;
                SDL_RenderCopy(renderer, TipochekLeftTexture, NULL, &FlashlightRect);
                animateSpriteAAA(nothingFramesReverse,numNothingFramesReverse,10,950,&currentTexture,&startTime,&currentFrame);
                stopSoundEffect(run);
                isHoveredTest = false;
            }

            SDL_UpdateWindowSurface(window);

            renderText(renderer, countFont, &countAnomaly,AnomalyText, 0, 0, textColorAnomiles);

            if (ObjStatus[21] == 3)
            {
                renderText(renderer,countLiftFont,&TextTextureLift123,"To be continued", windowWidth / 3, windowHeight / 2, textColorAnomiles);
            }


            //check trigger
            if (checkTriggerCollision(&spriteRectCollision, &collisionTrigger) == 1) {
                if (!triggerState) {
                    timerID1 = SDL_AddTimer(500, timerCallbackStateTrue, NULL);
                    timerID2 = SDL_AddTimer(500, timerCallbackStateEffectMusicTrue, NULL);
                    triggerState = true;
                }
            }
            else triggerState = false;

            if (timer1Active){
                SDL_RemoveTimer(timerID1);
                timerID1 = SDL_AddTimer(2000, timerCallbackStateEffect, NULL);
                timer1Active = false;
            }
            if (timer2Active){
                SDL_RemoveTimer(timerID2);
                timerID2 = SDL_AddTimer(3000, timerCallbackStateEffectMusic, NULL);
                timer2Active = false;
            }

            if (effectActive) {
                //renderNoise(renderer,noiseTexture,windowWidth,windowHeight,120);
                //renderNoiseAnimation(renderer,noise,numNoise,20,&noiseTexture,&startTimeVignett,&currentFrameVignett,&windowWidth,&windowHeight,170);
                //timerID = SDL_AddTimer(2500, timerCallbackStateEffect, NULL);
                //timerID = SDL_AddTimer(2500, timerCallbackStateEffectMusic, NULL);
                //stopSoundEffect(effect);
                //vignetteFilterAnimation(renderer, vignetteFilter, numVignetteFrames, 30, &quit, &vignetteTexture, &startTimeVignett, &currentFrameVignett, &windowWidth, &windowHeight);
                //renderGlitch(renderer,flowerTexture,flowerRect,10);
                //renderGlitch1(renderer,flowerTexture,flowerRect,10);
                //renderColorChannelGlitch(renderer,flowerTexture,flowerRect.w, flowerRect.h,5,170, flowerRect);
                //inversionColor(renderer,flowerTexture,flowerRect.w, flowerRect.h,5,170,flowerRect);
           }
            SDL_GL_SetSwapInterval(1);
            SDL_RenderPresent(renderer);
        }
        fpsCounter.frameTime = SDL_GetTicks() - fpsCounter.frameStart;
    }
    return 0;
}


void deleteTrash(SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_RemoveTimer(timerID);
}
