#include "dupshell.h"

/**
 * histdisp - displays the history list
 * @d_typeinfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int histdisp(d_type *d_typeinfo)
{
	putlst(d_typeinfo->hist);
	return (0);
}

/**
 * rmaka - removes alias to string
 * @d_typeinfo: parameter struct
 * @string: the string alias
 *
 * Return:0 on success, 1 on error
 */
int rmaka(d_type *d_typeinfo, char *string)
{
	char *p, c;
	int ret;

	p = str_chr(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rmnodeindex(&(d_typeinfo->aka),
		retrindex(d_typeinfo->aka, specprefix(d_typeinfo->aka, string, -1)));
	*p = c;
	return (ret);
}

/**
 * setaka - sets alias to string
 * @d_typeinfo: parameter struct
 * @string: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setaka(d_type *d_typeinfo, char *string)
{
	char *p;

	p = str_chr(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rmaka(d_typeinfo, string));

	rmaka(d_typeinfo, string);
	return (putnode_end(&(d_typeinfo->aka), string, 0) == NULL);
}

/**
 * printaka - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printaka(lst_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_chr(node->string, '=');
		for (a = node->string; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * createaka - mimics the alias builtin (man alias)
 * @d_typeinfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int createaka(d_type *d_typeinfo)
{
	int i = 0;
	char *p = NULL;
	lst_t *node = NULL;

	if (d_typeinfo->argc_no == 1)
	{
		node = d_typeinfo->aka;
		while (node)
		{
			printaka(node);
			node = node->next_node;
		}
		return (0);
	}
	for (i = 1; d_typeinfo->argvstr[i]; i++)
	{
		p = str_chr(d_typeinfo->argvstr[i], '=');
		if (p)
			setaka(d_typeinfo, d_typeinfo->argvstr[i]);
		else
			printaka(specprefix(d_typeinfo->aka, d_typeinfo->argvstr[i], '='));
	}

	return (0);
}
