#include "dubshell.h"

/**
 * szlst - length of linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t szlst(const lst_t *hd)
{
	size_t k = 0;

	while (hd)
	{
		hd = hd->next_node;
		k++;
	}
	return (k);
}

/**
 * lsttostr - returns array of strings of the list->wrd
 * @hd: first node pointer
 *
 * Return: array of strings
 */
char **lsttostr(lst_t *hd)
{
	lst_t *nde = hd;
	size_t p = szlst(hd), k;
	char **wrds;
	char *word;

	if (!hd || !k)
		return (NULL);
	wrds = malloc(sizeof(char *) * (p + 1));
	if (!wrds)
		return (NULL);
	for (p = 0; nde; nde = nde->next_node, p++)
	{
		word = malloc(str_len(nde->wrd) + 1);
		if (!word)
		{
			for (k = 0; k < p; k++)
				free(wrds[k]);
			free(wrds);
			return (NULL);
		}

		word = str_cpy(word, nde->wrd);
		wrds[p] = word;
	}
	wrds[i] = NULL;
	return (wrds);
}


/**
 * putlst - prints all elements lst_t
 * @hd: first node pointer
 *
 * Return: size of list
 */
size_t putlst(const lst_t *hd)
{
	size_t d = 0;

	while (hd)
	{
		_puts(stringify_no(hd->no, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->wrd ? hd->wrd : "(nil)");
		_puts("\n");
		hd = hd->next_node;
		d++;
	}
	return (d);
}

/**
 * specprefix - gives a node with prefix at the start of a string
 * @nde: list head pointer
 * @prfx: string to match
 * @l: next char after prefix to match
 *
 * Return: match node or null
 */
lst_t *specprefix(lst_t *nde, char *prfx, char l)
{
	char *r = NULL;

	while (nde)
	{
		r = str_start(nde->wrd, prfx);
		if (r && ((l == -1) || (*r == l)))
			return (nde);
		nde = nde->next_node;
	}
	return (NULL);
}

/**
 * retrindex - retrives the index of a node
 * @hd: list head pointer
 * @nde: the node pointer
 *
 * Return: index of node or -1
 */
ssize_t retrindex(lst_t *hd, lst_t *nde)
{
	size_t h = 0;

	while (hd)
	{
		if (hd == nde)
			return (h);
		hd = hd->next_node;
		h++;
	}
	return (-1);
}
