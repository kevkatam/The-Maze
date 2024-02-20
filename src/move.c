#include "../headers/maze.h"
keys_t key;
gamer_t gamer;
/**
 * keyup - function that handles key up event
 * @evn: given event
 * Return: no return
 */
void keyup(SDL_Event evn)
{
	/** when left arrow key or A is pressed **/
	if (evn.key.keysym.sym == SDLK_LEFT || evn.key.keysym.sym == SDLK_a)
		key.a = 0;
	/** when right or D is pressed **/
	if (evn.key.keysym.sym == SDLK_RIGHT || evn.key.keysym.sym == SDLK_d)
		key.d = 0;
	/** when up or W key is pressed **/
	if (evn.key.keysym.sym == SDLK_UP || evn.key.keysym.sym == SDLK_w)
		key.w = 0;
	/** when down or S key is pressed **/
	if (evn.key.keysym.sym == SDLK_DOWN || evn.key.keysym.sym == SDLK_s)
		key.s = 0;
	/** when E key is pressed **/
	if (evn.key.keysym.sym == SDLK_e)
		key.e = 0;
	/** when escape or X key is pressed **/
	if (evn.key.keysym.sym == SDLK_ESCAPE)
		key.x = 0;
}
/**
 * keydown - function that handles the key down event
 * @evn: given event
 * Return: no return
 */
void keydown(SDL_Event evn)
{
	/** when up arrow key or W is pressed **/
	if (evn.key.keysym.sym == SDLK_UP || evn.key.keysym.sym == SDLK_w)
		key.w = 1;
	/** when left arrow key or A is pressed **/
	if (evn.key.keysym.sym == SDLK_LEFT || evn.key.keysym.sym == SDLK_a)
		key.a = 1;
	/** when down or S key is pressed **/
	if (evn.key.keysym.sym == SDLK_DOWN || evn.key.keysym.sym == SDLK_s)
		key.s = 1;
	/** when right or D is pressed **/
	if (evn.key.keysym.sym == SDLK_RIGHT || evn.key.keysym.sym == SDLK_d)
		key.d = 1;
	/** when E key is pressed **/
	if (evn.key.keysym.sym == SDLK_e)
		key.e = 1;
	/** when escape or X key is pressed **/
	if (evn.key.keysym.sym == SDLK_ESCAPE)
		key.x = 1;
}
/**
 * control_door - function that controls the door activity
 * Return: no return
 */
void control_door(void)
{
	int px_of, py_of, x, y;

	x = (gamer.dx < 0) ? -30 : 30;
	y = (gamer.dy < 0) ? -50 : 50;
	px_of = (gamer.x + x) / map_size;
	py_of = (gamer.y + y) / map_size;

	/** if the player is near the door **/
	if (getmap(px_of, py_of, 0) == 4)
		setmap(px_of, py_of, 0);
}
/**
 * control_keydown - function that controls when key is pressed down
 * @init: SDL2 instance
 * Return: no return
 */
void control_keydown(SDL_t init)
{
	int ix, iy, gx = gamer.x / map_size, gy = gamer.y / map_size, x = 0,
	    y = 0;


	x = (gamer.dx < 0) ? -20 : 20, y = (gamer.dy < 0) ? -20 : 20;
	/** when A is pressed **/
	if (key.a == 1)
	{
		gamer.a -= 0.1, gamer.a = fix_angle(gamer.a);
		gamer.dx = cos(gamer.a) * 5, gamer.dy = sin(gamer.a) * 5;
	}
	/** when D is pressed **/
	else if (key.d == 1)
	{
		gamer.a += 0.1, gamer.a = fix_angle(gamer.a);
		gamer.dx = cos(gamer.a) * 5, gamer.dy = sin(gamer.a) * 5;
	}
	/** when W is pressed **/
	else if (key.w == 1)
	{
		ix = ((gamer.dx * 5) + gamer.x + x) / map_size;
		iy = ((gamer.dy * 5) + gamer.y + y) / map_size;
		if (getmap(ix, gy, 0) == 0)
			gamer.x += gamer.dx * 2;
		if (getmap(gx, iy, 0) == 0)
			gamer.y += gamer.dy * 2;
	}
	/** when S is pressed **/
	else if (key.s == 1)
	{
		ix = ((gamer.x - (gamer.dx * 5)) - x) / map_size;
		iy = ((gamer.y - (gamer.dy * 5)) - y) / map_size;
		if (getmap(ix, gy, 0) == 0)
			gamer.x -= gamer.dx * 2;
		if (getmap(gx, iy, 0) == 0)
			gamer.y -= gamer.dy * 2;
	}
	else if (key.e == 1)
		control_door();
	/** set drawing colors and draw **/
	SDL_SetRenderDrawColor(init.rend, 80, 80, 80, 0);
	SDL_RenderClear(init.rend);
	present(init);
	SDL_RenderPresent(init.rend);
}

/**
 * control_events - function that controls the events
 * @init: SDL instance
 * Return: 0 on success 1 otherwise
 */
int control_events(SDL_t init)
{
	/** SDL_Event instance **/
	SDL_Event evn;

	/** while the escape and quit (X) keys are not pressed **/
	while (SDL_PollEvent(&evn))
	{
		/** when quit is pressed **/
		if (evn.type == SDL_QUIT)
			return (1);
		/** when down key is pressed **/
		else if (evn.type == SDL_KEYDOWN)
		{
			keydown(evn);
			if (key.x == 1)
				return (1);
		}
		/** when up arrow is pressed **/
		else if (evn.type == SDL_KEYUP)
			keyup(evn);
		/** call control_keydown to control key dowa operations **/
		control_keydown(init);
	}
	return (0);
}
