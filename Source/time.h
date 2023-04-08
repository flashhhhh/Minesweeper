Uint32 startTime;

// render current time
void printCurrentTime() {
    gallery.loadImage("../Image/clock.png");
    gallery.render(BOARD_WIDTH * CELL_SIZE + 75, SCREEN_HEIGHT * 20 /100, 125, SCREEN_HEIGHT * 15 /100);

    string timeText;
    SDL_Color color;
    Uint32 currentTime = (SDL_GetTicks() - startTime) /1000;

    timeText = changeNumberToString(currentTime);
    color = {0, 0, 0};

    gallery.loadFromRenderedText(timeText, color);
    gallery.render(BOARD_WIDTH * CELL_SIZE + 225, SCREEN_HEIGHT * 20 /100, 75, SCREEN_HEIGHT * 15 /100);
}