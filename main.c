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
	s_info s_i;

	(void)ac;
	(void)av;

	s_i.status = 0, s_i.iter_num = 1;
	init_environment(&s_i);

	shell(&s_i);

	exit(s_i.status);
}
