void printStartingBackground() {
    gallery.render(START_GAME_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gameStatus = INITIALIZING;
}

void printBackground() {
    if (gameDifficulty == EASY) {
        if (!isMute) gallery.render(EASY_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        else gallery.render(EASY_MUTE_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (gameDifficulty == MEDIUM) {
        if (!isMute) gallery.render(MEDIUM_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        else gallery.render(MEDIUM_MUTE_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (gameDifficulty == HARD) {
        if (!isMute) gallery.render(HARD_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        else gallery.render(HARD_MUTE_BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}

void printCurrentFlag() {
    string textTexture;
    SDL_Color color;

    textTexture = changeNumberToString(CURRENT_FLAGS);
    if (textTexture.size() == 1) textTexture = '0' + textTexture;
    color = {255, 255, 255};

    gallery.loadText(textTexture, color);
    gallery.render(FREE, &flagRect);
}

void printCurrentTime() {
    Uint32 currentTime = getCurrentTime();
    string timeText = changeTime(currentTime);
    SDL_Color color = {255, 255, 255};

    gallery.loadText(timeText, color);
    gallery.render(FREE, &timeRect);
}

void printScreen(BOARD *board) {
    printBackground();
    board->printBoard();
    printCurrentFlag();
    printCurrentTime();
}