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
 * changeNum - function changes number into char string
 * @num: represents number changed to char string
 * @base: base which a number is changed
 * @flags: argument paremeter flags
 * Return: string
 */
char *changeNum(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long c = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		c = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[c % base];
		c /= base;
	} while (c != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}
