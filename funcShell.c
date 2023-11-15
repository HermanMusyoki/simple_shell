#include "shell.h"

/**
 * cyso_hsh - this is a main function shell loop
 * @info: pass information to the function
 * @av: the command-line arguments provided to the program
 * Return: 0 on success, 1 on error, or error code
 */

int cyso_hsh(info_t *info, char **av)
{
	ssize_t w = 0;
	int builtin_ret = 0;

	while (w != -1 && builtin_ret != -2)
	{
		deleteInfo(info);
		if (active_sh(info))
			_puts("$ ");
		cyso_putchar(BUF_FLUSH);
		w = getInput(info);
		if (w != -1)
		{
			setInfo(info, av);
			builtin_ret = locateBuiltin(info);
			if (builtin_ret == -1)
				locateCommand(info);
		}
		else if (active_sh(info))
			_putchar('\n');
				freeInfo(info, 0);
	}
	createHistory(info);
	freeInfo(info, 1);
	if (!active_sh(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}
