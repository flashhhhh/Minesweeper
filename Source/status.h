enum DIFFICULTY {
    UNDEFINED, EASY, MEDIUM, HARD
};

enum GAME_STATUS {
    OPTIONS, INITIALIZING, RUNNING, LOSE, WIN, WAITING_FOR_PLAYER_RESPONSE, QUIT
};

int BOARD_WIDTH;
int BOARD_HEIGHT;
int CELL_SIZE = 50;

int CURRENT_FLAGS;

// current status of game
GAME_STATUS gameStatus = OPTIONS;
DIFFICULTY gameDifficulty;

void setupParameter(DIFFICULTY statusType) {
    if (statusType == EASY) {
        BOARD_WIDTH = 10;
        BOARD_HEIGHT = 10;
        CURRENT_FLAGS = 10;
    }
    else if (statusType == MEDIUM) {
        BOARD_WIDTH = 16;
        BOARD_HEIGHT = 16;
        CURRENT_FLAGS = 40;
    }
    else if (statusType == HARD) {
        BOARD_WIDTH = 24;
        BOARD_HEIGHT = 20;
        CURRENT_FLAGS = 99;
    }

    SCREEN_WIDTH = BOARD_WIDTH * CELL_SIZE + 400;
    SCREEN_HEIGHT = BOARD_HEIGHT * CELL_SIZE;

    gameStatus = RUNNING;
    gameDifficulty = statusType;
}

