#include "../headers/maze.h"
/**
 * drawmap - function that draws a map
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
						28, 28, 28, 0);
			else
				SDL_SetRenderDrawColor(init.rend,
						255, 255, 255, 0);
			rec.x = (j * map_size * SCALE) + 1;
			rec.y = (i * map_size * SCALE) + 1;
			rec.w = (map_size * SCALE) - 1;
			rec.h = (map_size * SCALE) - 1;
			SDL_RenderFillRect(init.rend, &rec);
		}
	}
}
/**
 * draw_sc - function to draw the walls
 * @init: SDL instance
 * @rn: ray number
 * @wh: wall height
 * @ra: ray angle
 * @sh: shading value
 * @rx: x coordinate of the ray
 * @ry: y coordinate of the ray
 * @mtxr: map texture
 * Return: no return
 */
void draw_sc(SDL_t init, int rn, float wh, float ra, float sh, float rx,
		float ry, int mtxr)
{
	float li, a = fix_angle(gamer.a - ra), of, tx_y = 0, tx_x, tx_s, c;
	int i, j, s = (int) ScreenWidth / 75, idx;

	wh = wh * cos(a), li = (map_size * 670) / wh, tx_s = 32.0 / (float)li;
	of = 280 - (li / 2);
	if (li > 670)
		li = 670, tx_y = (li - 670) / 2.0;
	tx_y = (tx_y * tx_s) + (mtxr * 32);
	if (sh == 1)
	{
		tx_x = (int) (rx / 2.0) % 32;
		if (ra > M_PI)
			tx_x =  31 - tx_x;
	}
	else
	{
		tx_x = (int) (ry / 2.0) % 32;
		if (ra > PI1 && ra < PI2)
			tx_x = 31 - tx_x;
	}

	for (i = 0; i < li; i++)
	{
		idx = (int)(tx_y) * 32 + (int)tx_x;
		c = (gettexture(idx) * 255) * sh;
		if (mtxr == 0)
			SDL_SetRenderDrawColor(init.rend, c / 4.0, c / 4.0, c, 0);
		else if (mtxr == 1)
			SDL_SetRenderDrawColor(init.rend, c / 4.0, c, c, 0);
		else if (mtxr == 2)
			SDL_SetRenderDrawColor(init.rend, c, c / 4.0, c / 4.0, 0);
		else if (mtxr == 3)
			SDL_SetRenderDrawColor(init.rend, c / 4.0, c, c / 4.0, 0);
		for (j = rn * s; j < (rn * s) + s; j++)
			SDL_RenderDrawPoint(init.rend, j, i + of);
		tx_y += tx_s;
	}
	drawfloor(init, of, rn, li, ra);
	drawceiling(init, of, rn, li, ra);
}
/**
 * drawfloor - function that draws the floor
 * @li_of: offset line
 * @li: vertical line
 * @ra: ray angle
 * @indx: ray index
 * @init: sdl2 instance
 * Return: no return
 */
void drawfloor(SDL_t init, float li_of, int indx, float li, float ra)
{
	int i, j, s = (int) ScreenWidth / 75, idx;
	float dy, fx, pa = gamer.a, tx_x, tx_y, c;

	for (i = li_of + li; i < ScreenHeight; i++)
	{
		dy = i - (520 / 2.0), fx = cos(fix_angle(pa - ra));
		tx_x = gamer.x / 2.0 + cos(ra) * 158 * 32 / dy / fx;
		tx_y = gamer.y / 2.0 - sin(ra) * 158 * 32 / dy / fx;

		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		c = (gettexture(idx) * 255) * 0.7;

		SDL_SetRenderDrawColor(init.rend, c / 2.0, c / 2.0, c / 2.0, 255);
		for (j = indx * s; j < (indx * s) + s; j++)
			SDL_RenderDrawPoint(init.rend, j, i);
	}
}
/**
 * drawceiling - function that draws the ceiling of the maze
 * @init: sdl instance
 * @li_of: line offset
 * @indx: index of each ray
 * @li: vertical line
 * @ra: angle of ray
 * Return: no return
 */
void drawceiling(SDL_t init, float li_of, int indx, float li, float ra)
{
	int i, j;
	float dy, fx, ga = gamer.a, tx_x, tx_y, c, idx;

	for (i = li_of + li; i < li_of; i++)
	{
		dy = (500 / 2.0);
		fx = cos(fix_angle(ga - ra));
		tx_x = gamer.x / 2.0 + cos(ra) * 158 * 32 / dy / fx;
		tx_y = gamer.y / 2.0 - sin(ra) * 158 * 32 / dy / fx;
		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		c = (gettexture(idx) * 255) * 0.7;
		SDL_SetRenderDrawColor(init.rend, c / 2.0, c / 1.2, c / 2.0, 0);
		for (j = indx * 10; j < (indx * 10) + 10; j++)
			SDL_RenderDrawPoint(init.rend, j, 500 - i);
	}
}
/**
 * show_gamer - function to show the gamer's position
 * @init: sdl2 instance
 * Return: no return
 */
void show_gamer(SDL_t init)
{
	SDL_Rect rec;
	float x, y, x1, y1;

	rec.x = gamer.x * SCALE;
	rec.y = gamer.y * SCALE;
	rec.w = gamer.w * SCALE;
	rec.h = gamer.h * SCALE;

	SDL_SetRenderDrawColor(init.rend, 101, 67, 33, 255);
	SDL_RenderFillRect(init.rend, &rec);

	x = gamer.x * SCALE;
	y = gamer.y * SCALE;
	x1 = (gamer.x + gamer.dx * 20) * SCALE;
	y1 = (gamer.y + gamer.dy * 20) * SCALE;
	SDL_RenderDrawLine(init.rend, x, y, x1, y1);
}
