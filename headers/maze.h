#ifndef MAZE_H
#define MAZE_H

#define ScreenWidth 1280 
#define ScreenHeight 768 
#define map_w 10
#define map_h 10
#define map_size 100
#define SCALE 0.25
#define PI1 (0.5 * M_PI)
#define PI2 (1.5 * M_PI)
#define RAD 0.0174533
#define WeaponScale 0.4
#define NumEnemy 1 
#define numrays 100
#define FOV (M_PI / 3)

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>


/**
* struct SDL_Instance - structure for an instance of SDL
* @wind: SDL window
* @rend: surface to draw
*
* Description:struct to create window and surface
*/
typedef struct SDL_Instance
{
	SDL_Window *wind;
	SDL_Renderer *rend;
} SDL_t;

/**
 * struct gamer - struct for the gamer
 * @x: x coordinate position
 * @y: y coordinate position
 * @w: gamer width
 * @h: gamer height
 * @a: gamer angle
 * @dx: change in x of player
 * @dy: change in y of player
 */
typedef struct gamer
{
	float x, y, w, h, a, dx, dy;
} gamer_t;

extern gamer_t gamer;
/**
 * struct - enemis - structure for enemies
 * @x: x coordinate of the enemy, horizontal position
 * @y: y coordinate of the enemy, vertical location
 * @z: z coordinate of the enemy
 * @p: path to the enemy image
 */
typedef struct enemies
{
	float x, y, z;
	char *p;
} enemy_t;
extern enemy_t enemy;
extern float buf[numrays];


/**
 * struct event_keys - structure for event keys
 * @w: up key
 * @a: down key
 * @d: right key
 * @a: left key
 * @e: open door
 * @x: exit
 * @s: down key
 * Description: structure to handle movements and camera rotation
 */
typedef struct event_keys
{
	int w, a, d, s, e, x;
} keys_t;


int init_window(SDL_t *init);
float fix_angle(float angle);
void launch(void);
void show_gamer(SDL_t init);
int getmap(int w, int h, int mt);
void setmap(int w, int h, int value);
void makemap(char **argv);
void freetoks(char **toks);
void freecols(char ***cols);
void freemap(int **map);
int **getaltitude(char **argv);
char **strsplit(char *str, char *d);
void present(SDL_t init);
void drawmap(SDL_t init);
void drawfloor(SDL_t init,float li_of, int indx, float li, float ra);
void draw_sc(SDL_t init, int rn, float wh, float ra, float sh, float rx,
		                float ry, int mtxr);
void drawceiling(SDL_t init, float li_of, int indx, float li, float ra);
int hitwall(float r_x, float r_y);
float find_d(float ix, float iy, float jx, float jy);
void vertical_clash(float ra, float *v_d, float *v_x, float *v_y, int *v_mtx);
void horizontal_clash(float ra, float *h_d, float *h_x, float *h_y,
		int *h_mtx);
void raycast(SDL_t init);
void keyup(SDL_Event evn);
void keydown(SDL_Event evn);
void control_door(void);
void control_keydown(SDL_t init);
int control_events(SDL_t init);
float gettexture(int idx);
void drawweapon(SDL_t init);
void drawenemy(SDL_t init);
float fdv(void);
void enemymap(SDL_t init);


















#endif
