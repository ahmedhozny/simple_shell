#include "shell.h"

/**
 * sigintHandler - entry point
 * @signal: signal number
 */
void sigintHandler(int signal)
{
	cleanup(session_getter_setter(NULL));
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
	s_info s_i = {0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	(void)ac;
	(void)av;

	session_getter_setter(&s_i);
	signal(SIGINT, sigintHandler);
	if (!init_environment(&s_i))
		cleanup(&s_i);
	else
		shell(&s_i);

	exit(s_i.status);
}

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
