#include "../headers/maze.h"

int map[map_h][map_w] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int floor_map[map_h][map_w] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
 */
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
	freemap(filemap);
}
/**
 * getaltitude - reads altitude from text file
 * @argv: command line arguments
 * Return: altitude
 */
int **getaltitude(char **argv)
{
	int **alt;
	int fd, i, j;
	char buff[1024];
	char **rows, ***cols;


	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		fprintf(stderr, "Error opening a file");
		return (NULL);
	}
	read(fd, buff, 1023);
	close(fd);

	alt = malloc(sizeof(int *) * map_w);
	if (alt == NULL)
		return (NULL);
	for (i = 0; i < map_w; i++)
		alt[i] = malloc(sizeof(int) * map_h);

	rows = strsplit(buff, "\n");

	cols = malloc(sizeof(char **) * map_w);

	for (i = 0; rows[i]; i++)
		cols[i] = strsplit(rows[i], " ");

	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
			alt[i][j] = atoi(cols[i][j]);
	}
	freetoks(rows);
	freecols(cols);
	return (alt);
}
/**
 * strsplit - split a string
 * @str: given string
 * @d: delimeter
 * Return: string array
 */
char **strsplit(char *str, char *d)
{
	char **toks;
	char *tok, *s2;
	int i = 0;
	int toks_size = 2;

	toks = malloc(sizeof(char *) * (toks_size + 1));
	if (!toks)
		return (NULL);
	s2 = strdup(str);
	tok = strtok(s2, d);
	toks_size++;
	while (tok)
	{
		toks[i] = strdup(tok);
		toks = realloc(toks, sizeof(char *) * toks_size);
		tok = strtok(NULL, d);
		i++;
		toks_size++;
	}
	toks[i] = "";
	if (tok)
		free(tok);
	if (s2)
		free(s2);
	return (toks);
}
