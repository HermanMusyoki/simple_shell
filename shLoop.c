#include "shell.h"

/**
 * locateCommand - function is used to find a specific command
 * @info: a pointer to a structure or data type
 * Return: void
 */

void locateCommand(info_t *info)
{
	char *path = NULL;
	int y, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (y = 0, l = 0; info->arg[y]; y++)
		if (!check_delimiter(info->arg[y], " \t\n"))
			l++;
	if (!l)
		return;

	path = locatePath(info, getEnv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((active_sh(info) || getEnv(info, "PATH=")
					|| info->argv[0][0] == '/') && checkCommand(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			outputError(info, "not found\n");
		}
	}
}

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

/**
 * forkCommand - responsible for forking new process to execute command
 * @info: a pointer to a structure or data type
 * Return: void
 */
void forkCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getShellEnv(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				outputError(info, "Permission denied\n");
		}
	}
}

/**
 * locateBuiltin - function  used to find a built-in command
 * @info: a pointer to a structure or data type
 * Return: -1 buitin not found,0 success,1 nt succes,2 exit
 */

int locateBuiltin(info_t *info)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", cyso_exit},
		{"env", cyso_env},
		{"aid", cyso_Aid},
		{"history", displayHistory},
		{"addEnv", cyso_addEnv},
		{"removeEnv", cyso_removeEnv},
		{"cd", cyso_Cd},
		{"alias", cyso_alias},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (stringCmp(info->argv[0], builtintbl[y].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[y].func(info);
			break;
		}

	return (built_in_ret);
}
