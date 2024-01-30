#ifndef MAZE_H
#define MAZE_H

#define ScreenWidth 640
#define ScreenHeight 480
#define map_w 10
#define map_h 10

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
* struct SDL_Instance - structure for an instance of SDL
* @wind: SDL window
* @rend: surface to draw
*
* Description:struct to create window and surface
*/
typedef struct SDL_Instance
{
	SDL_Window *wind;
	SDL_Renderer *rend;
} SDL_t;

int init_window(SDL_t *init);
int getmap(int w, int h, int mt);
void setmap(int w, int h, int value);
void makemap(char **argv);

















#endif
