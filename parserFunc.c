#include "shell.h"

/**
 * duplicateChars - creates ne char with copy,allocate memory for new string
 * @pathstr: original char string from which a portion will be duplicated
 * @start: index at which the portion to be duplicated starts
 * @stop: index at which the portion to be duplicated ends
 * Return: pointer to new buffer
 */

char *duplicateChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int y = 0, l = 0;

	for (l = 0, y = start; y < stop; y++)
		if (pathstr[y] != ':')
			buf[l++] = pathstr[y];
	buf[l] = 0;


	return (buf);
}

/**
 * checkCommand - evaluate if its a valid command or executable file
 * @info: provide additional info for the function to perform its check
 * @path: path to determine if it's a valid command or executable file
 * Return: 1 if true, 0 otherwise
 */

int checkCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * locatePath - search for the path of a specific command
 * @info: contains additional info for the path search operation
 * @pathstr: search path string,a colon-separated list of directories
 * @cmd: name of the command the function is searching the full path
 * Return: full path of cmd if found or NULL
 */

char *locatePath(info_t *info, char *pathstr, char *cmd)
{
	int y = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((stringLen(cmd) > 2) && beginWith(cmd, "./"))
	{
		if (checkCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[y] || pathstr[y] == ':')
		{
			path = duplicateChars(pathstr, curr_pos, y);
			if (!*path)
				stringCat(path, cmd);
			else
			{
				stringCat(path, "/");
				stringCat(path, cmd);
			}
			if (checkCommand(info, path))
				return (path);
			if (!pathstr[y])
				break;
			curr_pos = y;
		}
		y++;
	}
	return (NULL);
}
