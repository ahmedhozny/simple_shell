#include "shell.h"

/**
 * session_getter_setter - gets or sets the session information pointer
 * @s_i: session info to store new pointer, null to get the latest one
 * Return: latest pointer if any is set, NULL if session is never set
 */
s_info *session_getter_setter(s_info *s_i)
{
	static s_info *session_info;

	if (s_i != NULL)
		session_info = s_i;
	return (session_info);
}

/**
 * sigintHandler - entry point
 * @signal: signal number
 */
void sigintHandler(int signal)
{
	if (signal == SIGINT)
	{
		cleanup(session_getter_setter(NULL));
		exit(130);
	}
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
	s_info s_i = {0, 0, STDIN_FILENO, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	if (!init_environment(&s_i))
		return (cleanup(&s_i), 1);
	if (ac > 2)
		return (cleanup(&s_i), 1);
	if (ac == 2)
	{
		s_i.fd = open(av[1], O_RDONLY);
		if (s_i.fd == -1 && errno == EACCES)
		{
			if (errno == EACCES)
				return (file_error(&s_i, av[1], ": Permission denied\n"), cleanup(&s_i),
								2);
			else
				return (file_error(&s_i, av[1], ": No such file\n"), cleanup(&s_i), 2);
		}
	}

	session_getter_setter(&s_i);
	signal(SIGINT, sigintHandler);

	shell(&s_i);
	exit(s_i.status);
}
