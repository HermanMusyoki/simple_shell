#include "shell.h"

/**
 * changeVars - a function the changes vars in the tokenized string
 * @info: pointer to the struct
 *
 * Return: 1 (success) or 0 (fail)
 */
int changeVars(info_t *info)
{
	int m = 0;
	list_t *node;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;

		if (!stringCmp(info->argv[m], "$?"))
		{
			changeString(&(info->argv[m]),
					stringDup(changeNum(info->status, 10, 0)));
			continue;
		}

		if (!stringCmp(info->argv[m], "$$"))
		{
			changeString(&(info->argv[m]),
					stringDup(changeNum(getpid(), 10, 0)));
			continue;
		}

		node = nodeBeginsChar(info->env, &info->argv[m][1], '=');

		if (node)
		{
			changeString(&(info->argv[m]),
					stringDup(stringChr(node->str, '=') + 1));
			continue;
		}

		changeString(&info->argv[m], stringDup(""));

	}

	return (0);
}

/**
 * changeString - a function the changes a string  to a new one
 * @old: pointer to the old string to change
 * @new: pointer to the new string
 *
 * Return: 1 (success) or 0 (fail)
 */
int changeString(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}

/**
 * changeAlias - a function that changes an aliases in the tokenized string
 * @info: pointer to the struct
 *
 * Return: 1 (success) or 0 (fail)
 */
int changeAlias(info_t *info)
{
	int m;
	list_t *node;
	char *ptr;

	for (m = 0; m < 10; m++)
	{
		node = nodeBeginsChar(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = stringChr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = stringDup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}
