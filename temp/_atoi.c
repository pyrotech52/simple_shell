#include "shell.h"

/**
 * interactive - RETURN true if SHELL is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 *_isalpha - Check for Alphabetic Character
 *@c: Character to be  inputted
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * is_delim - CHECK if Character is a DELIMETER
 * @c: the char to CHECK
 * @delim: the DELIMETER String
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 *_atoi - CONVERT a String to INTEGER
 *@s: String to be Converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int c, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (c = 0;  s[c] != '\0' && flag != 2; c++)
	{
		if (s[c] == '-')
			sign *= -1;

		if (s[c] >= '0' && s[c] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[c] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
