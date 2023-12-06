#include "dupshell.h"

/**
 * strexec - main loop
 * @systeminfo: the parameter & return info struct
 * @argv: the argument vector
 *
 * Return: 0 success, 1 error
 */
int strexec(system *systeminfo, char **argv)
{
	ssize_t s = 0;
	int ret_def = 0;

	while (s != -1 && ret_def != -2)
	{
		resetinfo(systeminfo);
		if (modsys(info))
			_puts("$ ");
		putoutchar(FLUSH_INDICATOR);
		s = getSysInput(syteminfo);
		if (s != -1)
		{
			settinginfo(systeminfo, argv);
			ret_def = search_builtin(systeminfo);
			if (ret_def == -1)
				search_cmd(systeminfo);
		}
		else if (modsys(systeminfo))
			_putchar('\n');
		memfrinfo(systeminfo, 0);
	}
	wrthist(systeminfo);
	memfrinfo(systeminfo, 1);
	if (!modsys(systeminfo) && systeminfo->status)
		exit(systeminfo->status);
	if (ret_def == -2)
	{
		if (systeminfo->error_no == -1)
			exit(systeminfo->status);
		exit(systeminfo->error_no);
	}
	return (ret_def);
}

/**
 * search_builtin - finds a builtin command
 * @systeminfo: the parameter & return info struct
 *
 * Return: -1 not found,
 *		0 success,
 *		1 not successful,
 */
int search_builtin(system *systeminfo)
{
	int j, def_ret = -1;
	bltn_tbl tablebltn[] = {
		{"exit", exitbin},
		{"env", managenv},
		{"help", helpbin},
		{"history", histdisp},
		{"setenv", modsetenv},
		{"unsetenv", unsetenvrm},
		{"cd", cdbin},
		{"alias", createaka},
		{NULL, NULL}
	};

	for (j = 0; tablebltn[j].type; j++)
		if (str_cmp(systeminfo->argvstr[0], tablebltn[j].type) == 0)
		{
			systeminfo->line_tt++;
			def_ret = tablebltn[j].handler(systeminfo);
			break;
		}
	return (def_ret);
}

/**
 * search_cmd - locates command in path
 * @systeminfo: the parameter & return info struct
 *
 * Return: void
 */
void search_cmd(system *systeminfo)
{
	char *path = NULL;
	int l, v;

	systeminfo->path = systeminfo->argv[0];
	if (systeminfo->counter_line == 1)
	{
		systeminfo->line_tt++;
		systeminfo->counter_line = 0;
	}
	for (l = 0, v = 0; systeminfo->argstr[l]; l++)
		if (!delimchar(systeminfo->argstr[l], " \t\n"))
			v++;
	if (!v)
		return;

	path = cmd_path(systeminfo, retrienv
		(systeminfo, "PATH="), systeminfo->argvstr[0]);
	if (path)
	{
		systeminfo->path = path;
		child_fork(systeminfo);
	}
	else
	{
		if ((modsys(systeminfo) || retrienv(systeminfo, "PATH=")
			|| systeminfo->argvstr[0][0] == '/')
				&& cmd_exist(systeminfo, systeminfo->argvstr[0]))
			child_fork(systeminfo);
		else if (*(systeminfo->argstr) != '\n')
		{
			systeminfo->status = 127;
			print_error(systeminfo, "not found\n");
		}
	}
}

/**
 * child_fork - creats a child process to carry out the command
 * @systeminfo: the parameter & return info struct
 *
 * Return: void
 */
void child_fork(system *systeminfo)
{
	pid_t branch_pid;

	branch_pid = fork();
	if (branch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (branch_pid == 0)
	{
		if (execve(systeminfo->path, systeminfo->argvstr, strenv(systeminfo)) == -1)
		{
			memfrinfo(systeminfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(systeminfo->status));
		if (WIFEXITED(systeminfo->status))
		{
			systeminfo->status = WEXITSTATUS(systeminfo->status);
			if (systeminfo->status == 126)
				outputErr(systeminfo, "Permission denied\n");
		}
	}
}
