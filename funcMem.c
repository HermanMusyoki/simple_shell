#include "shell.h"

/**
 * cysoFree - free memory associated with allocated block parameter
 * @ptr: pointer to allocated memory block that needs to be deallocated
 * Return: 1 if freed, otherwise 0.
 */

int cysoFree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}
