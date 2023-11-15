#include "shell.h"

/**
 * memoryRealloc - a function that reallocates momory area
 * @ptr: pointer to the memory area previous alocated
 * @old_size: parameter for amount of bytes of old block
 * @new_size: parameter for amount of bytes of the new block
 *
 * Return: address for the new block of allocated memory
 */
void *memoryRealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	new = malloc(new_size);
	if (!new)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new[old_size] = ((char *)ptr)[old_size];
	free(ptr);

	return (new);
}


/**
 * addMemory - a function that sets memory with a constant byte
 * @str: the pointer to the memory area to fill
 * @b: parameter for the byte to set the string
 * @n: the number of bytes to be set in the memory
 * Return: address for str memory area
 */
char *addMemory(char *str, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)

		str[m] = b;

	return (str);
}

/**
 * freeStrings - a function that frees strings
 * @dptr: double pointer to the strings to free
 */
void freeStrings(char **dptr)
{
	char **m = dptr;

	if (!dptr)
		return;

	while (*dptr)
		free(*dptr++);

	free(m);
}

