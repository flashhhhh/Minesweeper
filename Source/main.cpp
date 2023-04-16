#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#include "screen.h"
#include "gallery.h"
#include "mouse.h"
#include "time.h"
#include "status.h"
#include "board.h"
#include "interface.h"

int main(int argc, char* argv[]) {
    setupGame();
    initEverything();
    createGalleryList();

    srand(time(NULL));

    SDL_Event event; bool quit = false;

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
    Mix_Music* music;
    int numMusics = 4;

    BOARD board;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            button.handleEvent(&event);
        }

        if (gameStatus == OPTIONS) {
            SDL_RenderClear(renderer);

            createOptions();

            SDL_RenderPresent(renderer);
        }
        else if (gameStatus == INITIALIZING) {
            pair<ButtonSprite, SDL_Point> currentMouse = button.processClick();

            if (currentMouse.first != BUTTON_SPRITE_MOUSE_OUT) {
                int x = currentMouse.second.x;
                int y = currentMouse.second.y;

                if (insideRectangle(x, y, quitRect)) quit = true;
                else if (insideRectangle(x, y, newGameRect)) {
                    setupParameter(MEDIUM);                    
                    board.initBoard(gameDifficulty);
                }
            }
        }
        else {
            SDL_RenderClear(renderer);

            printScreen(&board);

            if (gameStatus == LOSE) {
                if (loseIndex == 0) {
                    SDL_Delay(1000);
                    
                    if (!isMute) {
                        string musicName = "../Music/losing.wav";
                        music = Mix_LoadMUS(musicName.c_str());
                        Mix_PlayMusic(music, 0);
                    }
                }

                if (loseIndex >= 0) {
                    string path = changeNumberToString(loseIndex);
                    path = "../Image/losing/losing-" + path + ".png";

                    gallery.loadImage(path);
                    gallery.render(FREE, X, Y, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE);

                    SDL_Delay(10);
                }

                if (loseIndex + 1 < numLoseAnimation) ++loseIndex;
            }
            else if (gameStatus == WIN) {
                if (winIndex == 0) {
                    SDL_Delay(1000);

                    if (!isMute) {
                        string musicName = "../Music/winning.wav";
                        music = Mix_LoadMUS(musicName.c_str());
                        Mix_PlayMusic(music, 0);
                    }
                }

                if (winIndex >= 0) {
                    string path = changeNumberToString(winIndex);
                    path = "../Image/winning/winning-" + path + ".png";

                    gallery.loadImage(path);
                    gallery.render(FREE, X, Y, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE);

                    string text;
                    SDL_Color color = {0, 0, 0};

                    Uint32 currentTime = getCurrentTime();
                    text = changeTime(currentTime);
                    gallery.loadText(text, color);
                    gallery.render(FREE, &winTimeRect);

                    bestTime = min(bestTime, currentTime);
                    text = changeTime(bestTime);
                    gallery.loadText(text, color);
                    gallery.render(FREE, &bestRect);

                    updateBestTime();

                    SDL_Delay(10);
                }

                if (winIndex + 1 < numWinAnimation) ++winIndex;
            }
            
            SDL_RenderPresent(renderer);
            SDL_Delay(10);

            pair<ButtonSprite, SDL_Point> currentMouse = button.processClick();
            int x, y;

            x = currentMouse.second.x; y = currentMouse.second.y;

            if (currentMouse.first == BUTTON_SPRITE_MOUSE_LEFT_DOWN) {
                if (insideRectangle(x, y, exitButton)) quit = true;
                
                if (insideRectangle(x, y, easyRect)) {
                    setupParameter(EASY);
                    board.initBoard(gameDifficulty);
                }
                else if (insideRectangle(x, y, mediumRect)) {
                    setupParameter(MEDIUM);
                    board.initBoard(gameDifficulty);
                }                
                else if (insideRectangle(x, y, hardRect)) {
                    setupParameter(HARD);
                    board.initBoard(gameDifficulty);
                }
                
                if (insideRectangle(x, y, loudSpeakerButton)) {
                    if (isMute == 0) isMute = 1;
                    else isMute = 0;
                }
                
                if (insideRectangle(x, y, darkMode)) mode = DARK;
                else if (insideRectangle(x, y, lightMode)) mode = LIGHT;
            }
            
            if (insideRectangle(currentMouse.second.x, currentMouse.second.y, X, Y, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE)) {
                x = (currentMouse.second.x - X) /CELL_SIZE;
                y = (currentMouse.second.y - Y) /CELL_SIZE;

                if (currentMouse.first == BUTTON_SPRITE_MOUSE_LEFT_DOWN) {
                    board.updateFirstLeftClick(x, y);
                    board.generateBoard();
                    int numShowedCell = board.leftClickCell(x, y);

                    if (!isMute) {
                        string musicName = "../Music/";
                        if (numShowedCell == 1) musicName += "just_one_cell.wav";
                        else if (numShowedCell >= 2 && numShowedCell <= 10) musicName += "quite_large_area.wav";
                        else if (numShowedCell > 10) musicName += "very_large_area.wav";

                        music = Mix_LoadMUS(musicName.c_str());
                        Mix_PlayMusic(music, 0);
                    }
                }
                else if (currentMouse.first == BUTTON_SPRITE_MOUSE_RIGHT_DOWN) {
                    int type = board.rightClickCell(x, y);

                    if (!isMute) {
                        string musicName = "../Music/";
                        if (type == 1) musicName += "flag.wav";
                        else if (type == 0) musicName += "unflag.wav";

                        music = Mix_LoadMUS(musicName.c_str());
                        Mix_PlayMusic(music, 0);
                    }
                }
            }
        }
    }

    closeEverthing();
}