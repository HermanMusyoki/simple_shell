#include "shell.h"

/**
 * puts_FD - a function that outputs an input string
 * @str: pointer to the the string to output
 * @fd: parameter to the filedescriptor to be written on
 *
 * Return: character number to print
 */
int puts_FD(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);

	while (*str)
	{
		m += put_FD(*str++, fd);
	}

	return (m);
}

/**
 * cyso_putchar - a function that writes the character c to standard error
 * @c: stores the character to write to stderr
 *
 * Return:  1 (success) or -1 (fail)
 */
int cyso_putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}

	if (c != BUF_FLUSH)
		buf[m++] = c;

	return (1);
}

/**
 * cyso_puts - a function that output an input string
 * @str: pointer to the string to output.
 *
 * Return: void
 */
void cyso_puts(char *str)
{
	int m = 0;

	if (!str)
		return;

	while (str[m] != '\0')
	{
		cyso_putchar(str[m]);
		m++;
	}

}
/**
 * put_FD - a function that writes the character c to given file descriptor
 * @c: parameter for the character to output
 * @fd: parameter to the  file descriptor to write the character
 *
 * Return: 1 (success) or -1 (fail)
 */
int put_FD(char c, int fd)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}

	if (c != BUF_FLUSH)
		buf[m++] = c;

	return (1);
}

