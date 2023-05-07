# Minesweeper

---

## Introduction

---

A game project made with SDL2 C++.
Watch game's demo:

## Technologies

**Project uses:**

+ Visual Studio Code (VSCode).
+ SDL2 devel 2.0.20 mingw.
+ SDL2 image devel 2.0.5 mingw.
+ SDL2 ttf devel 2.0.18 mingw.
+ SDL2 mixer devel 2.0.4 mingw.

## How to compile and play

- **Linux**:
  - Turn on your terminal.
  - Set up SDL2 in your computer:
    - Type:
    ```
    sudo apt-cache search libsdl2
    ```
    - Then type:
    ```
    sudo apt-get install libsdl2-dev
    ```
  - Clone this repository to your computer.
  - Cd to the cloned folder (minesweeper).
  - Type:

  ```
  g++ Source/main.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main 
  ```

  - `main` file will be generated. Open the file to run the game (Double click or run ./main in terminal).
- **Window**:

  - Turn on your terminal.
  - Clone this repository to your computer.
  - Cd to the cloned folder (minesweeper).
  - Type:

  ```
  g++ Source/main.cpp -Iinclude -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main
  ```

  - `main.exe` file will be generated. Open the file to run the game (Double click or run "main.exe" in terminal).

## Contents
---

#### How to play

You got a rectangle board which has some cells containing bomb. You must find out all of the bomb cells in the board by clearing all of the non-bomb cells.

![image](https://user-images.githubusercontent.com/111177346/234326087-9b99359b-b88b-4818-ae17-2149b878edda.png)

#### Control and Feature

This game just needs only mouse to play. Here are some types of object in this game:

- A cell of board:
  * If you left-click, the game'll be over and you'll be lose if this cell containing bomb. ![image](https://user-images.githubusercontent.com/111177346/234323337-460f2486-17b3-44b4-bb20-497e3c360f61.png)
    Otherwise, a number will be display which meaning the number of neighbor cells that containing bomb (2 cells will be called neighbor if they share at least 1 common point).
    If the number of neighbor cells containing bomb is zero, it will display nothing.
  * In case you doubt this cell containing bomb, you can right-click and it'll be flagged. ![image](https://user-images.githubusercontent.com/111177346/234323293-3c14865c-7fc4-49f1-811c-ce3c6a062890.png)
    When a cell is flagged, you can't left-click to it any more. You can right-click again to unflag.
- Difficulty: This game has 3 difficulties:
  * Easy: You will solve a $10 * 10$ board and $10$ flags.
  * Medium: You will solve a $16*16$ board and $40$ flags.
  * Hard: You will solve a $22*22$ board and $99$ flags.

And here are some types of feature in this game:

- Mode: There are 2 types of game mode: Dark Mode and Light Mode. ![image](https://user-images.githubusercontent.com/111177346/234321049-53046f00-8e6c-4dff-9804-46ba85b400ec.png)
- Sound: If you left-click to the sound button ![image](https://user-images.githubusercontent.com/111177346/234317715-56121d6f-f58c-4d9b-b36f-c3201f99891d.png), the game'll be mute ![image](https://user-images.githubusercontent.com/111177346/234317647-9f87dfbf-7d66-4a8a-945c-ae762bc6f643.png). Left-click again to unmute.
- Quit: If you left-click to the quit button, you will be out of the game. ![image](https://user-images.githubusercontent.com/111177346/234315517-114754f3-11f2-42c6-ba9e-9979dd683e2c.png)

#### Note

- The number of flags is equal to the number of bombs, but you don't need to use all of the flags to win. You'll win if you clear all of the non-bomb cells.
- The game is NOT guarented for you to win. You may need some luckiness to win this game :((
- However, the first left-click is always safe. It means that the first cell you left-clicking can't contain bomb. Moreover, it will create a large area that doesn't contain bomb (Play game or watch game's demo to understand more clearly).

## Algorithm
---

- When you left-click to a zero-cell (a cell doesn't have any neighbor cell containing bomb), you must flood fill to all of the neighbor cell of it and so on. Use BFS to do it.

* The algorithm is similar in your first left-clicking to create a non-bomb cell area. Just BFS colaborates with probability.
