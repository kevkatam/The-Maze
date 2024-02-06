#include "../headers/maze.h"
/**
 * main - entry point
 * @argc: no of command line arguments
 * @argv: array of command line arguments
 * Return: always success
 */
int main(int argc, char **argv)
{
	SDL_t init;

	if (init_window(&init) != 0)
		return (1);

	if (argc > 1)
		makemap(argv);
	while (1)
	{
		SDL_SetRenderDrawColor(init.rend, 128, 128, 128, 0);
		SDL_RenderClear(init.rend);

		SDL_RenderPresent(init.rend);
	}
	SDL_DestroyRenderer(init.rend);
	SDL_DestroyWindow(init.wind);
	SDL_Quit();
	return (0);
}
/**
 * present - presents the game
 * @init: sdl2 instance
 * Return: no return
 */
void present(SDL_t init)
{
	drawmap(init);
}
