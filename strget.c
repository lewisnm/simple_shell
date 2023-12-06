#include "dupshell.h"

/**
 * putbuf - chained commands in buff
 * @systeminfo: param struct
 * @buf: address of buffer
 * @size: address of var size
 *
 * Return: bytes read
 */
ssize_t putbuf(system *systeminfo, char **buf, size_t *size)
{
	ssize_t l = 0;
	size_t size_p = 0;

	if (!*size)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handleSigint);
#if ENABLE_GETLINE
		l = getline(buf, &size_p, stdin);
#else
		l = custGetline(info, buf, &size_p);
#endif
		if (l > 0)
		{
			if ((*buf)[l - 1] == '\n')
			{
				(*buf)[l - 1] = '\0'; /* remove trailing newline */
				l--;
			}
			systeminfo->counter_line = 1;
			strip_comment(*buf);
			conhistlist(systeminfo, *buf, systeminfo->numhist++);
			{
				*size = l;
				systeminfo->buf_cmd = buf;
			}
		}
	}
	return (l);
}

/**
 * getSysInput - gets a line without the newline char
 * @systeminfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t getSysInput(system *systeminfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, k, size;
	ssize_t s = 0;
	char **sto_p = &(systeminfo->argstr), *z;

	_putchar(FLASH_INDICATOR);
	s = putbuf(systeminfo, &buf, &size);
	if (s == -1) /* EOF */
		return (-1);
	if (size)
	{
		k = a;
		z = buf + a;

		chainproc(systeminfo, buf, &k, a, size);
		while (k < size)
		{
			if (chain_opp(systeminfo, buf, &k))
				break;
			k++;
		}

		a = k + 1;
		if (a >= size)
		{
			a = size = 0;
			systeminfo->buf_operation = NORM;
		}

		*sto_p = z;
		return (str_len(z));
	}

	*sto_p = buf;
	return (s);
}

/**
 * wade_buf - reads a buffer
 * @systeminfo: parameter struct
 * @buf: buffer
 * @q: size
 *
 * Return: w
 */
ssize_t wade_buf(system *systeminfo, char *buf, size_t *q)
{
	ssize_t w = 0;

	if (*q)
		return (0);
	w = read(systeminfo->rdfiledes, buf, R_BUF_SZ);
	if (w >= 0)
		*q = w;
	return (w);
}

/**
 * custGetLine - gets the next line of input from STDIN
 * @systeminfo: parameter struct
 * @str: address of pointer to buffer, preallocated or NULL
 * @girth: size of preallocated ptr buffer if not NULL
 *
 * Return: t
 */
int custGetLine(system *systeminfo, char **str, size_t *girth)
{
	static char buf[R_BUF_SZ];
	static size_t j, gir;
	size_t m;
	ssize_t z = 0, t = 0;
	char *o = NULL, *brand_p = NULL, *d;

	o = *str;
	if (o && girth)
		t = *girth;
	if (j == gir)
		j = gir = 0;

	z = wade_buf(systeminfo, buf, &gir);
	if (z == -1 || (z == 0 && gir == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	m = d ? 1 + (unsigned int)(d - buf) : gir;
	brand_p = reallocmem(o, t, t ? t + m : m + 1);
	if (!brand_p) /* MALLOC FAILURE! */
		return (o ? free(p), -1 : -1);

	if (t)
		str_n_cat(brand_p, buf + j, m - j);
	else
		str_n_cpy(brand_p, buf + j, m - j + 1);

	t += m - j;
	j = m;
	o = brand_p;

	if (girth)
		*girth = t;
	*str = o;
	return (t);
}

/**
 * handleSigint - blocks ctrl-C
 * @signo: the signal number
 *
 * Return: void
 */
void handleSigint(__attribute__((unused))int signo)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_INDICATOR);
}
