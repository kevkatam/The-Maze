#include "../headers/maze.h"
/**
 * drawweapon - function that draws the weapon
 * @init: sdl2 instance
 * Return: no return
 */
void drawweapon(SDL_t init)
{
	SDL_Texture *tx = NULL;
	SDL_Rect shooter;
	int w, h;
	SDL_Surface *s = IMG_Load("../images/weapon.png");

	if (s)
	{
		SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
		tx = SDL_CreateTextureFromSurface(init.rend, s);
		SDL_QueryTexture(tx, NULL, NULL, &w, &h);
		shooter.w = w * WeaponScale;
		shooter.h = h * WeaponScale;
		shooter.x = (ScreenWidth - shooter.w) / 2;
		shooter.y = (ScreenHeight - shooter.h) + 20;

		if (tx)
			SDL_RenderCopy(init.rend, tx, NULL, &shooter);
		else
			printf("failed to create texture\n");

		SDL_FreeSurface(s);
		SDL_DestroyTexture(tx);
	}
	else
		printf("failed to create surface\n");
}
enemy_t enemies[NumEnemy] = {
	{750, 360, 5, "../images/enemy.png"},
};

/**
 * drawenemy - function that draws th enemies
 * @init: sdl2 instance
 * Return: no return
 */
void drawenemy(SDL_t init)
{
	SDL_Texture *tx = NULL;
	SDL_Rect enm;
	int w, h, i;
	float dx, dy, ds, sx, DOF, ea, ed, es, ex;

	for (i = 0; i < 2; i++)
	{
		SDL_Surface *s = IMG_Load(enemies[i].p);

		if (s)
		{
			SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
			tx = SDL_CreateTextureFromSurface(init.rend, s);
			SDL_QueryTexture(tx, NULL, NULL, &w, &h);

			dx = enemies[i].x - gamer.x;
			dy = enemies[i].y - gamer.y;
			ds = sqrt(dx * dx + dy * dy);

			ea = atan2(dy, dx) - gamer.a;
			ed = cos(ea) * ds;

			DOF = fdv();
			es = map_size * DOF / ed;
			sx = tan(ea) * DOF;

			enm.x = (ScreenWidth / 2) + sx - (es / 2);
			ex = ed / 4;
			enm.y = (ScreenHeight - es) / 2.0f;
			enm.w = es - 200;
			enm.h = es - 20;
			if (tx && ex > 0 && ex < numrays && enm.y < buf[(int)ex])
				SDL_RenderCopy(init.rend, tx, NULL, &enm);
		}
		else
			printf("image not found\n");
		SDL_FreeSurface(s);
		SDL_DestroyTexture(tx);
	}
}
/**
 * fdv - function that finds the view point distance
 * Return: view point distance
 */
float fdv(void)
{
	float s = ScreenWidth / 2, a = FOV / 2;

	return (s / tan(a));
}
/**
 * enemymap - function that draws the enemy map
 * @init: sdl2 instance
 * Return: no return
 */
void enemymap(SDL_t init)
{
	SDL_Rect rec;
	float ex, ey;
	int i;

	for (i = 0; i < NumEnemy; i++)
	{
		ex = enemies[i].x * SCALE;
		ey = enemies[i].y * SCALE;
		rec.x = ex - 2;
		rec.y = ey - 2;
		rec.w = 5;
		rec.h = 5;

		SDL_SetRenderDrawColor(init.rend, 0, 255, 255, 0);
		SDL_RenderFillRect(init.rend, &rec);
	}
}
