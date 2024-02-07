#ifndef MAZE_H
#define MAZE_H

#define ScreenWidth 640
#define ScreenHeight 480
#define map_w 10
#define map_h 10
#define map_size 100
#define SCALE 0.5
#define PI1 (0.5 * M_PI)
#define PI2 (1.5 * M_PI)
#define RAD 0.0174533
#define numrays 60

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


int init_window(SDL_t *init);
float fix_angle(float angle);
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
int hitwall(float r_x, float r_y);
float find_d(float ix, float iy, float jx, float jy);
void vertical_clash(float ra, float *v_d, float *v_x, float *v_y, int *v_mtx);
void horizontal_clash(float ra, float *h_d, float *h_x, float *h_y,
		int *h_mtx);
void raycast(SDL_t init);


















#endif
