#include "../headers/maze.h"
/**
 * main - entry point
 * @argc: no of command line arguments
 * @argv: array of command line arguments
 * Return: always success
 */
int main(int argc, char **argv)
{
	/** SDL2 instance variable **/
	SDL_t init;

	/** creates and initialize the window **/
	if (init_window(&init) != 0)
		return (1);

	/** launch the game **/
	launch();

	if (argc > 1)
		makemap(argv);

	/** infinite loop **/
	while (1)
	{
		SDL_SetRenderDrawColor(init.rend, 255, 255, 255, 0);
		SDL_RenderClear(init.rend);

		/** controls the user input keys **/
		if (control_events(init) == 1)
			break;

		/** present the game, by drawing walls, ceiling, floor and 
		  enemies **/
		present(init);
		SDL_RenderPresent(init.rend);

	}
	/** destroys renderer, window and quits the game **/
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
	show_gamer(init);
	drawweapon(init);
	drawenemy(init);
	enemymap(init);
}
/**
 * launch - function to launch the game
 * Return: no return
 */
void launch(void)
{
	/** initial features of the player **/
	gamer.x = ScreenWidth / 2;
	gamer.y = ScreenWidth / 2;
	gamer.w = 1;
	gamer.h = 25;
	gamer.a = PI2;
	gamer.dx = cos(gamer.a) * 5;
	gamer.dy = sin(gamer.a) * 5;
}
