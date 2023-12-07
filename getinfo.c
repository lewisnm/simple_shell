#include "dupshell.h"

/**
 * resetinfo - denotes struct named system
 * @systeminfo: & of struct; hexadecimal val
 */
void resetinfo(system *systeminfo)
{
	systeminfo->argstr = NULL;
	systeminfo->argvstr = NULL;
	systeminfo->path = NULL;
	systeminfo->argc_no = 0;
}

/**
 * settinginfo - denotes system struct
 * @systeminfo: &of struct
 * @av: av, denotes arg vector
 */
void settinginfo(system *systeminfo, char **av)
{
	int t = 0;

	systeminfo->fname = av[0];
	if (systeminfo->argstr)
	{
		systeminfo->argvstr = tkzStr(systeminfo->argstr, " \t");
		if (!systeminfo->argvstr)
		{

			systeminfo->argvstr = malloc(sizeof(char *) * 2);
			if (systeminfo->argvstr)
			{
				systeminfo->argvstr[0] = str_dup(systeminfo->argstr);
				systeminfo->argvstr[1] = NULL;
			}
		}
		for (t = 0; systeminfo->argvstr && systeminfo->argvstr[t]; t++)
			;
		systeminfo->argc_no = t;

		akasub(systeminfo);
		varsub(systeminfo);
	}
}

/**
 * memfrinfo - system struct freed in fields
 * @systeminfo: &of struct
 * @total: checks if freeing all fields
 */
void memfrinfo(system *systeminfo, int total)
{
	freemem(systeminfo->argvstr);
	systeminfo->argvstr = NULL;
	systeminfo->path = NULL;
	if (total)
	{
		if (!systeminfo->buf_cmd)
			free(systeminfo->argstr);
		if (systeminfo->envcpy)
			memlist(&(systeminfo->envcpy));
		if (systeminfo->hist)
			memfree(&(systeminfo->hist));
		if (systeminfo->aka)
			memfree(&(systeminfo->aka));
		freemem(systeminfo->environcpy);
			systeminfo->environcpy = NULL;
		clearmem((void **)systeminfo->buf_cmd);
		if (systeminfo->rdfiledes > 2)
			close(systeminfo->rdfiledes);
		_putchar(FLUSH_INDICATOR);
	}
}
