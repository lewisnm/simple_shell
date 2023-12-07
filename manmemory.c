#include "dupshell.h"

/**
 **filblock - custom memset; fill n=memry block with constant/similar byte
 *@sptr: points to the block of memory
 *@u: the similar/constant byte with which *sptr is filled with
 *@byteno: total bytes the memset aims to fill the memory block with
 *Return: pointer to the blockof memory mset fills with cnstnt byte
 */
char filblock(char *sptr, char u, unsigned int byteno)
{
	unsigned int a;

	for (a = 0; a < byteno; a++)
		sptr[a] = u;
	return (sptr);
}

/**
 * freemem - clears strings' string
 * @ptrstr: strings' string
 */
void freemem(char **ptrstr)
{
	char **y = ptrstr;

	if (!ptrstr)
		return;
	while (*ptrstr)
		free(*ptrstr++);
	free(y);
}

/**
 * reallocmem - custom realloc function that re-allocates memoryblock
 * @p: points to blckold
 * @blckold: blckold byte size
 * @blcknew: blcknew byte size
 *
 * Return: pointer to the old block
 */
void *reallocmem(void *p, unsigned int blckold, unsigned int blcknew)
{
	char *pnt;

	if (!p)
		return (malloc(blcknew));
	if (!blcknew)
		return (free(p), NULL);
	if (blcknew == blckold)
		return (p);

	pnt = malloc(new_size);
	if (!pnt)
		return (NULL);

	blckold = blckold < blcknew ? blckold : blcknew;
	while (blckold--)
		pnt[blckold] = ((char *)p)[blckold];
	free(p);
	return (pnt);
}
