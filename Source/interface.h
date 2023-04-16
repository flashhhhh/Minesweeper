// Create options
void createOptions() {
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

void printCurrentDifficulty() {
    drawRectangle(easyRect, 0, 0, 255, 255);
    drawRectangle(mediumRect, 0, 0, 255, 255);
    drawRectangle(hardRect, 0, 0, 255, 255);
}

// render number of CURRENT_FLAG
void printCurrentFlag() {
    string textTexture;
    SDL_Color color;

    textTexture = changeNumberToString(CURRENT_FLAGS);
    if (textTexture.size() == 1) textTexture = '0' + textTexture;
    color = {255, 255, 255};

    gallery.loadText(textTexture, color);
    gallery.render(FREE, &flagRect);

    //drawRectangle(flagRect, 0, 0, 255, 255);
}

// render current time
void printCurrentTime() {
    string timeText;
    SDL_Color color;
    Uint32 currentTime = getCurrentTime();

    int minute = currentTime /60; int second = currentTime % 60;

    string minuteText = changeNumberToString(minute);
    while (minuteText.size() < 2) minuteText = "0" + minuteText;

    string secondText = changeNumberToString(second);
    while (secondText.size() < 2) secondText = "0" + secondText;

    timeText = minuteText + ':' + secondText;
    color = {255, 255, 255};

    gallery.loadText(timeText, color);
    gallery.render(FREE, &timeRect);

    //drawRectangle(timeRect, 0, 0, 255, 255);
}

void printLoudSpeakerButton() {
    drawRectangle(loudSpeakerButton, 0, 0, 255, 255);
}

void printExitButton() {
    drawRectangle(exitButton, 0, 0, 255, 255);
}

void printMode() {
    drawRectangle(darkMode, 0, 0, 255, 255);
    drawRectangle(lightMode, 0, 0, 255, 255);
}

// Print Screen
void printScreen(BOARD *board) {
    printBackground();

    board->printBoard();

    //printCurrentDifficulty();

    printCurrentFlag();
    printCurrentTime();
    //printLoudSpeakerButton();
    //printExitButton();
    //printMode();
}