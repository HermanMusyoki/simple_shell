#include "shell.h"

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
 * cyso_Erratoi - function converts a string to an integer
 * @s: a pointer to a char data type
 * Return: 0 if no numbers in string,otherwise-1 on error
 */
int cyso_Erratoi(char *s)
{
	int y = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (y = 0;  s[y] != '\0'; y++)
	{
		if (s[y] >= '0' && s[y] <= '9')
		{
			result *= 10;
			result += (s[y] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else

			return (-1);
	}

	return (result);
}

/**
 * outputD - function brings the output of integer value
 * @input: represents the integer value printed
 * @fd: the filedescriptor formats integer value
 * Return: number of characters printed
 */
int outputD(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int y, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = cyso_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (y = 1000000000; y > 1; y /= 10)
	{
		if (_abs_ / y)
		{
			__putchar('0' + current / y);
			count++;
		}
		current %= y;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * changeNum - function changes number into char string
 * @num: represents number changed to char string
 * @base: base which a number is changed
 * @flags: argument paremeter flags
 * Return: string
 */
char *changeNum(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long c = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		c = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[c % base];
		c /= base;
	} while (c != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * outputError - function gives the ouput of an error message
 * @info: a pointer to a struct info related to the error
 * @estr: a pointer to a char data type
 * Return: 0 if no numbers in string,otherwise -1 on error
 */
void outputError(info_t *info, char *estr)
{
	cyso_puts(info->fname);

	cyso_puts(": ");

	outputD(info->line_count, STDERR_FILENO);

	cyso_puts(": ");

	cyso_puts(info->argv[0]);

	cyso_puts(": ");

	cyso_puts(estr);
}

/**
 * deleteComments - function changes first instance of comments 0\n
 * @buf: pointer address of the string
 * Return: Always 0;
 */

void deleteComments(char *buf)
{
	int y;

	for (y = 0; buf[y] != '\0'; y++)
		if (buf[y] == '#' && (!y || buf[y - 1] == ' '))
		{
			buf[y] = '\0';

			break;
		}
}