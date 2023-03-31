bool createOptions() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    string difficultyText;
    SDL_Color color = {255, 0, 0};

    // Easy Option
    drawRectangle(450, 125, 150, 75, 0, 0, 255, 255);

    difficultyText = "Easy";
    gallery.loadFromRenderedText(difficultyText, color);
    gallery.render(500, 150, 50, 25);

    // Medium Option
    drawRectangle(450, 250, 150, 75, 0, 0, 255, 255);

    difficultyText = "Medium";
    gallery.loadFromRenderedText(difficultyText, color);
    gallery.render(500, 275, 50, 25);

    // Hard Option
    drawRectangle(450, 375, 150, 75, 0, 0, 255, 255);

    difficultyText = "Hard";
    gallery.loadFromRenderedText(difficultyText, color);
    gallery.render(500, 400, 50, 25);

    SDL_RenderPresent(renderer);
    gameStatus = INITIALIZING;

    return 1;
}

bool checkDifficulty(int x, int y) {
    DIFFICULTY difficulty = UNDEFINED;

    if (insideRectangle(x, y, 450, 125, 150, 75)) difficulty = EASY;
    else if (insideRectangle(x, y, 450, 250, 150, 75)) difficulty = MEDIUM;
    else if (insideRectangle(x, y, 450, 375, 150, 75)) difficulty = HARD;

    if (difficulty == UNDEFINED) return 0;

    setupParameter(difficulty);
    startTime = SDL_GetTicks();
    return 1;
}

bool createDifficulty() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    return 1;
}

void processLose() {
    string text = "Game Over!";
    SDL_Color color = {0, 0, 0};

    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 50, SCREEN_HEIGHT * 45 /100, 300, SCREEN_HEIGHT * 20 /100);

    SDL_Rect playAgainRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 70 /100, 225, SCREEN_HEIGHT * 10 /100};
    drawRectangle(playAgainRect, 0, 0, 255, 255);

    text = "Play Again";
    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 125, SCREEN_HEIGHT * 72 /100, 125, SCREEN_HEIGHT * 6 /100);

    SDL_Rect quitRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 85 /100, 225, SCREEN_HEIGHT * 10 /100};
    drawRectangle(quitRect, 0, 0, 255, 255);

    text = "Quit Game";
    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 125, SCREEN_HEIGHT * 87 /100, 125, SCREEN_HEIGHT * 6 /100);

    gameStatus = WAITING_FOR_PLAYER_RESPONSE;
}

void processWin() {
    string text = "You Win!";
    SDL_Color color = {0, 0, 0};

    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 50, SCREEN_HEIGHT * 45 /100, 300, SCREEN_HEIGHT * 20 /100);

    SDL_Rect playAgainRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 70 /100, 225, SCREEN_HEIGHT * 10 /100};
    drawRectangle(playAgainRect, 0, 0, 255, 255);

    text = "Play Again";
    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 125, SCREEN_HEIGHT * 72 /100, 125, SCREEN_HEIGHT * 6 /100);

    SDL_Rect quitRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 85 /100, 225, SCREEN_HEIGHT * 10 /100};
    drawRectangle(quitRect, 0, 0, 255, 255);

    text = "Quit Game";
    gallery.loadFromRenderedText(text, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 125, SCREEN_HEIGHT * 87 /100, 125, SCREEN_HEIGHT * 6 /100);

    gameStatus = WAITING_FOR_PLAYER_RESPONSE;
}

void getPlayerResponse(int x, int y) {
    SDL_Rect playAgainRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 70 /100, 225, SCREEN_HEIGHT * 10 /100};
    SDL_Rect quitRect = {BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 85 /100, 225, SCREEN_HEIGHT * 10 /100};

    if (insideRectangle(x, y, playAgainRect.x, playAgainRect.y, playAgainRect.w, playAgainRect.h)) gameStatus = OPTIONS;
    else if (insideRectangle(x, y, quitRect.x, quitRect.y, quitRect.w, quitRect.h)) gameStatus = QUIT;
}

void printCurrentFlag() {
    gallery.loadFromFile("../Image/flag.png");
    gallery.render(BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 5 /100, 125, SCREEN_HEIGHT * 15 /100);

    string textTexture;
    SDL_Color color;

    textTexture = changeNumberToString(CURRENT_FLAGS);
    if (textTexture.size() == 1) textTexture = '0' + textTexture;

    color = {0, 0, 0};

    gallery.loadFromRenderedText(textTexture, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 225, SCREEN_HEIGHT * 5 /100, 75, SCREEN_HEIGHT * 15 /100);
}