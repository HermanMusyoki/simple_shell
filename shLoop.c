#include "shell.h"

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
