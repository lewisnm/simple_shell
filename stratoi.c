#include "dupshell.h"

/**
 * modsys - return 1 for interactive mode of shell
 * @d_typeinfo: &ofstruct
 *
 * Return: 1 if shell is interactive(sysallowmdfctn) 0 for else
 */
int modsys(d_type *d_typeinfo)
{
	return (isatty(STDIN_FILENO) && d_typeinfo->rdfiledes <= 2);
}

/**
 * delimchar - function to identify delimiter character in a string
 * @c: char to be checked whether or not delimiter
 * @delim: delimiter char taken as string
 * Return: if true, comp returns 1, and 0 for false
 */
int delimchar(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *alphachar - custom isalpha to check for alphabetic chrctr
 *@c: denotes input character
 *Return: 0 if char not alphabet, 1 if alphabet char is found
 */

int alphachar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strtint - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strtint(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
