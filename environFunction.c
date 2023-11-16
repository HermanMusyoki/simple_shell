#include "shell.h"

/**
 * cyso_addEnv - function activates new environment variable
 * @inform: pointer structure with arguments
 *  Return: Always 0
 */

int cyso_addEnv(info_t *inform)
{
	if (inform->argc != 3)
	{
		cyso_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (addEnv(inform, inform->argv[1], inform->argv[2]))

		return (0);

	return (1);
}

/**
 * getEnv - function  access and retrieve environment variable values
 * @info: pointer to Structure with arguments
 * @id: represents the name of an environment variable to retrieve
 * Return: the value
 */

char *getEnv(info_t *info, const char *id)
{
	list_t *node = info->env;
	char *v;

	while (node)
	{
		v = beginWith(node->str, id);
		if (v && *v)
			return (v);
		node = node->next;
	}

	return (NULL);
}

/**
 * cyso_env - function prints the current environment
 * @information: pointer to Structure with arguments
 * Return: Always 0
 */

int cyso_env(info_t *information)
{
	outputListstr(information->env);

	return (0);
}

/**
 * cyso_removeEnv - function removes an environment variable
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int cyso_removeEnv(info_t *info)
{
	int y;

	if (info->argc == 1)
	{
		cyso_puts("Too few arguements.\n");

		return (1);
	}
	for (y = 1; y <= info->argc; y++)
	removeEnv(info, info->argv[y]);

	return (0);
}

/**
 * fillEnv_list - function fills environ linked list
 * @info: pointer structure with arguments
 * Return: Always 0
 */

int fillEnv_list(info_t *info)
{
	list_t *node = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		putNodeEnd(&node, environ[y], 0);
	info->env = node;

	return (0);
}
