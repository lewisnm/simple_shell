#include "dupshell.h"

/**
 * putnode_start - adds a node at the start of a list
 * @start: pointer to head node
 * @wrd: str field of node
 * @fig: node index
 *
 * Return: size of list
 */
lst_t *putnode_start(lst_t **start, const char *wrd, int fig)
{
	lst_t *newNode;

	if (!start)
		return (NULL);
	newNode = malloc(sizeof(lst_t));
	if (!newNode)
		return (NULL);
	filblock((void *)newNode, 0, sizeof(lst_t));
	newNode->fig = fig;
	if (wrd)
	{
		newNode->wrd = str_dup(wrd);
		if (!newNode->wrd)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->next_node = *start;
	*start = newNode;
	return (newNode);
}

/**
 * putnode_end - adds a node at the end of a list
 * @start: address of pointer to head node
 * @wrd: wrd field of node
 * @fig: node index
 *
 * Return: size of list
 */
lst_t *putnode_end(lst_t **start, const char *wrd, int fig)
{
	lst_t *newNode, *nde;

	if (!start)
		return (NULL);

	nde = *start;
	newNode = malloc(sizeof(lst_t));
	if (!newNode)
		return (NULL);
	filblock((void *)newNode, 0, sizeof(lst_t));
	newNode->fig = fig;
	if (wrd)
	{
		newNode->wrd = str_dup(wrd);
		if (!newNode->wrd)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next_node)
			nde = nde->next_node;
		nde->next_node = newNode;
	}
	else
		*start = newNode;
	return (newNode);
}

/**
 * printlststr - prints the wrd'th value of a list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t printlststr(const lst_t *hd)
{
	size_t l = 0;

	while (hd)
	{
		_puts(hd->wrd ? h->wrd : "(nil)");
		_puts("\n");
		hd = hd->next_node;
		l++;
	}
	return (l);
}

/**
 * rmnodeindex - removes a node at a given index
 * @start: address of pointer to first node
 * @ndx: index of node to remove
 *
 * Return: 1 success, 0 fail
 */
int rmnodeindex(lst_t **start, unsigned int ndx)
{
	lst_t *nde, *prvnd;
	unsigned int g = 0;

	if (!start || !*start)
		return (0);

	if (!ndx)
	{
		nde = *start;
		*start = (*start)->next_node;
		free(nde->wrd);
		free(nde);
		return (1);
	}
	nde = *start;
	while (nde)
	{
		if (g == ndx)
		{
			prvnd->next_node = nde->next_node;
			free(nde->wrd);
			free(nde);
			return (1);
		}
		g++;
		prvnd = nde;
		nde = nde->next_node;
	}
	return (0);
}

/**
 * memfree - frees all nodes
 * @hdptr: address of head node
 *
 * Return: void
 */
void memfree(lst_t **hdptr)
{
	lst_t *nde, *nxtnd, *hd;

	if (!hdptr || !*hdptr)
		return;
	hd = *hdptr;
	nde = hd;
	while (nde)
	{
		nxtnd = nde->next_node;
		free(nde->wrd);
		free(nde);
		nde = nxtnd;
	}
	*hdptr = NULL;
}
