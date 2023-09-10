#include "shell.h"

/**
 * main - it is made as a temporary test file
 * until we write it in a better way
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	char *av[2];
	size_t len = 0;
	char *line = NULL;
	ssize_t r;
	char **env = environ;

	av[1] = NULL;
	while (1)
	{
		_puts(PROMPT);
		_putchar(BUF_FLUSH);
		r = getline(&line, &len, stdin);
		if (r != -1)
		{
			line[strcspn(line, "\n")] = '\0';
			av[0] = line;
			child_pid = fork();
			if (child_pid == 0)
			{
				if (execve(av[0], av, env) == -1)
					perror("Error");
			}
			else
				wait(NULL);
		}
	}
	free(line);
	return (0);
}
