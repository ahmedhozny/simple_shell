#include "shell.h"

s_info s_i = {0, 1, NULL, NULL, NULL};

/**
 * sigintHandler - entry point
 * @signal: signal number
 */
void sigintHandler(int signal)
{
	cleanup(&s_i);
	exit(signal);
}

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
	(void)ac;
	(void)av;

	signal(SIGINT, sigintHandler);
	if (!init_environment(&s_i))
		cleanup(&s_i);
	else
		shell(&s_i);

	exit(s_i.status);
}
