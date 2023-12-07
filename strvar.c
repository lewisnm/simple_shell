#include "dupshell.h"

/**
 * check_opp - checks if current char is a chain delimeter
 * @systeminfo: the parameter struct
 * @buf: char buffer
 * @s: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_opp(system *systeminfo, char *buf, size_t *s)
{
	size_t k = *s;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		systeminfo->buf_operation = OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		systeminfo->buf_operation = AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		systeminfo->buf_operation = CHAIN;
	}
	else
		return (0);
	*s = k;
	return (1);
}

/**
 * chainproc - countinues the chain depending on the last status
 * @systeminfo: struct parameter
 * @buf: buffer char
 * @s: info on the current position in buf
 * @j: starting position in buf
 * @sz: length of buf
 *
 * Return: Void
 */
void chainproc(system *systeminfo, char *buf, size_t *s, size_t j, size_t sz)
{
	size_t k = *s;

	if (systeminfo->buf_operation == AND)
	{
		if (systeminfo->status)
		{
			buf[j] = 0;
			k = sz;
		}
	}
	if (systeminfo->buf_operation == OR)
	{
		if (!systeminfo->status)
		{
			buf[j] = 0;
			k = sz;
		}
	}

	*s = k;
}

/**
 * aka_sub - replaces aliases in the tokenized string
 * @systeminfo: the parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int aka_sub(system *systeminfo)
{
	int j;
	lst_t *nde;
	char *s;

	for (j = 0; j < 10; j++)
	{
		nde = specprefix(systeminfo->aka, systeminfo->argvstr[0], '=');
		if (!nde)
			return (0);
		free(systeminfo->argvstr[0]);
		p = str_chr(nde->wrd, '=');
		if (!s)
			return (0);
		p = str_dup(s + 1);
		if (!s)
			return (0);
		systeminfo->argvstr[0] = s;
	}
	return (1);
}

/**
 * varsub - substitutes vars in the tokenized string
 * @systeminfo: the parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int varsub(system *systeminfo)
{
	int j = 0;
	lst_t *nde;

	for (j = 0; systeminfo->argvstr[j]; j++)
	{
		if (systeminfo->argvstr[j][0] != '$' || !systeminfo->argvstr[j][1])
			continue;

		if (!str_cmp(systeminfo->argvstr[j], "$?"))
		{
			strsub(&(systeminfo->argvstr[j]),
				str_dup(stringify_no(systeminfo->status, 10, 0)));
			continue;
		}
		if (!str_cmp(systeminfo->argvstr[j], "$$"))
		{
			strsub(&(systeminfo->argvstr[j]),
				str_dup(stringify_no(getpid(), 10, 0)));
			continue;
		}
		nde = specprefix(systeminfo->envcpy, &systeminfo->argvstr[j][1], '=');
		if (nde)
		{
			strsub(&(systeminfo->argvstr[j]),
				str_dup(str_chr(nde->wrd, '=') + 1));
			continue;
		}
		strsub(&systeminfo->argvstr[j], str_dup(""));

	}
	return (0);
}

/**
 * strsub - replaces string
 * @prev: address of old string
 * @next: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int strsub(char **prev, char *next)
{
	free(*prev);
	*prev = next;
	return (1);
}
