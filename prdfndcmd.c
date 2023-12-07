#include "dupshell.h"

/**
 * exitbin - this function indicates the exit of the custom shell
 * @systeminfo: struct potentially with args
 *          maintains constnt func prototype
 *
 *  Return: exits with 0 if systeminfo.argvstr[0] is != to exit
 */
int exitbin(system *systeminfo)
{
	int term_proc;

	if (systeminfo->argvstr[1])
	{
		term_proc = atoiErr(systeminfo->argvstr[1]);
		if (term_proc == -1)
		{
			systeminfo->status = 2;
			outputErr(systeminfo, "Illegal number: ");
			output(systeminfo->argvstr[1]);
			putoutchar('\n');
			return (1);
		}
		systeminfo->error_o = atoiErr(systeminfo->argvstr[1]);
		return (-2);
	}
	systeminfo->error_no = -1;
	return (-2);
}

/**
 * cdbin - function that alters current directory
 * @systeminfo: struct that potentially has args
 *          maintain constnt func prototype
 *  Return: 0 on code execution success
 */
int cdbin(system *systeminfo)
{
	char *sptr, *ptrdirctry, bufmem[1024];
	int drctry;

	sptr = cwd_altr(bufmem, 1024);
	if (!sptr)
		_puts("TODO: >>cwd_alter failure emsg here<<\n");
	if (!systeminfo->argvstr[1])
	{
		ptrdirctry = retrienv(systeminfo, "HOME=");
		if (!ptrdirctry)
			drctry = /* TODO: what it will be */
				drctrych((ptrdirctry = retrienv(systeminfo, "PWD=")) ? ptrdirctry : "/");
		else
			drctry = drctrych(ptrdirctry);
	}
	else if (str_cmp(systeminfo->argvstr[1], "-") == 0)
	{
		if (!retrienv(systeminfo, "OLDPWD="))
		{
			_puts(sptr);
			_putchar('\n');
			return (1);
		}
		_puts(retrienv(systeminfo, "OLDPWD=")), _putchar('\n');
		drctry = /* TODO: what should this be? */
			drctrych((ptrdirctry = retrienv(systeminfo, "OLDPWD=")) ? ptrdirctry : "/");
	}
	else
		drctry = drctrych(systeminfo->argvstr[1]);
	if (drctry == -1)
	{
		outputErr(systeminfo, "can't cd to ");
		output(systeminfo->argvstr[1]), putoutchar('\n');
	}
	else
	{
		setenvset(systeminfo, "OLDPWD", retrienv(systeminfo, "PWD="));
		setenvset(systeminfo, "PWD", cwd_alter(bufmem, 1024));
	}
	return (0);
}

/**
 * helpbin - function that alters current directory
 * @systeminfo: struct that potentially has args
 *          maintain cnstnt func prototype
 *  Return: 0 on code execution success
 */
int helpbin(system *systeminfo)
{
	char **strarr;

	strarr = systeminfo->argvstr;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*strarr);
	return (0);
}
