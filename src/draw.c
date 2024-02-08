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
	int i, j, s = (int) ScreenWidth / 60; /**idx;*/

	wh = wh * cos(a), li = (map_size * 420) / wh, tx_s = 32.0 / (float)li;
	of = 280 - (li / 2);
	if (li > 420)
		li = 420, tx_y = (li - 420) / 2.0;
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
		/**idx = (int)(tx_y) * 32 + (int)tx_x,*/ c = 255; 
		   /** 
		    *c = (get_tx(idx) * 255) * sh;
		    */
		if (mtxr == 0)
			SDL_SetRenderDrawColor(init.rend, c / 2.0, c / 2.0, c, 0);
		else if (mtxr == 1)
			SDL_SetRenderDrawColor(init.rend, c / 2.0, c, c, 0);
		else if (mtxr == 2)
			SDL_SetRenderDrawColor(init.rend, c, c / 2.0, c / 2.0, 0);
		else if (mtxr == 3)
			SDL_SetRenderDrawColor(init.rend, c / 2.0, c, c / 2.0, 0);
		for (j = rn * s; j < (rn * s) + s; j++)
			SDL_RenderDrawPoint(init.rend, j, i + of);
	}
	drawfloor(init, of, rn, li, ra);
}
/**
 * drawfloor - function that draws the floor
 * @li_of: offset line
 * @li: vertical line
 * @ra: ray angle
 * @indx: ray index
 * @init: sdl2 instance
 * @return: no return
 */
void drawfloor(SDL_t init,float li_of, int indx, float li, float ra)
{
	int i, j, s = (int) ScreenWidth / 60, idx;
	float dy, fx, pa = gamer.a, tx_x, tx_y, c;

	for (i = li_of + li; i < ScreenHeight; i++)
	{
		dy = i - (520 / 2.0), fx = cos(fix_angle(pa - ra));
		tx_x = gamer.x / 2.0 + cos(ra) * 158 * 32 / dy / fx;
		tx_y = gamer.y / 2.0 - sin(ra) * 158 * 32 / dy / fx;

		/**idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);*/
		/**
		 *c = (get_tx(idx) * 255) * 0.7;
		 */
		c = 255;

		SDL_SetRenderDrawColor(init.rend, c / 1.5, c / 1.5, c, 0);
		for (j = indx * s; j < (indx * s) + s; j++)
			SDL_RenderDrawPoint(init.rend, j, i);
	}
}
