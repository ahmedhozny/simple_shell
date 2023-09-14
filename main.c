#include "shell.h"

/**
 * main - entry point
 * @ac: arguments count
 * @av: arguments vector
 *
 * Return: 0 on Success,
 * proper exit code otherwise
 */
int main(int ac, char **av)
{
	s_info s_i = {0, 1, NULL, NULL};
	(void)ac;
	(void)av;

	init_environment(&s_i);
	shell(&s_i);

	exit(s_i.status);
}
