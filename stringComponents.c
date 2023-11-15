#include "shell.h"

/**
 * beginWith -  checks if one string starts with another
 * @haystack: string the function searches for the prefix specified
 * @needle: prefix string which function checks if it  starts haystack
 * Return: address of next char of haystack or NULL
 */

char *beginWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}

/**
 * stringLen - function calculates,returns the length of a string
 * @s: string for which the length needs to be determined
 * Return: integer length of string
 */
int stringLen(char *s)
{
	int Y = 0;

	if (!s)

		return (0);

	while (*s++)
		Y++;

	return (Y);
}

/**
 * stringCat - function concatenates two strings
 * @dest: string should be large to accommodate combined result
 * @src: string that will be appended to end of dest string
 * Return: pointer to destination buffer
 */

char *stringCat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;

	return (ret);
}

/**
 * stringCmp - compare the two strings until a difference is found
 * @s1: returns a negative integer value
 * @s2: returns a positive integer value
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int stringCmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)

		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
