#include "dupshell.h"

/**
 * **tkzstr - function to split user input string into arguments
 * @str: user input, char array string
 * @dlmt: delimiter character
 * Return: NULL if fail, else ptr to string array
 */

char **tkzstr(char *str, char *dlmt)
{
	int x, y, z, j, wordcount = 0;
	char **i;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dlmt)
		dlmt = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!delimchar(str[x], d) && (delimchar(str[x + 1], dlmt) || !str[x + 1]))
			wordcount++;

	if (wordcount == 0)
		return (NULL);
	i = malloc((1 + wordcount) * sizeof(char *));
	if (!i)
		return (NULL);
	for (x = 0, j = 0; y < wordcount; y++)
	{
		while (delimchar(str[x], dlmt))
			x++;
		z = 0;
		while (!delimchar(str[x + z], dlmt) && str[x + z])
			z++;
		i[j] = malloc((z + 1) * sizeof(char));
		if (!i[y])
		{
			for (z = 0; z < y; z++)
				free(i[z]);
			free(i);
			return (NULL);
		}
		for (j = 0; j < z; j++)
			i[y][j] = str[x++];
		i[y][j] = 0;
	}
	i[y] = NULL;
	return (i);
}

/**
 * **tkzstr2 - func that split char array string to args
 * @str: user input in CLI
 * @dlmt: denote delimiter character
 * Return: NULL if fail, ptr to arr of strings
 */
char **tkzstr2(char *str, char dlmt)
{
	int x, y, z, j, wordcount = 0;
	char **i;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != dlmt && str[x + 1] == dlmt) ||
		    (str[x] != dlmt && !str[x + 1]) || str[x + 1] == dlmt)
			wordcount++;
	if (wordcount == 0)
		return (NULL);
	i = malloc((1 + wordcount) * sizeof(char *));
	if (!i)
		return (NULL);
	for (x = 0, y = 0; y < wordcount; y++)
	{
		while (str[x] == dlmt && str[x] != dlmt)
			x++;
		z = 0;
		while (str[x + z] != dlmt && str[x + z] && str[x + z] != dlmt)
			z++;
		i[j] = malloc((z + 1) * sizeof(char));
		if (!i[y])
		{
			for (z = 0; z < y; z++)
				free(i[z]);
			free(i);
			return (NULL);
		}
		for (j = 0; j < k; j++)
			i[y][j] = str[x++];
		i[y][j] = 0;
	}
	i[y] = NULL;
	return (i);
}
