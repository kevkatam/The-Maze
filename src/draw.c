#include "../headers/maze.h"
/**
 * drawap - function that draws a map
 * @init: SDL instance
 * Return: nothing
 */
void drawmap(SDL_t init)
{
	int i, j;
	SDL_Rect rec;

	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
		{
			if (getmap(j, i, 0) > 0)
				SDL_SetRenderDrawColor(init.rend,
						139, 69, 19, 255);
			else
				SDL_SetRenderDrawColor(init.rend,
						64, 64, 64, 255);
			rec.x = (j * map_size * SCALE) + 1;
			rec.y = (i * map_size * SCALE) + 1;
			rec.w = (map_size * SCALE) - 1;
			rec.h = (map_size * SCALE) - 1;
			SDL_RenderFillRect(init.rend, &rec);
		}
	}
}
