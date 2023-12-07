#include "shell.h"

/**
 * str_cpy - copies a string
 * @loc: the destination
 * @orgn: the source
 *
 * Return: pointer to dest
 */
char *str_cpy(char *loc, char *orgn)
{
	int f = 0;

	if (loc == orgn || orgn == 0)
		return (orgn);
	while (orgn[f])
	{
		loc[f] = orgn[f];
		f++;
	}
	loc[f] = 0;
	return (loc);
}

/**
 * str_dup - duplicates a string
 * @ogStr: str to duplicate
 *
 * Return: ptr to the duplicated string
 */
char *str_dup(const char *ogStr)
{
	int girth = 0;
	char *get;

	if (ogStr == NULL)
		return (NULL);
	while (*ogStr++)
		girth++;
	get = malloc(sizeof(char) * (girth + 1));
	if (!get)
		return (NULL);
	for (girth++; girth--;)
		get[girth] = *--ogStr;
	return (get);
}

/**
 *_puts - prints an input string
 *@wrd: the string to be printed
 *
 * Return: void
 */
void _puts(char *wrd)
{
	int j = 0;

	if (!wrd)
		return;
	while (wrd[j] != '\0')
	{
		_putchar(wrd[j]);
		j++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1 or -1 for an error
 */
int _putchar(char ch)
{
	static int j;
	static char buf[W_BUF_SZ];

	if (ch == FLASH_INDICATOR || J >= W_BUF_SZ)
	{
		write(1, buf, j);
		j = 0;
	}
	if (ch != FLASH_INDICATOR)
		buf[j++] = ch;
	return (1);
}
