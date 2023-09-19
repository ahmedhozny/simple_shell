#include "shell.h"

/**
 * pre_execute - prepares requested command for execution
 * @s_i: session info
 */
void pre_execute(s_info *s_i)
{
	char *tmp = NULL;

	if (!s_i->cur_cmd || !s_i->cur_cmd[0])
		return;
	if (exec_builtin(s_i))
		return;
	s_i->status = 0;
	if (s_i->cur_cmd[0][0] != '.' && s_i->cur_cmd[0][0] != '/')
	{
		tmp = search_PATH(s_i);
		if (!tmp)
			command_validity_error(s_i, s_i->cur_cmd[0], 1);
		else
		{
			free(s_i->cur_cmd[0]);
			s_i->cur_cmd[0] = tmp;
		}
	}
	else if (access(s_i->cur_cmd[0], X_OK) == -1)
		command_validity_error(s_i, s_i->cur_cmd[0], 1);

	if (!s_i->status)
		_execute(s_i);
}

/**
 * _execute -executes a given command
 * @s_i: session info pointer
 * @arg0: command name
 * @argv: command arguments
 * Return: 0 on success, -1 on failure, or error number of fork error
 */
int _execute(s_info *s_i)
{
	int pid, status;
	char **env = environment_to_array(s_i);

	if (!env)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		s_i->status = errno;
		perror("Fork error");
		return (bigFree(env, -1), errno);
	}

	if (pid == 0)
	{
		execve(s_i->cur_cmd[0], s_i->cur_cmd, env);
		s_i->status = 127;
		perror(s_i->cur_cmd[0]);
		exit(127);
	}

	wait(&status);
	s_i->status = WEXITSTATUS(status);
	bigFree(env, -1);
	return ((s_i->status != 0) ? -1 : 0);
}
