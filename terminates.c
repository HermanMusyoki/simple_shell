#include "shell.h"

/**
 **stringnCat - a function to join two strings
 *@dest: pointer to the first string
 *@src: pointer to the second string to join
 *@n: the number of bytes used during concatenation
 *Return: the joined string
 */
char *stringnCat(char *dest, char *src, int n)
{
	int m, b;
	char *str = dest;

	m = 0;
	b = 0;

	while (dest[m] != '\0')
		m++;

	while (src[b] != '\0' && b < n)
	{
		dest[m] = src[b];
		m++;
		b++;
	}

	if (b < n)
		dest[m] = '\0';

	return (str);
}
/**
 **stringChr - a function to find a character in a string
 *@str: pointer to the string to parse for character
 *@chars: the character to find in the string
 *Return: pointer str to the memory area of string str
 */
char *stringChr(char *str, char chars)
{
	do {
		if (*str == chars)
			return (str);

	} while (*str++ != '\0');


	return (NULL);
}


/**
 **stringnCpy - a function that copies a string
 *@dest: pointer to the destination string to copy from src
 *@src: pointer to the source string to copy from
 *@n: parameter for number of characters from src to copy
 *Return: the copied string
 */
char *stringnCpy(char *dest, char *src, int n)
{
	int m, b;
	char *str = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{

		b = m;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (str);
}

