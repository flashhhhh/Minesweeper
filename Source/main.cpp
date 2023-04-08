#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#include "screen.h"
#include "gallery.h"
#include "mouse.h"
#include "status.h"
#include "time.h"
#include "interface.h"
#include "board.h"

int main(int argc, char* argv[]) {
    if (!initEverything()) {
        cout << "Failed to initialize!\n";
        return 0;
    }

    SDL_Event event; bool quit = false;
    srand(time(NULL));

    BOARD board;

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
    Mix_Music* music;

    int numMusics = 4;

    while (!quit) {
        /*if (Mix_PlayingMusic() == 0) {
            string Number; int number = rand() %numMusics + 1;
            stringstream ss;
            ss << number; ss >> Number;

            string musicName = "../Music/music";

            musicName += Number;
            musicName += ".wav";

            cout << number <<" "<< musicName <<'\n';
            music = Mix_LoadMUS(musicName.c_str());
            Mix_PlayMusic(music, 0);
        }*/

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            button.handleEvent(&event);
        }

        if (gameStatus == OPTIONS) {
            createOptions();
        }
        else if (gameStatus == INITIALIZING) {
            pair<ButtonSprite, SDL_Point> currentMouse = button.processClick();

            if (currentMouse.first != BUTTON_SPRITE_MOUSE_OUT) {
                int x = currentMouse.second.x;
                int y = currentMouse.second.y;

                if (checkDifficulty(x, y)) {
                    board.initBoard(gameDifficulty);
                    initDifficulty();
                }
            }
        }
        else if (gameStatus == RUNNING) {
            SDL_SetRenderDrawColor(renderer, 246, 190, 0, 255);
            SDL_RenderClear(renderer);
            
            pair<ButtonSprite, SDL_Point> currentMouse = button.processClick();
            int x, y;

            x = currentMouse.second.x /CELL_SIZE;
            y = currentMouse.second.y /CELL_SIZE;

            if (currentMouse.first == BUTTON_SPRITE_MOUSE_LEFT_DOWN) {
                board.updateFirstLeftClick(x, y);
                board.generateBoard();
                board.leftClickCell(x, y);
            }
            else if (currentMouse.first == BUTTON_SPRITE_MOUSE_RIGHT_DOWN) {
                board.rightClickCell(x, y);
            }

            board.printBoard();
            printCurrentFlag();
            printCurrentTime();

            if (gameStatus == LOSE) {
                processLose();
            }
            else if (gameStatus == WIN) {
                processWin();
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        else if (gameStatus == WAITING_FOR_PLAYER_RESPONSE) {
            pair<ButtonSprite, SDL_Point> currentMouse = button.processClick();

            if (currentMouse.first != BUTTON_SPRITE_MOUSE_OUT) {
                int x = currentMouse.second.x;
                int y = currentMouse.second.y;

                getPlayerResponse(x, y);
            }
        }
        else if (gameStatus == QUIT) quit = true;
    }

    closeEverthing();
}