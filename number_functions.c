#include "shell.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Return: int
 */
int _atoi(char *s)
{
	unsigned int i = 0, n = 0, sign = 1;
	int ans, flag;

	flag = 0;
	while (s[i] != '\0' && !flag)
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
			flag = 1;
		if (!flag)
			i++;
	}
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		n *= 10;
		n += s[i] - '0';
		i++;
	}
	ans = n * sign;
	return (ans);
}

/**
 * digits_counter - counts digits of a number
 * @num: number to look into
 * Return: number of digits
 */
unsigned int digits_counter(unsigned long num)
{
	unsigned int d = 0;

	while (num > 0)
	{
		num /= 10;
		d++;
	}

	return (d < 1 ? 1 : d);
}

/**
 * convertUnsignedNum - converts unsigned number to string
 * @num: unsigned number to be converted
 * Return: string representation of the number
 */
char *convertUnsignedNum(unsigned long num)
{
	char *c;
	unsigned int i, d;

	d = digits_counter(num);
	c = malloc(sizeof(char) * (d + 1));
	if (!c)
		return (NULL);

	if (num == 0)
		c[0] = '0';
	else
	{
		for (i = 0; i < d; i++)
		{
			c[d - i - 1] = (num % 10) + '0';
			num /= 10;
		}
	}

	c[d] = '\0';
	return (c);
}

/**
 * _isPositiveNumber - checks if a string is actually a positive number
 * @str: string to be checked
 * Return: 1 if string is a number, 0 if not
 */
int _isPositiveNumber(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
