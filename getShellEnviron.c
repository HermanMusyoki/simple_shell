#include "shell.h"
/**
 * addEnv - a function that sets a new environment variable,
 *             or change the current one
 * @info: a pointer to a structure storing possible arguments
 * @var: pointer to the string environment variable property
 * @value: pointer to the string with the env variable
 *  Return: 0 (success)
 */
int addEnv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(stringLen(var) + stringLen(value) + 2);
	if (!buf)
		return (1);
	stringCpy(buf, var);
	stringCat(buf, "=");
	stringCat(buf, value);
	node = info->env;
	while (node)
	{
		ptr = beginWith(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	putNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


/**
 * getShellEnv - a function that returns the string
 * array copy of the shell environment
 * @info: a pointer to structure for possible arguments
 * Return: Always 0 (success)
 */
char **getShellEnv(info_t *info)
{
	if (!info->environ || info->env_changed)

	{

		info->environ = strList(info->env);

		info->env_changed = 0;
	}



	return (info->environ);
}

/**
 * removeEnv - a function the unsets an environment variable
 * @info: a pointer to a structure storing possible arguments
 * @var: a pointer to the string environment var property
 *
 * Return: 1 (success) or 0 (fail)
 */
int removeEnv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t m = 0;
	char *ptr;


	if (!node || !var)
		return (0);


	while (node)
	{

		ptr = beginWith(node->str, var);

		if (ptr && *ptr == '=')
		{
			info->env_changed = removeNodeatIndex(&(info->env), m);
			m = 0;
			node = info->env;
			continue;
		}

		node = node->next;
		m++;
	}


	return (info->env_changed);
}

