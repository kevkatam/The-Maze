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
enemy_t enemies[2] = {
	{429.5, 385, 5, "../images/enemy.png"},
	{79.8, 446.2, 5, "../images/enemy2.png"},
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
			dy = enemies[i].x - gamer.y;
			ds = sqrt(dx * dx + dy * dy);

			ea = atan2(dy, dx) - gamer.a;
			ed = cos(ea) * ds;

			DOF = fdv();
			es = map_size * DOF / ed;
			sx = tan(ea) * DOF;

			enm.x = (ScreenWidth / 2) + sx - (es / 2);
			ex = ed / 4;
			enm.y = (ScreenHeight - es) / 2.0f;
			enm.w = es;
			enm.h = es;
			if (tx && ex > 0 && ex < 2 && enm.y < buf[(int)ex])
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
