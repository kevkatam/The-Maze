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
	launch();

	if (argc > 1)
		makemap(argv);
	while (1)
	{
		SDL_SetRenderDrawColor(init.rend, 255, 255, 255, 0);
		SDL_RenderClear(init.rend);

		if (control_events(init) == 1)
			break;

		present(init);
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
	raycast(init);
	drawmap(init);
}
/**
 * launch - function to launch the game
 * Return: no return
 */
void launch(void)
{
	gamer.x = 150;
	gamer.y = 400;
	gamer.w = 12;
	gamer.h = 15;
	gamer.a = PI2;
	gamer.dx = cos(gamer.a) * 5;
	gamer.dy = sin(gamer.a) * 5;
}
