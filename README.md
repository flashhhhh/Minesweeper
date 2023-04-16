# Minesweeper
---

## Introduction
---
A game project made with SDL2 C++.
Watch game's demo: 

## Technologies
---
**Project uses:**
+ Visual Studio Code (VSCode).
+ SDL2 devel 2.0.20 mingw.
+ SDL2 image devel 2.0.5 mingw.
+ SDL2 ttf devel 2.0.18 mingw.
+ SDL2 mixer devel 2.0.4 mingw.

## How to compile and play
---
- **Linux**:
  - Clone this repository to your computer.
  - Open command line inside the cloned folder, cd to folder Source.
  - Type: g++ main.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main  (or "make all" instead)
  - main file will be generated. Open the file to run the game (Double click or run ./main in the cmd).
- **Window**: (Will be updated soon).

## Contents
---
#### How to play
You got a rectangle board which has some cells containing bomb. You must find out all of the bomb cells in the board by clearing all of the non-bomb cells.

#### Control and Feature
This game just needs only mouse to play. Here are some types of object in this game:
- A cell of board:
   * If you left-click, the game'll be over and you'll be lose if this cell containing bomb. Otherwise, a number'll be display which meaning the number of neighbor cells that containing bomb (2 cells will be called neighbor if they share at least 1 common point). If the number of neighbor cells is zero, it will display nothing.
   * In case you doubt this cell containing bomb, you can right-click and it'll be flagged. When a cell is flagged, you can't left-click to it any more. You can right-click again to unflag.
- Difficulty: This game has 3 difficulties:
    * Easy: You will solve a $10 * 10$ board and $10$ flags.
    * Medium: You will solve a $16*16$ board and $40$ flags.
    * Hard: You will solve a $22*22$ board and $99$ flags.

And here are some types of feature in this game:
- Mode: There are 2 types of game mode: Dark Mode and Light Mode.
- Sound: If you left-click to the sound button, the game'll be mute. Left-click again to unmute.
- Quit: If you left-click to the quit button, you will be out of the game.

#### Note
- The number of flags is equal to the number of bombs, but you don't need to use all of the flags to win. You'll win if you clear all of the non-bomb cells.
- The game is NOT guarented for you to win. You may need some luckiness to win this game ahihi @@
- However, the first left-click is always safe. It means that the first cell you left-clicking can't contain bomb. Moreover, it will create a large area that doesn't contain bomb (Play game or watch game's demo to understand more clearly).

## Algorithm
---
- When you left-click to a zero-cell (a cell doesn't have any neighbor cell containing bomb), you must flood fill to all of the neighbor cell of it and so on. Use BFS to do it.
- The algorithm is similar in your first left-clicking to create a non-bomb cell area. Just BFS colaborates with probability.