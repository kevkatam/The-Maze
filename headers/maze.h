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
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


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
void freetoks(char **toks);
void freecols(char ***cols);
void freemap(int **map);
int **getaltitude(char **argv);
char **strsplit(char *str, char *d);


















#endif
