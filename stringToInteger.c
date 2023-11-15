#include "shell.h"
/**
 * check_delimiter -a function to check if character is a delimiter
 * @c: character to be checked
 * @delimiter: the string containing the delimeter
 * Return: 1 (true) 0r 0 (false /fail)
 */
int check_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);

	return (0);
}
/**
 * stringToInteger - a function that convers a given string to integer
 * @str: the string to convert to integer
 * Return: 0 always (success)
 */

int stringToInteger(char *str)
{
	int m, sign = 1, flag = 0, print_out;
	unsigned int result = 0;

	for (m = 0; str[m] != '\0' && flag != 2; m++)
	{
		if (str[m] == '-')
			sign *= -1;

		if (str[m] >= '0' && str[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		print_out = -result;
	else
		print_out = result;


	return (print_out);
}


/**
 * active_sh - checks if the shell is interactive torespond to commands
 * @info: pointer to the address of the struct
 *
 * Return: 1 (success) or 0 (fail)
 */
int active_sh(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * checkAlpha -a function to check if character is alphabet
 * @c: The character to check if is alphabet
 * Return: 1 (success) and 0 (fail)
 */

int checkAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);

	else
		return (0);
}
