# The Maze

The maze is a 3D game that uses raycsting to render a 2D map into  a 3D navigable world.

The maze was written in C and SDL2 library. Development was performed using Ubuntu 20.04.6 LTS - gcc (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0

## About SDL2

Simple DirectMedia Layer is a cross-platform development library designed to providelow level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular gamesincluding Valve's award winning catalog and many Humble Bundle games.

## Requirements to Play

- Mac OS
- SDL2 and sdl_image

## Installations

Install SDL2

```bash
sudo apt update

sudo apt install libsdl2-dev 

sudo apt install libsdl2-image-dev 
```


# Play The Game

- Clone the github repo [github repo](https://github.com/kevkatam/The-Maze)

## Compliation

```bash
gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm $(sdl2-config --cflags --libs) -lSDL2_image -o maze
```

## Run

- To move foraward through the game use the W or up arrow key.
- To move backwards use the s key or down arrow key
- To rotate the player sideways use left or right arrow keys or A and D keys

## Flowchart

For a detailed flowchart of the game logic and architecture,please see the [Flowchart](https://drive.google.com/file/d/1SLSFGgfL5cN5p9JzPTIGMhTad82aFTPI/view?usp=sharing)

## Project Demo
To view the 3D Maze demo, please visit [3D Maze Demo](https://youtu.be/Qa1AlJfw2hg)

## Author

[Kevin Kipruto](https://github.com/kevkatam)
