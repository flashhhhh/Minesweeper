# Minesweeper

### Introduction
A game project made with SDL2 C++.
Watch game's demo: 

### Technologies
Project uses:
+ Visual Studio Code (VSCode).
+ SDL2 devel 2.0.20 mingw.
+ SDL2 image devel 2.0.5 mingw.
+ SDL2 ttf devel 2.0.18 mingw.
+ SDL2 mixer devel 2.0.4 mingw.

### How to compile and play
* Linux:
  * Clone this repository to your computer.
  * Open command line inside the cloned folder, cd to folder Source.
  * Type: g++ main.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main
  * main file will be generated. Open the file to run the game (Double click or run ./main in the cmd).
* Window: (Will be updated soon).

### Contents
##### How to play
You got a rectangle board. Some cells in the board contain bomb but you can't see exactly which cells have bomb. When you left click to a cell in the board:

+ If this cell contains bomb, the game is over and you lose.
+ Otherwise, it will display a number which is the number of neighbor cells that contain bomb (2 cells call neighbor if they share at least 1 common point. So it's easy to see that a cell have at most 8 neighbor cells). If the nubmer of neighbor cells is zero, it will display nothing.

The game has some flags that you can use. The number of flags is equal to the number of bombs. When you right click to a hidden cell, if it's unmarked then it's marked and otherwise. After mark a cell, you lose 1 flag. If a cell is marked, it can't be left click any more.

To win the game, you must clear all of the non-bomb cells. It means that you must left click to all of the cells that don't contain bomb.

The game has 3 difficulties:
+ If difficulty is easy, you will solve a $10 * 10$ board and $10$ flags.
+ If difficulty is medium, you will solve a $16 * 16$ board and $40$ flags.
+ If difficulty is hard, you will solve a $24 * 20$ board and $99$ flags.