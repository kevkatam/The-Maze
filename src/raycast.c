#include "../headers/maze.h"
/**
 * hitwall - function that checks whether the ray hits a wall
 * @r_x: x ray position
 * @r_y: y ray position
 * Return: 1 if ray hits wall 0 otherwise
 */
int hitwall(float r_x, float r_y)
{
	int mx, my, mp;

	if (r_x < 0 || r_x >= map_w * map_size || r_y < 0 ||
			r_y >= map_h * map_size)
		return (-1);
	mx = floor(r_x / map_size);
	my = floor(r_y / map_size);
	mp = my * map_w + mx;

	if (mp > 0 && mp < map_w * map_h && getmap(mx, my, 0) > 0)
		return (getmap(mx, my, 0));
	else
		return (0);
}
/**
 * find_d - finds distance btwn two points
 * @ix: x- coordinate of 1st point
 * @iy: y-coordinate of 1st point
 * @jx: x-coordinate of 2nd point
 * @jy: y-coordinate of 2nd point
 * Return: distance
 */
float find_d(float ix, float iy, float jx, float jy)
{
	float p;

	p = ((jx - ix) * (jx - ix) + (jy - iy) * (jy - iy));

	return (sqrt(p));
}
/**
 * horizontal_clash - function that checks the horizontal collision
 * @ra: ray angle
 * @h_d: ref to horizontal distance
 * @h_x: ref to horizontal x coordinate
 * @h_y: ref to horizontal y coordinate
 * @h_mtx: value of horizontal map texture
 * Return: no return
 */
void horizontal_clash(float ra, float *h_d, float *h_x, float *h_y,
		int *h_mtx)
{
	float rx, ry, xo, yo, tann;
	int dif, val;

	tann = -1 / tan(ra);
	dif = 0;

	if (ra > M_PI)
	{
		ry = (((int)gamer.y >> 6) << 6) - 0.0001;
		rx = ((gamer.y - ry) * tann) + gamer.x;
		yo = -64, xo = -yo * tann;
	}
	else if (ra < M_PI && ra > 0)
	{
		ry = (((int)gamer.y >> 6) << 6) + 100;
		rx = ((gamer.y - ry) * tann) + gamer.x;
		yo = 100, xo = -yo * tann;
	}
	else if (ra == 0 || ra == M_PI)
		rx = gamer.x, ry = gamer.y, dif = 10;
	while (dif < 10)
	{
		val = hitwall(rx, ry);
		if (val != 0)
		{
			dif = 10;
			if (val > 0)
				*h_mtx = val - 1;
		}
		else
			rx += xo, ry += yo, dif += 1;
	}
	*h_x = rx;
	*h_y = ry;
	*h_d = find_d(gamer.x, gamer.y, rx, ry);
}
/**
 * vertical_clash - checks vertical clash
 * @ra: ray angle
 * @v_d: ref to vertical distance
 * @v_x: ref to vertical x-coordinate
 * @v_y: ref to vertical y-coordinate
 * @v_mtx: vertcal map texture
 * Return: no return
 */
void vertical_clash(float ra, float *v_d, float *v_x, float *v_y, int *v_mtx)
{
	float rx, ry, xo, yo, tann;
	int dif, val;

	tann = -tan(ra);
	dif = 0;

	if (ra > PI1 && ra < PI2)
	{
		rx = (((int)gamer.x >> 6) << 6) - 0.0001;
		ry = ((gamer.x - rx) * tann) + gamer.y;
		xo = -64, yo = -xo * tann;
	}
	else if ((ra < PI1 || ra > PI2) && ra)
	{
		rx = (((int)gamer.x >> 6) << 6) + 100;
		ry = ((gamer.x - rx) * tann) + gamer.y;
		xo = 100, yo = -xo * tann;
	}
	else if (ra == 0 || ra == M_PI)
	{
		rx = gamer.x, ry = gamer.y, dif = 10;
	}
	while (dif < 10)
	{
		val = hitwall(rx, ry);
		if (val != 0)
		{
			dif = 10;
			if (val > 0)
				*v_mtx = val - 1;
		}
		else
			rx += xo, ry += yo, dif += 1;
	}
	*v_x = rx;
	*v_y = ry;
	*v_d = find_d(gamer.x, gamer.y, rx, ry);
}
gamer_t gamer;
float buf[numrays];
/**
 * raycast - function that casts a ray to a wall
 * @init: sdl2 instance
 * Return: no return
 */
void raycast(SDL_t init)
{
	float ra, hx, hy, hd = 1000000, sh = 1, px, py, rx, ry;
	float vx, vy, vd = 1000000, dis, r_x, r_y;
	int i, vtx = 0, htx = 0;
	SDL_Rect top, map;

	top.x = 0, top.y = 0, top.w = ScreenWidth, top.h = 400;
	map.x = 0, map.y = 0, map.w = (map_w * (map_size * SCALE));
	map.h = (map_h * (map_size * SCALE));
	SDL_SetRenderDrawColor(init.rend, 135, 206, 235, 255);
	SDL_RenderFillRect(init.rend, &top);

	SDL_SetRenderDrawColor(init.rend, 120, 120, 120, 0);
	SDL_RenderFillRect(init.rend, &map);

	ra = gamer.a - RAD * 30, ra = fix_angle(ra);
	for (i = 0; i < numrays; i++)
	{
		horizontal_clash(ra, &hd, &hx, &hy, &htx);
		vertical_clash(ra, &vd, &vx, &vy, &vtx);

		if (hd < vd)
			r_x = hx, r_y = hy, dis = hd, sh = 1, buf[i] = hd;
		else
		{
			r_x = vx, r_y = vy, dis = vd, sh = 0.5, buf[i] = vd;
			htx = vtx;
		}
		SDL_SetRenderDrawColor(init.rend, 0, 0, 0, 255);
		px = gamer.x * SCALE, py = gamer.y * SCALE;
		rx = r_x * SCALE, ry = r_y * SCALE;
		SDL_RenderDrawLine(init.rend, px, py, rx, ry);
		draw_sc(init, i, dis, ra, sh, r_x, r_y, htx);
		ra += RAD, ra = fix_angle(ra);
	}
}
