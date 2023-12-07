#include "dupshell.h"

/**
 * rethistfile - custom fucntion to fetch a file's history
 * @systeminfo: argument from struct
 *
 * Return: string with the history file
 */

char *rethistfile(system *systeminfo)
{
	char *buf, *drct;

	drct = retrienv(systeminfo, "HOME=");
	if (!drct)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(drct) + str_len(HISTORY_FILE_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, drct);
	str_cat(buf, "/");
	str_cat(buf, HISTORY_FILE_NAME);
	return (buf);
}

/**
 * wrthist - custom function opens file or create a new one if not found
 * @systeminfo: argument from struct
 *
 * Return: -1 if fail, 1 is code execution succeeds
 */
int wrthist(system *systeminfo)
{
	ssize_t file_desc;
	char *ptrfileN = rethistfile(systeminfo);
	lst_t *ptrnode = NULL;

	if (!ptrfileN)
		return (-1);

	file_desc = open(ptrfileN, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(ptrfileN);
	if (file_desc == -1)
		return (-1);
	for (ptrnode = systeminfo->hist; ptrnode; ptrnode = ptrnode->next)
	{
		_putsfd(ptrnode->str, file_desc);
		_putfd('\n', file_desc);
	}
	writechar(FLUSH_INDICATOR, file_desc);
	close(file_desc);
	return (1);
}

/**
 * rdhist - function to fetch and return the history of an allocated file
 * @systeminfo: struct as arg
 *
 * Return: file's numhist on execution success or 0 if otherwise found
 */
int rdhist(system *systeminfo)
{
	int j, fin = 0, counterl = 0;
	ssize_t file_desc, retlen, szfnd = 0;
	struct stat st;
	char *buf = NULL, *ptrfileN = rethistfile(systeminfo);

	if (!ptrfileN)
		return (0);

	file_desc = open(ptrfileN, O_RDONLY);
	free(ptrfileN);
	if (file_desc == -1)
		return (0);
	if (!fstat(file_desc, &st))
		szfnd = st.st_size;
	if (szfnd < 2)
		return (0);
	buf = malloc(sizeof(char) * (szfnd + 1));
	if (!buf)
		return (0);
	retlen = read(file_desc, buf, szfnd);
	buf[szfnd] = 0;
	if (retlen <= 0)
		return (free(buf), 0);
	close(file_desc);
	for (j = 0; j < szfnd; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			conhistlist(systeminfo, buf + fin, counterl++);
			fin = j + 1;
		}
	if (fin != j)
		conhistlist(systeminfo, buf + fin, counterl++);
	free(buf);
	systeminfo->numhist = counterl;
	while (systeminfo->numhist-- >= MAX_HISTORY_ENTRIES)
		rmnodeindex(&(systeminfo->hist), 0);
	renohist(systeminfo);
	return (systeminfo->numhist);
}

/**
 * conhistlist - function adds node at end of singly linked list
 * @systeminfo: struct potentially with args
 * @buf: buffer
 * @counterl: history of file plus new end node
 *
 * Return: 0 on execution success
 */
int conhistlist(system *systeminfo, char *buf, int counterl)
{
	lst_t *ptrnode = NULL;

	if (systeminfo->hist)
		ptrnode = systeminfo->hist;
	putnode_end(&ptrnode, buf, counterl);

	if (!systeminfo->hist)
		systeminfo->hist = ptrnode;
	return (0);
}

/**
 * renohist - reno singly llist after alteration
 * @systeminfo: struct potentially with args
 *
 * Return: new history of file
 */
int renohist(system *systeminfo)
{
	lst_t *ptrnode = systeminfo->hist;
	int j = 0;

	while (ptrnode)
	{
		ptrnode->no = j++;
		ptrnode = ptrnode->next;
	}
	return (systeminfo->numhist = j);
}
