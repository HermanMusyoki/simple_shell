#include "shell.h"

/**
 * main - entry point responsible for the program's execution
 * @ac: number of command-line arguments passed to the program
 * @av: array of strings containing the command-line arguments
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				cyso_puts(av[0]);
				cyso_puts(": 0: Can't open ");
				cyso_puts(av[1]);
				cyso_putchar('\n');
				cyso_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	fillEnv_list(info);
	checkHistory(info);
	cyso_hsh(info, av);

	return (EXIT_SUCCESS);
}
