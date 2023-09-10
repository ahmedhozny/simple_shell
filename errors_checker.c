#include "shell.h"

int command_validity_checker(s_info s_i, char *cmd, int print_error)
{
	char *temp;

	if (!cmd)
	{
		s_i.status = 127;
		if (print_error)
		{
			/* pwd needed */
			_puts("[PWD here]");
			_puts(": ");
			temp = convertUnsignedNum(s_i.iter_num);
			_puts(temp);
			free(temp);
			_puts(": ");
			_puts(cmd);
			_puts(": not found");
			_puts("\n");
		}
		return (-1);
	}
	s_i.status = 0;
	return (0);
}
