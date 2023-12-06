#include "dupshell.h"

/**
 * atoiErr - changes a string to in
 * @k: the string to be converted
 * Return: 0 success
 *       -1 error
 */
int atoiErr(char *k)
{
	int v = 0;
	unsigned long int finding = 0;

	if (*k == '+')
		k++;
	for (v = 0;  s[v] != '\0'; v++)
	{
		if (s[v] >= '0' && k[v] <= '9')
		{
			finding *= 10;
			finding += (k[v] - '0');
			if (finding > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (finding);
}

/**
 * outputErr - outputs error message
 * @systeminfo: the parameter & return info struct
 * @imstr: string with err message
 * Return: 0 if no number, converted number or
 *        -1 on error
 */
void outputErr(system *systeminfo, char *imstr)
{
	output(systeminfo->filename);
	output(": ");
	print_int(systeminfo->line_tt, STDERR_FILENO);
	output(": ");
	output(systeminfo->argvstr[0]);
	output(": ");
	output(imstr);
}

/**
 * print_int - function prints a decimal number
 * @promptmess: the input message
 * @file_desc: the filedescriptor to write to
 *
 * Return: no of characters printed
 */
int print_int(int promptmess, int file_desc)
{
	int (*__putchar)(char) = _putchar;
	int b, counter = 0;
	unsigned int absval, cur_pos;

	if (file_desc == STDERR_FILENO)
		__putchar = putoutchar;
	if (promptmess < 0)
	{
		absval = -promptmess;
		__putchar('-');
		counter++;
	}
	else
		absval = promtmess;
	cur_pos = absval;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (absval / b)
		{
			__putchar('0' + cur_pos / b);
			counter++;
		}
		cur_pos %= b;
	}
	__putchar('0' + cur_pos);
	counter++;

	return (counter);
}

/**
 * stringify_no- converts a string to int
 * @fig: numb
 * @cntrl: base
 * @checks: argument flags
 *
 * Return: string
 */
char *stringify_no(long int fig, int cntrl, int checks)
{
	static char *lst;
	static char buf[50];
	char elem = 0;
	char *shw;
	unsigned long k = fig;

	if (!(checks & UNSIGNED_ENABLED) && fig < 0)
	{
		k = -fig;
		elem = '-';

	}
	lst = checks & LOWERCASE_ENABLED ? "0123456789abcdef" : "0123456789ABCDEF";
	shw = &buf[49];
	*shw = '\0';

	do	{
		*--shw = lst[k % cntrl];
		k /= cntrl;
	} while (k != 0);

	if (elem)
		*--shw = elem;
	return (shw);
}

/**
 * strip_comments - function replaces '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void strip_comments(char *buf)
{
	int p;

	for (p = 0; buf[p] != '\0'; p++)
		if (buf[p] == '#' && (!p || buf[p - 1] == ' '))
		{
			buf[p] = '\0';
			break;
		}
}
