#include "dupshell.h"

/**
 * strenv - arr of strings for environ is returned
 * @systeminfo: struct with args, mntn con func prototype
 *
 * Return: 0 on execution success
 */
char **strenv(system *systeminfo)
{
	if (!systeminfo->environcpy || systeminfo->altered_env)
	{
		systeminfo->environcpy = list_to_strings(systeminfo->varenv);
		systeminfo->altered_env = 0;
	}

	return (systeminfo->environcpy);
}

/**
 * rmsetenv - env var is eliminated
 * @systeminfo: struct with args, mntn con func prototype
 *
 *  Return: 1 if rm success, 0 otherwise
 * @varstr: property of env variable string
 */
int rmsetenv(system *systeminfo, char *varstr)
{
	list_t *ptrnode = systeminfo->varenv;
	size_t u = 0;
	char *ptr;

	if (!ptrnode || !varstr)
		return (0);

	while (ptrnode)
	{
		ptr = str_start(ptrnode->str, varstr);
		if (ptr && *ptr == '=')
		{
			systeminfo->altered_env = rmnodeindex(&(systeminfo->varenv), u);
			u = 0;
			ptrnode = systeminfo->varenv;
			continue;
		}
		ptrnode = ptrnode->next_node;
		u++;
	}
	return (systeminfo->altered_env);
}

/**
 * setenvset - func to assgn val to new env var
 *             function to manipulate or mod already existing env var
 * @systeminfo: struct with args, mntn con func prototype
 * @varstr: property of the current env var string
 * @ptrval: value of current env var string
 *
 *  Return: 0 on code execution success
 */
int setenvset(system *systeminfo, char *varstr, char *ptrval)
{
	char *buf = NULL;
	list_t *ptrnode;
	char *ptr;

	if (!varstr || !ptrval)
		return (0);

	buf = malloc(str_len(varstr) + str_len(ptrval) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, varstr);
	str_cat(buf, "=");
	str_cat(buf, ptrval);
	ptrnode = systeminfo->varenv;
	while (ptrnode)
	{
		ptr = str_start(ptrnode->str, varstr);
		if (ptr && *ptr == '=')
		{
			free(ptrnode->str);
			ptrnode->str = buf;
			systeminfo->altered_env = 1;
			return (0);
		}
		ptrnode = ptrnode->next_node;
	}
	putnode_end(&(systeminfo->varenv), buf, 0);
	free(buf);
	systeminfo->altered_env = 1;
	return (0);
}
