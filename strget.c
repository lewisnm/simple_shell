#include "dupshell.h"

/**
 * input_buf - chained commands in buff
 * @d_typeinfo: param struct
 * @buf: address of buffer
 * @size: address of varbl size
 *
 * Return: bytes read
 */
ssize_t input_buf(d_type *d_typeinfo, char **buf, size_t *size)
{
	ssize_t s = 0;
	size_t lenVar = 0;

	if (!*size) /* if nothing left in the buffer, fill it */
	{
		/*clearmem((void **)d_typeinfo->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if ENABLEcustGetLine
		s = getline(buf, &lenVar, stdin);
#else
		s = custGetLine(d_typeinfo, buf, &lenVar);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			d_typeinfo->counter_line = 1;
			strip_comments(*buf);
			conhistlist(d_typeinfo, *buf, d_typeinfo->numhist++);
			/* if (str_chr(*buf, ';')) is this a command chain? */
			{
				*size = s;
				d_typeinfo->buf_cmd = buf;
			}
		}
	}
	return (s);
}

/**
 * getSysInput - gets a line without the newline char
 * @d_typeinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t getSysInput(d_type *d_typeinfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t j, i, size;
	ssize_t s = 0;
	char **buf_p = &(d_typeinfo->argstr), *ptrP;

	_putchar(FLUSH_INDICATOR);
	s = input_buf(d_typeinfo, &buf, &size);
	if (s == -1) /* EOF */
		return (-1);
	if (size)	/* we have commands left in the chain buffer */
	{
		i = j; /* init new iterator to current buf position */
		ptrP = buf + j; /* get pointer for return */

		chainproc(d_typeinfo, buf, &i, j, size);
		while (i < size) /* iterate to semicolon or end */
		{
			if (check_opp(d_typeinfo, buf, &i))
				break;
			i++;
		}

		j = i + 1; /* increment past nulled ';'' */
		if (j >= size) /* reached end of buffer? */
		{
			j = size = 0; /* reset position and length */
			d_typeinfo->buf_operation = NORM;
		}

		*buf_p = ptrP; /* pass back pointer to current command position */
		return (str_len(ptrP)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from custGetLine() */
	return (s); /* return length of buffer from custGetLine() */
}

/**
 * read_buf - reads a buffer
 * @d_typeinfo: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: w
 */
ssize_t read_buf(d_type *d_typeinfo, char *buf, size_t *j)
{
	ssize_t s = 0;

	if (*j)
		return (0);
	s = read(d_typeinfo->rdfiledes, buf, R_BUF_SZ);
	if (s >= 0)
		*j = s;
	return (s);
}

/**
 * custGetLine - gets the next line of input from STDIN
 * @d_typeinfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: t
 */
int custGetLine(d_type *d_typeinfo, char **ptr, size_t *length)
{
	static char buf[R_BUF_SZ];
	static size_t j, size;
	size_t n;
	ssize_t s = 0, m = 0;
	char *ptrP = NULL, *newBlock = NULL, *ptrC;

	ptrP = *ptr;
	if (ptrP && length)
		m = *length;
	if (j == size)
		j = size = 0;

	s = read_buf(d_typeinfo, buf, &size);
	if (s == -1 || (s == 0 && size == 0))
		return (-1);

	ptrC = str_chr(buf + j, '\n');
	n = ptrC ? 1 + (unsigned int)(ptrC - buf) : size;
	newBlock = reallocmem(ptrP, m, m ? m + n : n + 1);
	if (!newBlock) /* MALLOC FAILURE! */
		return (ptrP ? free(ptrP), -1 : -1);

	if (m)
		str_n_cat(newBlock, buf + j, n - j);
	else
		str_n_cpy(newBlock, buf + j, n - j + 1);

	m += n - j;
	j = n;
	ptrP = newBlock;

	if (length)
		*length = m;
	*ptr = ptrP;
	return (m);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signo: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signo)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_INDICATOR);
}
