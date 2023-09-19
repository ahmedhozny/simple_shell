#include "shell.h"
#include <stdio.h>

/**
 * variable_rep - variable replacement
 * @s_i: session info
 *
 * Return: 1 on Success, 0 Otherwise
 */
int variable_rep(s_info *s_i)
{
	int i, j, k, size = 1, var_size = 0;
	char **cmd = s_i->cur_cmd, *tmp = NULL, *new_cmd = NULL, *rep = NULL,
			 add = -1;
	node *var = NULL;

	for (i = 0; cmd[i]; i++)
	{
		for (j = 0; cmd[i][j] != '\0'; j++)
		{
			if (cmd[i][j] != '$' || (cmd[i][j] == '$' && cmd[i][j + 1] == '\0'))
				continue;
			if (cmd[i][j + 1] == '$')
				rep = convertUnsignedNum((unsigned long)getpid());
			else if (cmd[i][j + 1] == '?')
				rep = convertUnsignedNum((unsigned long)s_i->status);
			else
			{
				for (k = j + 1; isValidName(cmd[i][k]); k++)
					var_size++;
				add = cmd[i][k], cmd[i][k] = '\0', var = _getenv(s_i, cmd[i] + j + 1);
				if (add != '\0')
					size++;
				if (var)
					rep = _strdup(var->d_ptr);
			}
			cmd[i][j] = '\0';
			if (!rep)
				return (0);
			tmp = _strcat(cmd[i], rep, -1), free(rep);
			if (!tmp)
				return (0);
			size += var_size ? var_size : 1;
			new_cmd = _strcat(tmp, cmd[i] + j + size, add), free(tmp);
			if (!new_cmd)
				return (0);
			free(cmd[i]), cmd[i] = new_cmd;
		}
	}
	return (1);
}
