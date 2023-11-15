#include "shell.h"

/**
 * freeList - function frees all nodes of a linked list
 * @head_ptr: head of  pointer to a stored data
 * Return: void
 */

void freeList(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * putNode -  function adds a new node to a linked list
 * @head: modifies the head pointer if necessary
 * @str: string data that will be stored
 * @num: numerical value associated with the new node
 * Return: size of list
 */

list_t *putNode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	addMemory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = stringDup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * outputListstr - outputs the string list stored in each node
 * @h: pointer to the head of the linked list
 * Return: size of list
 */
size_t outputListstr(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}

	return (y);
}

/**
 * removeNodeatIndex - function clears a node from a linked list
 * @head:  head of the linked list
 * @index: index of the node to be deleted from the linked list
 * Return: 1 on success, 0 on failure
 */
int removeNodeatIndex(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int y = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (y == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		y++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
