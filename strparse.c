#include "shell.h"

/**
 * cmd_exist - finds executable file in command
 * @systeminfo: the systeminfo struct
 * @path: denotes path of the file to be executed
 *
 * Return: 0 on code success, 1 if error
 */
int cmd_exist(system *systeminfo, char *path)
{
	struct stat st;

	(void)systeminfo;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_str - this function enables string duplication
 * @findpath: the env var PATH and its value
 * @indexstart: index of where to begin
 * @indexstop: index of where to stop
 *
 * Return: a pointer to buf declared
 */
char *dup_str(char *findpath, int indexstart, int indexstop)
{
	static char buf[1024];
	int x = 0, j = 0;

	for (j = 0, x = indexstart; x < indexstop; x++)
		if (findpath[i] != ':')
			buf[j++] = findpath[x];
	buf[j] = 0;
	return (buf);
}

/**
 * cmd_path - identify the PATH env var in string fetched
 * @systeminfo: struct of systeminfo
 * @findpath: env var PATH; string
 * @cmmnd: command from string to be found
 *
 * Return: NULL if command not found and it's path in full if found
 */
char *cmd_path(system *systeminfo, char *findpath, char *cmmnd)
{
	int j = 0, index = 0;
	char *path;

	if (!findpath)
		return (NULL);
	if ((str_len(cmmnd) > 2) && str_start(cmmnd, "./"))
	{
		if (cmd_exist(systeminfo, cmmnd))
			return (cmmnd);
	}
	while (1)
	{
		if (!findpath[j] || findpath[j] == ':')
		{
			path = dup_str(findpath, index, i);
			if (!*path)
				str_cat(path, cmmnd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmmnd);
			}
			if (cmd_exist(systeminfo, path))
				return (path);
			if (!findpath[j])
				break;
			index = j;
		}
		j++;
	}
	return (NULL);
}
