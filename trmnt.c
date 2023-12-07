#include "dupshell.h"

/**
 **str_n_cpy - makes a copy of a string
 *@trgt: where the string id to be copied to
 *@ori: the original string
 *@num: no of chrs to be copied
 *Return: the concatenated string
 */
char *str_n_cpy(char *trgt, char *ori, int num)
{
	int k, l;
	char *p = trgt;

	k = 0;
	while (ori[k] != '\0' && k < num - 1)
	{
		trgt[k] = ori[k];
		k++;
	}
	if (k < num)
	{
		l = k;
		while (l < num)
		{
			trgt[l] = '\0';
			l++;
		}
	}
	return (p);
}

/**
 **str_n_cat - joins two strings
 *@trgt: first string
 *@ori: second string
 *@num: num of bytes used
 *Return: the concatenated string
 */
char *str_n_cat(char *trgt, char *ori, int num)
{
	int k, l;
	char *p = trgt;

	k = 0;
	l = 0;
	while (trgt[k] != '\0')
		k++;
	while (ori[l] != '\0' && l < num)
	{
		trgt[k] = ori[l];
		k++;
		l++;
	}
	if (l < num)
		trgt[k] = '\0';
	return (p);
}

/**
 **str_chr - finds a char in a string
 *@str: string being checked
 *@cha: char being searched
 *Return: (s) a pointer to the memory area s
 */
char *str_chr(char *str, char cha)
{
	do {
		if (*str == cha)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
