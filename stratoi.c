#include "dupshell.h"

/**
 * modsys - return 1 for interactive mode of shell
 * @systeminfo: &ofstruct
 *
 * Return: 1 if shell is interactive(sysallowmdfctn) 0 for else
 */
int modsys(system *systeminfo)
{
	return (isatty(STDIN_FILENO) && systeminfo->rdfiledes <= 2);
}

/**
 * delimchar - function to identify delimiter character in a string
 * @z: char to be checked whether or not delimiter
 * @delimiter: delimiter char taken as string
 * Return: if true, comp returns 1, and 0 for false
 */
int delimchar(char z, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == z)
			return (1);
	return (0);
}

/**
 *alphachar - custom isalpha to check for alphabetic chrctr
 *@z: denotes input character
 *Return: 0 if char not alphabet, 1 if alphabet char is found
 */

int alphachar(int z)
{
	if ((z >= 'a' && z <= 'z') || (z >= 'A' && z <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strint - converts a string to an integer
 *@atoistr: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strint(char *atoistr)
{
	int k, oprtr = 1, flgint = 0, printout;
	unsigned int foundval = 0;

	for (k = 0;  atoistr[k] != '\0' && flgint != 2; k++)
	{
		if (atoistr[k] == '-')
			oprtr *= -1;

		if (atoistr[k] >= '0' && atoistr[k] <= '9')
		{
			flgint = 1;
			foundval *= 10;
			foundval += (atoistr[k] - '0');
		}
		else if (flgint == 1)
			flgint = 2;
	}

	if (oprtr == -1)
		printout = -foundval;
	else
		printout = foundval;

	return (printout);
}
