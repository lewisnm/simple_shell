#include "shell.h"

/**
 **str_n_cpy - makes a copy of a string
 *@destin: where the string id to be copied to
 *@srcString: the original string
 *@no: no of chrs to be copied
 *Return: the concatenated string
 */
char *str_n_cpy(char *destin, char *srcString, int n)
{
	int k, i;
	char *str = destin;

	k = 0;
	while (srcString[k] != '\0' && k < n - 1)
	{
		destin[k] = srcString[k];
		k++;
	}
	if (k < n)
	{
		i = k;
		while (i < n)
		{
			destin[i] = '\0';
			i++;
		}
	}
	return (str);
}

/**
 **str_n_cat - joins two strings
 *@trgt: first string
 *@ori: second string
 *@num: num of bytes used
 *Return: the concatenated string
 */
char *str_n_cat(char *destin, char *srcString, int n)
{
	int k, i;
	char *str = destin;

	k = 0;
	i = 0;
	while (destin[k] != '\0')
		k++;
	while (srcString[i] != '\0' && i < n)
	{
		destin[k] = srcString[i];
		k++;
		i++;
	}
	if (i < n)
		destin[k] = '\0';
	return (str);
}

/**
 **str_chr - finds a char in a string
 *@str: string being checked
 *@cha: char being searched
 *Return: (str) a pointer to the memory area str
 */
char *str_chr(char *str, char y)
{
	do {
		if (*str == y)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
