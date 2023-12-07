#include "dupshell.h"

/**
 * managenv - prints the current environment
 * @systeminfo: struct potentially with args;
 *          maintains const func prototype
 * Return: 0 on code execution success
 */
int managenv(system *systeminfo)
{
	printstrlst(systeminfo->envcpy);
	return (0);
}

/**
 * retrienv - fetch corresponding val of env var given
 * @systeminfo: struct potentially with args
 * @ptrenv: name of envt vrbl provided
 *
 * Return: the value
 */
char *retrienv(system *systeminfo, const char *ptrenv)
{
	list_t *ptrnode = systeminfo->envcpy;
	char *y;

	while (ptrnode)
	{
		y = starts_with(ptrnode->str, ptrenv);
		if (y && *y)
			return (y);
		ptrnode = ptrnode->next_node;
	}
	return (NULL);
}

/**
 * modsetenv - give val of corresponding provided env var
 *             manipulate or modify the current env var
 * @systeminfo: struct with possible args
 *        maintains const func prototype
 *  Return: 0 on code execution success
 */
int modsetenv(system *systeminfo)
{
	if (systeminfo->argc_no != 3)
	{
		output("Incorrect arg count\n");
		return (1);
	}
	if (setenvset(systeminfo, systeminfo->argvstr[1], systeminfo->argvstr[2]))
		return (0);
	return (1);
}

/**
 * unsetenvrm - eradicate env var
 * @systeminfo: struct potentially with args
 *        mntn const func prototype
 *  Return: 0 on code success
 */
int unsetenvrm(system *systeminfo)
{
	int t;

	if (systeminfo->argc_no == 1)
	{
		output("Very few arg count\n");
		return (1);
	}
	for (t = 1; t <= systeminfo->argc_no; t++)
		rmsetenv(systeminfo, systeminfo->argvstr[t]);

	return (0);
}

/**
 * initenvar - initializes linked list
 * @systeminfo: struct with  potential args Used to maintain
 *          mntn cnstnt func prototype
 * Return: 0 on code execution success
 */
int initenvar(system *systeminfo)
{
	list_t *ptrnode = NULL;
	size_t t;

	for (t = 0; environcpy[t]; t++)
		putnode_end(&ptrnode, environcpy[t], 0);
	systeminfo->envcpy = ptrnode;
	return (0);
}
