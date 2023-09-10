#include "shell.h"

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
 * @x: unsigned number to be converted
 * Return: string representation of the number
 */
char *convertUnsignedNum(unsigned long num)
{
	char *c;
	unsigned int i, d;

	if (num == 0)
		return ((char *) '0');
	d = digits_counter(num);

	c = malloc(sizeof(char) * (d + 1));
	if (!c)
	{
		free(c);
		return (0);
	}

	for (i = 0; i < d; i++)
	{
		c[d - i - 1] = (num % 10) + '0';
		num /= 10;
	}

	c[d] = '\0';
	return (c);
}
