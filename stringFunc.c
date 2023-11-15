#include "shell.h"
/**
 * _putchar - a function that writes the character c to standard output
 * @c: parameter to character c to output
 *
 * Return: 1 (success) or -1 (fail)
 */
int _putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);

		m = 0;
	}

	if (c != BUF_FLUSH)
		buf[m++] = c;

	return (1);
}

/**
 * stringDup - a function that duplicates a string
 * @str: pointer to the string to duplicate
 *
 * Return: duplicate string address
 */
char *stringDup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}
/**
 * _puts - a function that outputs an input string
 * @str: pointer to the string to output
 *
 * Return: Void
 */
void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;

	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * stringCpy -a function that copies a string
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 *
 * Return: dest string
 */
char *stringCpy(char *dest, char *src)

{
	int m = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[m])
	{
		dest[m] = src[m];
		m++;
	}

	dest[m] = 0;
	return (dest);
}
