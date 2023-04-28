enum DIFFICULTY {
    UNDEFINED, EASY, MEDIUM, HARD
};

enum GAME_STATUS {
    STARTING, INITIALIZING, RUNNING, LOSE, WIN
};

enum MODE {
    DARK, LIGHT
};

// properties of the board
int X, Y, BOARD_WIDTH, BOARD_HEIGHT, CELL_SIZE;
// current flags of game
int CURRENT_FLAGS;

// current status of game
GAME_STATUS gameStatus;
// current difficulty of game
DIFFICULTY gameDifficulty;

// check whether the sound is mute
bool isMute;

// dark mode or light mode
MODE mode;

// render win or lose animation
int loseIndex, winIndex, numLoseAnimation, numWinAnimation;

// hitbox of some features
SDL_Rect newGameRect, quitRect, flagRect, timeRect, loudSpeakerButton, exitButton, darkMode, lightMode, easyRect, mediumRect, hardRect, winTimeRect, bestRect;

// control the time of game
Uint32 startTime, prevTime, bestTime;

Uint32 getCurrentTime();
void getBestTime();
void updateBestTime(Uint32 currentTime);

void setupGame() {
    SCREEN_WIDTH = 1920;
    SCREEN_HEIGHT = 1080;

    gameStatus = STARTING;

    newGameRect = {865, 465, 275, 175};
    quitRect = {870, 800, 280, 195};

    isMute = 0;
    mode = LIGHT;

    numLoseAnimation = 45; numWinAnimation = 62;
}

// setup properties of game for each DIFFICULTY
void setupParameter(DIFFICULTY statusType) {
    if (statusType == EASY) {
        BOARD_WIDTH = 10;
        BOARD_HEIGHT = 10;
        CURRENT_FLAGS = 10;
        CELL_SIZE = 56;

        X = 720;
        Y = 228;

        flagRect = {625, 550, 50, 50};
        timeRect = {610, 445, 80, 60};

        loudSpeakerButton = {618, 673, 75, 45};
        exitButton = {615, 755, 75, 50};

        darkMode = {620, 297, 72, 43};
        lightMode = {620, 250, 72, 43};

        easyRect = {1340, 203, 150, 130};
        mediumRect = {1340, 410, 160, 120};
        hardRect = {1345, 605, 165, 120};

        winTimeRect = {1010, 605, 80, 27};
        bestRect = {1010, 655, 80, 27};
    }
    else if (statusType == MEDIUM) {
        BOARD_WIDTH = 16;
        BOARD_HEIGHT = 16;
        CURRENT_FLAGS = 40;
        CELL_SIZE = 45;

        X = 562;
        Y = 165;

        flagRect = {445, 585, 55, 60};
        timeRect = {425, 450, 100, 70};

        loudSpeakerButton = {435, 740, 80, 50};
        exitButton = {435, 845, 80, 50};

        darkMode = {435, 259, 90, 58};
        lightMode = {435, 200, 90, 58};
        
        easyRect = {1340, 140, 208, 160};
        mediumRect = {1350, 395, 208, 160};
        hardRect = {1360, 645, 208, 160};

        winTimeRect = {935, 652, 100, 30};
        bestRect = {935, 717, 100, 30};
    }
    else if (statusType == HARD) {
        BOARD_WIDTH = 22;
        BOARD_HEIGHT = 22;
        CURRENT_FLAGS = 99;
        CELL_SIZE = 40;

        X = 475;
        Y = 115;

        flagRect = {335, 620, 60, 80};
        timeRect = {305, 465, 120, 80};

        loudSpeakerButton = {315, 810, 105, 70};
        exitButton = {315, 940, 105, 70};

        darkMode = {320, 230, 105, 65};
        lightMode = {320, 160, 105, 65};

        easyRect = {1430, 85, 250, 190};
        mediumRect = {1440, 398, 240, 200};
        hardRect = {1460, 715, 230, 170};

        winTimeRect = {935, 710, 100, 35};
        bestRect = {935, 792, 100, 35};
    }

    gameStatus = RUNNING;
    gameDifficulty = statusType;

    loseIndex = winIndex = -1;

    startTime = -1;
    prevTime = 0;
    getBestTime();
}

Uint32 getCurrentTime() {
    Uint32 currentTime;

    if (startTime == -1) currentTime = 0;
    else if (gameStatus == RUNNING) {
        currentTime = (SDL_GetTicks() - startTime) /1000;
        prevTime = currentTime;
    }
    else currentTime = prevTime;

    return currentTime;
}

void getBestTime() {
    string path;
    if (gameDifficulty == EASY) path = "easy";
    else if (gameDifficulty == MEDIUM) path = "medium";
    else if (gameDifficulty == HARD) path = "hard";

    path = "Data/" + path + "BestTime.txt";

    ifstream file(path.c_str());
    file >> bestTime;
}

void updateBestTime() {
    string path;
    if (gameDifficulty == EASY) path = "easy";
    else if (gameDifficulty == MEDIUM) path = "medium";
    else if (gameDifficulty == HARD) path = "hard";

    path = "Data/" + path + "BestTime.txt";

    ofstream file(path.c_str());
    file << bestTime;
}