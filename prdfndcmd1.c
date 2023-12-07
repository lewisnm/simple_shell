#include "dupshell.h"

/**
 * histdisp - displays the history list
 * @systeminfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int histdisp(system *systeminfo)
{
	putlst(system->hist);
	return (0);
}

/**
 * rmaka - removes alias to string
 * @systeminfo: parameter struct
 * @word: the string alias
 *
 * Return:0 on success, 1 on error
 */
int rmaka(system *systeminfo, char *word)
{
	char *s, d;
	int get;

	s = str_chr(word, '=');
	if (!s)
		return (1);
	d = *s;
	*s = 0;
	get = rmnodeindex(&(systeminfo->aka),
		retrindex(systeminfo->aka, specprefix(systeminfo->aka, word, -1)));
	*s = d;
	return (get);
}

/**
 * setaka - sets alias to string
 * @systeminfo: parameter struct
 * @word: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setaka(system *systeminfo, char *word)
{
	char *s;

	s = str_chr(word, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (rmaka(systeminfo, word));

	rmaka(systeminfo, word);
	return (putnode_end(&(systeminfo->aka), word, 0) == NULL);
}

/**
 * printaka - prints an alias string
 * @nde: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printaka(lst_t *nde)
{
	char *s = NULL, *b = NULL;

	if (nde)
	{
		s = str_chr(nde->wrd, '=');
		for (b = nde->wrd; b <= s; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * createaka - mimics the alias builtin (man alias)
 * @systeminfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int createaka(system *systeminfo)
{
	int j = 0;
	char *s = NULL;
	lst_t *nde = NULL;

	if (systeminfo->argcstr == 1)
	{
		nde = syteminfo->aka;
		while (nde)
		{
			printaka(nde);
			nde = nde->next_node;
		}
		return (0);
	}
	for (j = 1; systeminfo->argvstr[j]; j++)
	{
		s = str_chr(systeminfo->argvstr[j], '=');
		if (s)
			setaka(systeminfo, systeminfo->argvstr[j]);
		else
			printaka(specprefix(systeminfo->aka, systeminfo->argvstr[j], '='));
	}

	return (0);
}
