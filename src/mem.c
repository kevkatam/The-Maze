#include "../headers/maze.h"
/**
 * freetoks - frees memory assigned to tokens
 * @toks: given tokens
 * Return: nothing
 */
void freetoks(char **toks)
{
	char **temp = toks;

	if (toks)
	{
		while (*toks)
			free(*toks++);
		free(temp);
	}
}

/**
 * freecols - free allocated memory for columns
 * @cols: given columns
 * Return: nothing
 */
void freecols(char ***cols)
{
	int i, j;


	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
			free(cols[i][j]);
		free(cols[i]);
	}
	free(cols);
}
/**
 * freemap - free memory allocated for map
 * @map: given map
 * Return: nothing
 */
void freemap(int **map)
{
	int i;


	for (i = 0; i < map_w; i++)
		free(map[i]);
	free(map);
}
