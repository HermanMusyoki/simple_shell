#include "shell.h"

/**
 * sigint_handler - function represents the signal number
 * @sig_num: suppress warnings from the compiler about the variable
 * Return: void
 */

void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");

	_puts("$ ");

	_putchar(BUF_FLUSH);
}

/**
 * inputBuffer - function handles input operations involving a buffer
 * @info: contains info needed to carry out the input operation
 * @buf: rep a pointer to a buffer where input data is to be stored
 * @len: represents the length or size of the buffer
 * Return: bytes read
 */

ssize_t inputBuffer(info_t *info, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_v = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		w = cyso_getLine(buf, &len_v, stdin);
#else
		w = get_Line(info, buf, &len_v);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0';
				w--;
			}
			info->linecount_flag = 1;
			deleteComments(*buf);
			createHistoryList(info, *buf, info->histcount++);
			{
				*len = w;
				info->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * readBuffer - reads data from an external source and store in the buffer
 * @info: contains info required for the read operation to be performed
 * @buf: represents the buffer where the read data is to be stored
 * @i: represent an index or offset within the buffe
 * Return: r
 */

ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * getInput - function reads data from an external source
 * @info: contains info required for the input operation to be carried out
 * Return: bytes
 */

ssize_t getInput(info_t *info)
{
	static char *buf;
	static size_t y, g, len;
	ssize_t w = 0;
	char **buf_v = &(info->arg), *v;

	_putchar(BUF_FLUSH);
	w = inputBuffer(info, &buf, &len);
	if (w == -1)
		return (-1);
	if (len)
	{
		g = y;
		v = buf + y;

		readChain(info, buf, &g, y, len);
		while (g < len)
		{
			if (cyso_isChain(info, buf, &g))
				break;
			g++;
		}

		y = g + 1;
		if (y >= len)
		{
			y = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_v = v;
		return (stringLen(v));
	}

	*buf_v = buf;
	return (w);
}

/**
 * get_Line - function is used for reading lines of text
 * @info: contains info needed to perform the line-reading operation
 * @ptr: a pointer to a pointer that will point to allocated buffer
 * @length:  length of chars that can be read into the buffer
 * Return: s
 */

int get_Line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t y, len;
	size_t l;
	ssize_t w = 0, s = 0;
	char *p = NULL, *new_p = NULL, *b;

	p = *ptr;
	if (p && length)
		s = *length;
	if (y == len)
		y = len = 0;

	w = readBuffer(info, buf, &len);
	if (w == -1 || (w == 0 && len == 0))
		return (-1);

	b = stringChr(buf + y, '\n');
	l = b ? 1 + (unsigned int)(b - buf) : len;
	new_p = memoryRealloc(p, s, s ? s + l : l + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		stringnCat(new_p, buf + y, l - y);
	else
		stringnCpy(new_p, buf + y, l - y + 1);

	s += l - y;
	y = l;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
