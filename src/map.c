#include "../headers/maze.h"

int map[map_w][map_h] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int floor_map[map_w][map_h] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

/**
 * getmap - finds map value at given coordinat
 * @w: x-coordinat
 * @h: y-coordinate
 * @mt: map type
 * Return: value at w, h
 */
int getmap(int w, int h, int mt)
{
	if (mt == 1)
		return (floor_map[h][w]);
	return (map[h][w]);
}
/**
 * setmap - sets value of map at a given coordinate
 * @w: x-coordinate
 * @h: y-coordinate
 * @value: the value to be set
 * Return: nothing
 */
void setmap(int w, int h, int value)
{
	map[h][w] = value;
}
/**
 * makemap - makes map from given file
 * @argv: command line argument array
 * Return: nothing
 *
void makemap(char **argv)
{
	int i, j;
	int **filemap;

	filemap = getaltitude(argv);

	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
			map[i][j] = filemap[i][j];
	}
	free_map(filemap);
}*/
