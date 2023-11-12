#include "shell.h"

/**
 * nodeBeginsChar - a function that prints node whose string begins with prefix
 * @node: pointer to list head of the linked list
 * @prefix: characters to match for comparison
 * @c: the next character after prefix to match in the string
 *
 * Return: node matching to prefix
 */
list_t *nodeBeginsChar(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = beginWith(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * strList - a function that prints an array of strings of the linked list
 * @head: pointer to first node of the linked list
 *
 * Return: string arrays of the list
 */
char **strList(list_t *head)
{
	list_t *node = head;
	size_t m = listLength(head), n;
	char **strs;
	char *str;

	if (!head || !m)
		return (NULL);

	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);

	for (m = 0; node; node = node->next, m++)
	{
		str = malloc(stringLen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < m; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = stringCpy(str, node->str);
		strs[m] = str;
	}
	strs[m] = NULL;

	return (strs);
}

/**
 * retrieveNode - a function that gets the index of a node in a linked list
 * @head: pointer to list head of the linked list
 * @node: pointer to the node to get the index
 *
 * Return: node index of the list
 */
ssize_t retrieveNode(list_t *head, list_t *node)
{
	size_t m = 0;

	while (head)
	{
		if (head == node)
			return (m);

		head = head->next;
		m++;
	}

	return (-1);
}


/**
 * listLength - a function that returns the length of linked list
 * @h: pointer to the first node of the linked list
 *
 * Return: length of the linked list
 */
size_t listLength(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		h = h->next;
		m++;
	}

	return (m);
}

/**
 * outputList - a function that outputs all elements of a list_t linked list
 * @h: pointer to first node of the linked list
 *
 * Return: all elements of the list
 */
size_t outputList(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(changeNum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}

	return (m);
}

