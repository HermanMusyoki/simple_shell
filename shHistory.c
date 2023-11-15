#include "shell.h"

/**
 * listHistory -  a function that puts numbers to the history linked
 * list after changes
 * @info: pointer to the struct of possible arguments
 *
 * Return: the new renumbered history count
 */
int listHistory(info_t *info)
{
	list_t *node = info->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}

	return (info->histcount = m);
}

/**
 * retrieveHistoryFile - a function that retrieves the history file
 * @info: pionter to the struct of arguments
 *
 * Return: string that is containing histoty file
 */

char *retrieveHistoryFile(info_t *info)
{
	char *buffer, *dirfile;

	dirfile = getEnv(info, "HOME=");

	if (!dirfile)
		return (NULL);

	buffer = malloc(sizeof(char) * (stringLen(dirfile) +
				stringLen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	stringCpy(buffer, dirfile);
	stringCat(buffer, "/");
	stringCat(buffer, HIST_FILE);

	return (buffer);
}
/**
 * createHistoryList - a function that creates entry to a history linked list
 * @info: pointer to the struct of possible arguments
 * @buf: pointer to the buffer
 * @linecount: parameter for number of history lines count
 *
 * Return: Always 0 (success)
 */
int createHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	putNodeEnd(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}


/**
 * createHistory - a function that write a file, or
 * appends to already created file
 * @info: pointer to the struct
 *
 * Return: 1 (success) or -1 (fail)
 */
int createHistory(info_t *info)
{
	ssize_t fd;
	char *filename = retrieveHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		puts_FD(node->str, fd);
		put_FD('\n', fd);
	}

	put_FD(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

