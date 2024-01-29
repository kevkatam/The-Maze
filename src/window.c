#include "../headers/maze.h"
/**
* init_window - initializes the window displaying the maze
* @init: a given instance
* Return: 0 success 1 on failure
*/
int init_window(SDL_t *init)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprint(stderr, "Unable to initialize SDL: %s\n",
		       SDL_GetError());
		return (1);
	}
	init->wind = SDL_CreateWindow("The Maze", 0, 0, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (init->wind == NULL)
	{
		fprint(stderr, "SDL_CreateWindow ERROR: %s\n", SDL_GetError());
		return (1);
	}
