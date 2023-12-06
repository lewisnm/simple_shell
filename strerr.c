#include "dupshell.h"

/**
 * output - prints string to CLI
 * @str: user input string
 *
 * Return: none ad void d_type is returned
 */
void output(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putoutchar(str[m]);
		m++;
	}
}

/**
 * putoutchar - output char to stream 1
 * @y: argument of function; char
 *
 * Return: 1 if success of code execution
 * If err is found, -1 error number appropriately set
 */
int putoutchar(char y)
{
	static int m;
	static char buf[W_BUF_SZ];

	if (y == FLUSH_INDICATOR || m >= W_BUF_SZ)
	{
		write(2, buf, m);
		m = 0;
	}
	if (y != FLUSH_INDICATOR)
		buf[m++] = y;
	return (1);
}

/**
 * writechar - write to file_desc; char y
 * @y: character; argument
 * @file_desc: file_desc being output to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writechar(char y, int file_desc)
{
	static int m;
	static char buf[W_BUF_SZ];

	if (y == FLUSH_INDICATOR || m >= W_BUF_SZ)
	{
		write(file_desc, buf, m);
		m = 0;
	}
	if (y != FLUSH_INDICATOR)
		buf[m++] = y;
	return (1);
}

/**
 * writestr - output char arr of strings
 * @str: user input string
 * @file_desc: file_desc being written to
 *
 * Return: the number of chars put
 */
int writestr(char *str, int file_desc)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += writechar(*str++, file_desc);
	}
	return (m);
}
