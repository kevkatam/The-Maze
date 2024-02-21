#include "../headers/maze.h"
/**
 * drawweapon - function that draws the weapon
 * @init: sdl2 instance
 * Return: no return
 */
void drawweapon(SDL_t init)
{
	/** sdl2 variables, width and height **/
	SDL_Texture *tx = NULL;
	SDL_Rect shooter;
	int w, h;
	SDL_Surface *s = IMG_Load("images/weapon.png");

	/** if image is present **/
	if (s)
	{
		/** remove background white color **/
		SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
		/** create texture **/
		tx = SDL_CreateTextureFromSurface(init.rend, s);
		/** query tx to find width and height of image **/
		SDL_QueryTexture(tx, NULL, NULL, &w, &h);
		shooter.w = w * WeaponScale;
		shooter.h = h * WeaponScale;
		shooter.x = (ScreenWidth - shooter.w) / 2;
		shooter.y = (ScreenHeight - shooter.h) + 20;

		/** draw the weapon with above features **/
		if (tx)
			SDL_RenderCopy(init.rend, tx, NULL, &shooter);
		else
			printf("failed to create texture\n");
		
		/** free and destroy surface **/
		SDL_FreeSurface(s);
		SDL_DestroyTexture(tx);
	}
	else
		printf("failed to create surface\n");
}
enemy_t enemies[NumEnemy] = {
	{750, 360, 5, "images/enemy.png"},
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

	/** for each enemy **/
	for (i = 0; i < NumEnemy; i++)
	{
		/** load the enemy image **/
		SDL_Surface *s = IMG_Load(enemies[i].p);

		/** if image is present **/
		if (s)
		{
			/** remove background color **/
			SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
			tx = SDL_CreateTextureFromSurface(init.rend, s);
			SDL_QueryTexture(tx, NULL, NULL, &w, &h);
			
			/** distance between player and enemy **/
			dx = enemies[i].x - gamer.x;
			dy = enemies[i].y - gamer.y;
			ds = sqrt(dx * dx + dy * dy);
			/** angle and enemy distance relative to the player **/
			ea = atan2(dy, dx) - gamer.a;
			ed = cos(ea) * ds;

			/** get depth of field **/
			DOF = fdv();
			es = map_size * DOF / ed;
			sx = tan(ea) * DOF;

			/** get screen position of the enemy **/
			enm.x = (ScreenWidth / 2) + sx - (es / 2);
			ex = ed / 4;
			enm.y = (ScreenHeight - es) / 2.0f;
			enm.w = es - 200;
			enm.h = es - 20;
			/** if enemy is not far from the player **/
			if (tx && ex > 0 && ex < numrays && enm.y < buf[(int)ex])
				SDL_RenderCopy(init.rend, tx, NULL, &enm);
		}
		else
			printf("image not found\n");
		/** free and destroy surface **/
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
	/** variables **/
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
	/** variables for SDL_Rect instance and enemy corrdinates **/
	SDL_Rect rec;
	float ex, ey;
	int i;

	/** for each enemy **/
	for (i = 0; i < NumEnemy; i++)
	{
		/** normalize enemy position relative to the map **/
		ex = enemies[i].x * SCALE;
		ey = enemies[i].y * SCALE;
		rec.x = ex - 2;
		rec.y = ey - 2;
		rec.w = 5;
		rec.h = 5;
		/** draw the map **/

		SDL_SetRenderDrawColor(init.rend, 0, 255, 255, 0);
		SDL_RenderFillRect(init.rend, &rec);
	}
}
