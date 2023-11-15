#include "shell.h"

/**
 * **stringTow2 - function splits a string into words
 * @str: the input string to split into substrings
 * @d: the delimeter  character that is used to split str into substrings
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stringTow2(char *str, char d)
{
	int y, g, l, a, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (y = 0; str[y] != '\0'; y++)
		if ((str[y] != d && str[y + 1] == d) ||
				    (str[y] != d && !str[y + 1]) || str[y + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, g = 0; g < numwords; g++)
	{
		while (str[y] == d && str[y] != d)
			y++;
		l = 0;
		while (str[y + l] != d && str[y + l] && str[y + l] != d)
			l++;
		s[g] = malloc((l + 1) * sizeof(char));
		if (!s[g])
		{
			for (l = 0; l < g; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (a = 0; a < l; a++)
			s[g][a] = str[y++];
		s[g][a] = 0;
	}
	s[g] = NULL;
	return (s);
}

/**
 * **stringTow - splits  string into multiple substrings based on delimeter
 * @str: the input string  to split into substrings
 * @d: the delimeter string to split the str into substrings
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stringTow(char *str, char *d)
{
	int y, g, l, a, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (y = 0; str[y] != '\0'; y++)
		if (!check_delimiter(str[y], d) && (check_delimiter
					(str[y + 1], d) || !str[y + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, g = 0; g < numwords; g++)
	{
		while (check_delimiter(str[y], d))
			y++;
		l = 0;
		while (!check_delimiter(str[y + l], d) && str[y + l])
			l++;
		s[g] = malloc((l + 1) * sizeof(char));
		if (!s[g])
		{
			for (l = 0; l < g; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (a = 0; a < l; a++)
			s[g][a] = str[y++];
		s[g][a] = 0;
	}
	s[g] = NULL;
	return (s);
}
