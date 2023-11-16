#include "shell.h"

/**
 * readChain - a function that parmits to continue chaining
 * according to last status
 * @info: pointer to the struct
 * @buf: pointer to the character in the buffer
 * @p: pointer to the current index
 * @st: the beggining of the buffer
 * @len: parameter for buffer length
 *
 * Return: Nothing
 */
void readChain(info_t *info, char *buffer, size_t *p, size_t str, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[str] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[str] = 0;
			m = len;
		}
	}

	*p = m;
}

/**
 * cyso_isChain - a function that checks if a character
 * in buffer is a chain delimeter
 * @info: pointer to the struct
 * @buf: pointer to thr character to test
 * @p: pointer to the current index in the buffer
 *
 * Return: 1 (success) or 0 (fail)
 */
int cyso_isChain(info_t *info, char *buffer, size_t *p)
{
	size_t m = *p;

	if (buffer[m] == '|' && buffer[m + 1] == '|')
	{
		buffer[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[m] == '&' && buffer[m + 1] == '&')
	{
		buffer[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[m] == ';')
	{
		buffer[m] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}
