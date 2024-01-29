#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>

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














#endif
