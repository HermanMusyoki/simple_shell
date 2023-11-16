#include "shell.h"

/**
 * outputAlias -a function that outputs an alias string
 * @node: pointer to the alias node to print
 *
 * Return: Always 0 (success) or  1  (fail)
 */
int outputAlias(list_t *node)
{
	char *ptr = NULL, *m = NULL;

	if (node)
	{
		ptr = stringChr(node->str, '=');
		for (m = node->str; m <= ptr; m++)
		_putchar(*m);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}


/**
 * removeAlias - a function that sets alias to string
 * @info: pointer to the struct
 * @string: a pointer to the string alias to set
 *
 * Return: Always 0 (success) 0r  1 (fail)
 */
int removeAlias(info_t *info, char *string)
{
	char *ptr, chars;
	int output;

	ptr = stringChr(string, '=');

	if (!ptr)
		return (1);

	chars = *ptr;
	*ptr = 0;
	output = removeNodeatIndex(&(info->alias),
		retrieveNode(info->alias, nodeBeginsChar(info->alias, string, -1)));
	*ptr = chars;

	return (output);
}

/**
 * cyso_alias - a function that works as builtin alias
 * @info: a pointer to a structure consisting of possible arguments
 *  Return: Always 0 (success)
 */
int cyso_alias(info_t *info)
{
	int m = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			outputAlias(node);
			node = node->next;
		}
		return (0);
	}

	for (m = 1; info->argv[m]; m++)
	{
		ptr = stringChr(info->argv[m], '=');
		if (ptr)
			addAlias(info, info->argv[m]);
		else
			outputAlias(nodeBeginsChar(info->alias, info->argv[m], '='));
	}

	return (0);
}

/**
 * addAlias -a function that sets alias to given string
 * @info:  a pointer to the struct
 * @string: a pointer to the string alias to set
 *
 * Return: Always 0 (success) or  1 (fail)
 */
int addAlias(info_t *info, char *string)
{
	char *ptr;

	ptr = stringChr(string, '=');

	if (!ptr)
		return (1);

	if (!*++ptr)
		return (removeAlias(info, string));

	removeAlias(info, string);

	return (putNodeEnd(&(info->alias), string, 0) == NULL);
}

