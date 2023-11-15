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

/**
 * putNodeEnd - adds a node to the end of the linked list
 * @head: modifies the head pointer if necessary
 * @str: string data that will be stored
 * @num:  numerical value associated with the new node
 * Return: size of list
 */
list_t *putNodeEnd(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	addMemory((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = stringDup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
