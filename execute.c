#include "shell.h"

/**
 * pre_execute - prepares requested command for execution
 * @s_i: session info
 *
 * Return: 1 on Success, 0 on Failure
 */
int pre_execute(s_info *s_i)
{
	char *tmp = NULL;

	if (!s_i->cur_cmd || !s_i->cur_cmd[0])
		return (0);
	tmp = get_alias(s_i, s_i->cur_cmd[0]);
	if (tmp != NULL)
		free(s_i->cur_cmd[0]), s_i->cur_cmd[0] = _strdup(tmp);
	if (!_strcmp(s_i->cur_cmd[0], "exit"))
		return (exit_sh(s_i), 0);
	s_i->status = 0;
	if (exec_builtin(s_i))
		return (1);
	if (s_i->cur_cmd[0][0] != '.' && s_i->cur_cmd[0][0] != '/')
	{
		tmp = search_PATH(s_i);
		if (!command_validity_error(s_i, tmp, 1))
		{
			free(s_i->cur_cmd[0]);
			s_i->cur_cmd[0] = tmp;
		}
	}
	else if (!command_validity_error(s_i, s_i->cur_cmd[0], 1))
		file_permission_error(s_i, 1);

	if (!s_i->status)
		return (!_execute(s_i));
	return (0);
}

/**
 * _execute -executes a given command
 * @s_i: session info pointer
 *
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
		s_i->status = 2;
		perror(s_i->cur_cmd[0]);
		exit(2);
	}

	wait(&status);
	s_i->status = WEXITSTATUS(status);
	bigFree(env, -1);
	return ((s_i->status != 0) ? -1 : 0);
}
