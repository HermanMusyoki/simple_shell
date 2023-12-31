#include "shell.h"

/**
 * freeInfo - function is expected to perform resource deallocation
 * @info: holds data that may need to be deallocated or released
 * @all: flag that allows function to control or free resources
 */

void freeInfo(info_t *info, int all)
{
	freeStrings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freeStrings(info->environ);
			info->environ = NULL;
		cysoFree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * setInfo - modifies field properties by extracting relevant info
 * @info: structure to be modified
 * @av: command-line arguments passed to the program
 */

void setInfo(info_t *info, char **av)
{
	int y = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = stringTow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = stringDup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (y = 0; info->argv && info->argv[y]; y++)
			;
		info->argc = y;

		changeAlias(info);
		changeVars(info);
	}
}

/**
 * deleteInfo - function performs cleanup tasks
 * @info: perform operations such as releasing resources
 */

void deleteInfo(info_t *info)
{
	info->arg = NULL;

	info->argv = NULL;

	info->path = NULL;

	info->argc = 0;
}
