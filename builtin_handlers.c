#include "shell.h"

/**
 * exec_builtin - execute proper built-in function
 * @s_i: session info
 *
 * Return: 1 on Success, 0 Otherwise
 */
int exec_builtin(s_info *s_i)
{
	char **args = s_i->cur_cmd, *cmd = s_i->cur_cmd[0];

	if (!_strcmp(cmd, "env"))
		print_env(s_i);
	else if (!_strcmp(cmd, "setenv"))
	{
		if (!args[1] || !args[2])
			return (print_error("Error: Usage: setenv VARIABLE VALUE\n"));
		_setenv(s_i, args[1], args[2]);
	}
	else if (!_strcmp(cmd, "unsetenv"))
	{
		if (!args[1])
			return (print_error("Error: Usage: unsetenv VARIABLE\n"));
		_unsetenv(s_i);
	}
	else if (!_strcmp(cmd, "exit"))
		exit_sh(s_i);
	else if (!_strcmp(cmd, "cd"))
	{
		if (cd(s_i) == 2)
			if (args[1])
				cd_validity_checker(s_i, args[1], 1);
	}
	else
		return (0);
	return (1);
}

/**
 * cd - prepare for change directory
 * @s_i: session info
 *
 * Return: 1 on Success, 2 on cd error , 0 Otherwise
 */
int cd(s_info *s_i)
{
	char *pwd = NULL;
	node *old_pwd = _getenv(s_i, "OLDPWD");
	size_t size = 0;

	pwd = getcwd(pwd, size);
	if (!pwd)
		return (0);
	if (s_i->cur_cmd[1] && s_i->cur_cmd[2])
		return (free(pwd), 0);
	if (old_pwd)
	{
		free(s_i->prev_dir);
		s_i->prev_dir = _strdup(old_pwd->d_ptr);
	}
	else if (!s_i->prev_dir)
		s_i->prev_dir = _strdup(pwd);
	if (!s_i->prev_dir)
		return (free(pwd), 0);

	return (change_dir(s_i, pwd));
}
/**
 * change_dir - change directory
 * @s_i: session info
 * @pwd: current working directory
 *
 * Return: 1 on Success, 2 on cd error , 0 Otherwise
 */
int change_dir(s_info *s_i, char *pwd)
{
	node *home = _getenv(s_i, "HOME");
	size_t size = 0;

	if (!s_i->cur_cmd[1])
	{
		if (!home)
			return (free(pwd), 0);
		if (chdir(home->d_ptr))
			return (free(pwd), 2);
	}
	else if (s_i->cur_cmd[1][0] == '-')
	{
		if (chdir(s_i->prev_dir))
			return (free(pwd), 2);
	}
	else if (chdir(s_i->cur_cmd[1]))
		return (free(pwd), 2);

	free(s_i->prev_dir);
	s_i->prev_dir = pwd, pwd = NULL;
	pwd = getcwd(pwd, size);
	if (!pwd)
	{
		s_i->status = errno;
		return (0);
	}
	if (s_i->cur_cmd[1] && s_i->cur_cmd[1][0] == '-')
		_puts(pwd), _putchar('\n');
	_setenv(s_i, "PWD", pwd), free(pwd);
	_setenv(s_i, "OLDPWD", s_i->prev_dir);
	return (1);
}
