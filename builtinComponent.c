#include "shell.h"


/**
 * displayHistory - a function that displays the history list,the
 * output is one line
 * command starting with line numbers begging at 0.
 * @info:a pointer to struct of arguments
 *  Return: Always 0 (success)
 */
int displayHistory(info_t *info)
{
	outputList(info->history);
	return (0);
}


/**
 * checkHistory -a function that checks history from file
 * @info: pointer to the struct
 *
 * Return: the history information or 0 (fail)
 */
int checkHistory(info_t *info)
{
	int m, final = 0, counter = 0;
	ssize_t fd, rdlen, filesize = 0;
	struct stat st;
	char *buf = NULL, *filename = retrieveHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buf = malloc(sizeof(char) * (filesize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, filesize);
	buf[filesize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (m = 0; m < filesize; m++)
		if (buf[m] == '\n')
		{
			buf[m] = 0;
			createHistoryList(info, buf + final, counter++);
			final = m + 1;
		}
	if (final != m)
		createHistoryList(info, buf + final, counter++);
	free(buf);
	info->histcount = counter;
	while (info->histcount-- >= HIST_MAX)
		removeNodeatIndex(&(info->history), 0);
	listHistory(info);
	return (info->histcount);
}
