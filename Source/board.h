int xChange[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int yChange[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct cell {
    bool isBomb, isFlag, isShowed, isZero;
    int numAdjBombs;

    cell() {
        isBomb = isFlag = isShowed = isZero = 0;
        numAdjBombs = 0;
    }
};

class BOARD {
    private:
        int numRows, numCols, numNonBombCells;
        vector<vector<cell> > bombBoard;
    
    public:
        void generateBoard();
        void initBoard();
        void initBoard(int statusType);
        void leftClickCell(int numRow, int numCol);
        void rightClickCell(int numRow, int numCol);
        void printBoard();
        void printScore();
};

void BOARD::generateBoard() {
    for (int numFlag = 0; numFlag < CURRENT_FLAGS; ++numFlag) {
        int numRow, numCol;

        do {
            numRow = rand() %numRows;
            numCol = rand() %numCols;
        }
        while (bombBoard[numRow][numCol].isBomb);

        bombBoard[numRow][numCol].isBomb = 1;
    }

    for (int numRow = 0; numRow < numRows; ++numRow)
        for (int numCol = 0; numCol < numCols; ++numCol) {
            if (bombBoard[numRow][numCol].isBomb) continue;

            for (int e = 0; e < 8; ++e) {
                int newRow = numRow + xChange[e]; int newCol = numCol + yChange[e];
                if (newRow < 0 || newRow >= numRows || newCol < 0 || newCol >= numCols) continue;

                bombBoard[numRow][numCol].numAdjBombs += bombBoard[newRow][newCol].isBomb;
            }

            if (bombBoard[numRow][numCol].numAdjBombs == 0) bombBoard[numRow][numCol].isZero = 1;
        }
}

void BOARD::initBoard() {
    numRows = numCols = 0;
}

void BOARD::initBoard(int statusType) {
    if (statusType == EASY) {
        numRows = 10;
        numCols = 10;
    }
    else if (statusType == MEDIUM) {
        numRows = 16;
        numCols = 16;
    }
    else if (statusType == HARD) {
        numRows = 24;
        numCols = 20;
    }

    numNonBombCells = numRows * numCols - CURRENT_FLAGS;

    bombBoard.clear(); bombBoard.resize(numRows);
    for (int numRow = 0; numRow < numRows; ++numRow) bombBoard[numRow].resize(numCols);
}

void BOARD::leftClickCell(int numRow, int numCol) {
    if (bombBoard[numRow][numCol].isFlag || bombBoard[numRow][numCol].isShowed) return;
    if (bombBoard[numRow][numCol].isBomb) {
        gameStatus = LOSE;
        return;
    }

    bombBoard[numRow][numCol].isShowed = 1;

    queue<pair<int,int> > myQueue;
    myQueue.emplace(numRow, numCol);

    while (!myQueue.empty()) {
        auto [curRow, curCol] = myQueue.front(); myQueue.pop();
        --numNonBombCells;

        if (!bombBoard[curRow][curCol].isZero) continue;

        for (int e = 0; e < 8; ++e) {
            int newRow = curRow + xChange[e]; int newCol = curCol + yChange[e];
            if (newRow < 0 || newRow >= numRows || newCol < 0 || newCol >= numCols || bombBoard[newRow][newCol].isShowed) continue;

            bombBoard[newRow][newCol].isShowed = 1;
            myQueue.emplace(newRow, newCol);
        }
    }

    if (numNonBombCells == 0) gameStatus = WIN;
}

void BOARD::rightClickCell(int numRow, int numCol) {
    if (bombBoard[numRow][numCol].isShowed) return;

    if (bombBoard[numRow][numCol].isFlag) {
        bombBoard[numRow][numCol].isFlag = 0;
        ++CURRENT_FLAGS;
    }
    else if (CURRENT_FLAGS > 0) {
        bombBoard[numRow][numCol].isFlag = 1;
        --CURRENT_FLAGS;
    }
}

void BOARD::printBoard() {
    // print background
    for (int numRow = 0; numRow < numRows; ++numRow)
        for (int numCol = 0; numCol < numCols; ++numCol)
            if ((numRow + numCol) &1) drawRectangle(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE, 1, 150, 32, 255);
        else drawRectangle(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE, 144, 238, 144, 255);

    // print line
    for (int numCol = 0; numCol <= numCols; ++numCol)
        drawLine(0, numCol * CELL_SIZE, numRows * CELL_SIZE, numCol * CELL_SIZE, 255, 255, 255, 255);
    
    for (int numRow = 0; numRow <= numRows; ++numRow)
        drawLine(numRow * CELL_SIZE, 0, numRow * CELL_SIZE, numCols * CELL_SIZE, 255, 255, 255, 255);
    
    // print cells
    for (int numRow = 0; numRow < numRows; ++numRow)
        for (int numCol = 0; numCol < numCols; ++numCol) {
            if (bombBoard[numRow][numCol].isFlag) {
                gallery.loadFromFile("../Image/flag.png");
                gallery.render(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
            else if (bombBoard[numRow][numCol].isShowed) {
                drawRectangle(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE, 0, 0, 0, 255);

                if (!bombBoard[numRow][numCol].isZero) {
                    string text;
                    SDL_Color textColor;

                    text = changeNumberToString(bombBoard[numRow][numCol].numAdjBombs);

                    if (text == "1") textColor = {0, 0, 255};
                    else if (text == "2") textColor = {0, 255, 0};
                    else if (text == "3") textColor = {255, 0, 0};
                    else if (text == "4") textColor = {128, 0, 128};
                    else if (text == "5") textColor = {128, 0, 0};
                    else if (text == "6") textColor = {64, 224, 208};
                    else if (text == "7") textColor = {128, 128, 128};
                    else if (text == "8") textColor = {255, 255, 255};

                    gallery.loadFromRenderedText(text, textColor);
                    gallery.render(numRow * CELL_SIZE + CELL_SIZE /4, numCol * CELL_SIZE + CELL_SIZE /4, CELL_SIZE /2, CELL_SIZE /2);
                }
            }
            else if (gameStatus == LOSE && bombBoard[numRow][numCol].isBomb) {
                drawRectangle(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE, 0, 0, 0, 255);

                gallery.loadFromFile("../Image/bomb.png");
                gallery.render(numRow * CELL_SIZE, numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
}