int xChange[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int yChange[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct cell {
    bool isBomb, isFlag, isShowed, isZero, canBeBomb, isFlood;
    int numAdjBombs, numAnimation;

    cell() {
        isBomb = isFlag = isShowed = isZero = isFlood = 0; canBeBomb = 1;
        numAdjBombs = numAnimation = 0;
    }
};

class BOARD {
    private:
        int numRows, numCols, numNonBombCells;
        int xFirstLeftClick, yFirstLeftClick;
        vector<vector<cell> > bombBoard;
    
    public:
        void initBoard();
        void initBoard(int statusType);
        void updateFirstLeftClick(int numRow, int numCol);
        void generateBoard();
        int leftClickCell(int numRow, int numCol);
        int rightClickCell(int numRow, int numCol);
        void printBoard();
    
    protected:
};

void BOARD::initBoard() {
    numRows = numCols = 0;
}

void BOARD::initBoard(int statusType) {
    numRows = BOARD_WIDTH;
    numCols = BOARD_HEIGHT;

    numNonBombCells = numRows * numCols - CURRENT_FLAGS;
    xFirstLeftClick = -1; yFirstLeftClick = 0;

    bombBoard.clear(); bombBoard.resize(numRows);
    for (int numRow = 0; numRow < numRows; ++numRow) bombBoard[numRow].resize(numCols);
}

// Save if (numRow, numCol) is the first-left click
void BOARD::updateFirstLeftClick(int numRow, int numCol) {
    if (xFirstLeftClick == -1 && yFirstLeftClick == 0) {
        xFirstLeftClick = numRow;
        yFirstLeftClick = numCol;
    }
}

void BOARD::generateBoard() {
    // If not the first-left click
    if (xFirstLeftClick == -1 || yFirstLeftClick == -1) return;

    int numCells;
    queue<pair<int,int> > mq;

    if (gameDifficulty == EASY) numCells = 0;
    else if (gameDifficulty == MEDIUM) numCells = Rand(10, 15);
    else if (gameDifficulty == HARD) numCells = Rand(25, 35);

    bombBoard[xFirstLeftClick][yFirstLeftClick].canBeBomb = 0; mq.emplace(xFirstLeftClick, yFirstLeftClick);

    while (!mq.empty()) {
        auto [curRow, curCol] = mq.front(); mq.pop();

        for (int e = 0; e < 8; ++e) {
            int newRow = curRow + xChange[e]; int newCol = curCol + yChange[e];

            if (newRow < 0 || newRow >= numRows || newCol < 0 || newCol >= numCols || !bombBoard[newRow][newCol].canBeBomb || numCells == 0 || Rand(0,99) < 25)
                continue;

            --numCells;
            bombBoard[newRow][newCol].canBeBomb = 0;
            mq.emplace(newRow, newCol);
        }
    }

    for (int numFlag = 0; numFlag < CURRENT_FLAGS; ++numFlag) {
        int numRow, numCol;

        do {
            numRow = rand() %numRows;
            numCol = rand() %numCols;
        }
        while (bombBoard[numRow][numCol].isBomb || !bombBoard[numRow][numCol].canBeBomb);

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
    
    xFirstLeftClick = 0; yFirstLeftClick = -1;

    // startTime starts at this moment
    startTime = SDL_GetTicks();
}

int BOARD::leftClickCell(int numRow, int numCol) {
    if (bombBoard[numRow][numCol].isFlag || bombBoard[numRow][numCol].isShowed) return 0;
    if (bombBoard[numRow][numCol].isBomb) {
        gameStatus = LOSE;
        return 0;
    }

    bombBoard[numRow][numCol].isFlood = 1;

    queue<pair<int,int> > myQueue;
    myQueue.emplace(numRow, numCol);

    int numShowedCell = 0;

    while (!myQueue.empty()) {
        auto [curRow, curCol] = myQueue.front(); myQueue.pop();
        
        if (!bombBoard[curRow][curCol].isFlag) {
            bombBoard[curRow][curCol].isShowed = 1;
            --numNonBombCells;

            ++numShowedCell;
        }

        if (!bombBoard[curRow][curCol].isZero) continue;

        for (int e = 0; e < 8; ++e) {
            int newRow = curRow + xChange[e]; int newCol = curCol + yChange[e];
            if (newRow < 0 || newRow >= numRows || newCol < 0 || newCol >= numCols || bombBoard[newRow][newCol].isFlood) continue;
            
            bombBoard[newRow][newCol].isFlood = 1;
            myQueue.emplace(newRow, newCol);
        }
    }

    if (numNonBombCells == 0) gameStatus = WIN;
    return numShowedCell;
}

int BOARD::rightClickCell(int numRow, int numCol) {
    if (bombBoard[numRow][numCol].isShowed) return -1;

    if (bombBoard[numRow][numCol].isFlag) {
        bombBoard[numRow][numCol].isFlag = 0;
        ++CURRENT_FLAGS;

        return 0;
    }
    else if (CURRENT_FLAGS > 0) {
        bombBoard[numRow][numCol].isFlag = 1;
        --CURRENT_FLAGS;

        return 1;
    }
}

void BOARD::printBoard() {
    // print background
    for (int numRow = 0; numRow < numRows; ++numRow)
        for (int numCol = 0; numCol < numCols; ++numCol) 
            if (mode == LIGHT) gallery.render(LIGHT_MODE_CELL, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        else if (mode == DARK) gallery.render(DARK_MODE_CELL, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);

    // print cells
    for (int numRow = 0; numRow < numRows; ++numRow)
        for (int numCol = 0; numCol < numCols; ++numCol) {
            if (bombBoard[numRow][numCol].isFlag) {
                //gallery.loadImage("../Image/flag.png");
                if (mode == DARK) gallery.render(DARK_FLAG, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                else gallery.render(LIGHT_FLAG, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
            else if (bombBoard[numRow][numCol].isShowed) {
                if (!bombBoard[numRow][numCol].isZero) {
                    textureName name = changeNumberToTextureName(bombBoard[numRow][numCol].numAdjBombs);
                    gallery.render(name, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
                else {
                    if (mode == DARK) gallery.render(DARK_ZERO_CELL, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    else gallery.render(LIGHT_ZERO_CELL, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
            }
            else if (gameStatus == LOSE && bombBoard[numRow][numCol].isBomb) {
                if (mode == DARK) gallery.render(DARK_BOMB, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                else gallery.render(LIGHT_BOMB, X + numRow * CELL_SIZE, Y + numCol * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
}