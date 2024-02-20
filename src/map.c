#include "../headers/maze.h"

int map[map_h][map_w] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


int floor_map[map_h][map_w] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 0, 1, 1, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
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
	/** if floor map is needed **/
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
	/** sets the map value to argument value **/
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

	/** gets map value from a file **/
	filemap = getaltitude(argv);

	/** updates the value with one parsed from the file **/
	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
			map[i][j] = filemap[i][j];
	}
	/** frees the map **/
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

	/** opens a file **/
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		fprintf(stderr, "Error opening a file");
		return (NULL);
	}
	/** reads the file **/
	read(fd, buff, 1023);
	close(fd);

	/** allocates map memory **/
	alt = malloc(sizeof(int *) * map_w);
	if (alt == NULL)
		return (NULL);
	for (i = 0; i < map_w; i++)
		alt[i] = malloc(sizeof(int) * map_h);

	/** splits the file per line **/
	rows = strsplit(buff, "\n");

	/** allocate row memory **/
	cols = malloc(sizeof(char **) * map_w);

	/** splits row per space **/
	for (i = 0; rows[i]; i++)
		cols[i] = strsplit(rows[i], " ");

	/** converts character to int **/
	for (i = 0; i < map_w; i++)
	{
		for (j = 0; j < map_h; j++)
			alt[i][j] = atoi(cols[i][j]);
	}
	/** frees map and row memories **/
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

	/** allocates token memory **/
	toks = malloc(sizeof(char *) * (toks_size + 1));
	if (!toks)
		return (NULL);
	/** duplicates string **/
	s2 = strdup(str);
	/** splits string based on a delimeter d **/
	tok = strtok(s2, d);
	toks_size++;
	/** while loop upto the string's end **/
	while (tok)
	{
		toks[i] = strdup(tok);
		toks = realloc(toks, sizeof(char *) * toks_size);
		tok = strtok(NULL, d);
		i++;
		toks_size++;
	}
	/** adds string's terminate character **/
	toks[i] = '\0';
	if (tok)
		free(tok);
	if (s2)
		free(s2);
	return (toks);
}
