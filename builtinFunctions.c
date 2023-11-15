include "shell.h"

/**
 * cyso_Cd - function changes directory
 * @info: pointer to Structure with arguments
 * Return: Always 0
 */

int cyso_Cd(info_t *info)
{
	char *t, *dir, buffer[1024];
	int chdir_ret;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = getEnv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (stringCmp(info->argv[1], "-") == 0)
	{
		if (!getEnv(info, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(getEnv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = getEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		outputError(info, "can't cd to ");
		cyso_puts(info->argv[1]), cyso_putchar('\n');
	}
	else
	{
		addEnv(info, "OLDPWD", getEnv(info, "PWD="));
		addEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cyso_Aid - fuction changes the current directory
 * @info: pointer to Structure with arguments
 * Return: Always 0
 */

int cyso_Aid(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

/**
 * cyso_exit - a function that exits the shell
 * @info: pointer to Structure with arguments
 * Return: (0) if info.argv[0] != "exit"
 */

int cyso_exit(info_t *info)
{
	int checkCommand;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		checkCommand = cyso_Erratoi(info->argv[1]);
		if (checkCommand == -1)
		{
			info->status = 2;
			outputError(info, "Illegal number: ");
			cyso_puts(info->argv[1]);
			cyso_putchar('\n');
			return (1);
		}
		info->err_num = cyso_Erratoi(info->argv[1]);

		return (-2);
	}
	info->err_num = -1;

	return (-2);
}
