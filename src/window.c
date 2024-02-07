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
		fprintf(stderr, "Unable to initialize SDL: %s\n",
		       SDL_GetError());
		return (1);
	}
	init->wind = SDL_CreateWindow("The Maze", 0, 0, ScreenWidth,
			ScreenHeight, SDL_WINDOW_OPENGL);
	if (init->wind == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow ERROR: %s\n", SDL_GetError());
		return (1);
	}

	init->rend = SDL_CreateRenderer(init->wind, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (init->rend == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
				SDL_GetError());
		SDL_Quit();
		return (1);
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Failed to initialize SDL_image.\n");
		return (1);
	}
	return (0);
}
/**
 * fix_angle - resets angle if above range
 * @angle: angle given
 * Return: angle reset
 */
float fix_angle(float angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
