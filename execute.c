#include "shell.h"

/**
 * _execute -executes a given command
 * @s_i: session info pointer
 * @arg0: command name
 * @argv: command arguments
 * Return: 0 on success, -1 on failure, or error number of fork error
 */
int _execute(s_info *s_i, char *arg0, char **argv)
{
	int pid, status;

	pid = fork();
	if (pid < 0)
	{
		s_i->status = errno;
		perror("Fork error");
		return (errno);
	}

	if (pid == 0)
	{
		execve(arg0, argv, environ);
		s_i->status = 127;
		perror(arg0);
		exit(127);
	}

	wait(&status);
	s_i->status = WEXITSTATUS(status);
	return ((s_i->status != 0) ? -1 : 0);
}
