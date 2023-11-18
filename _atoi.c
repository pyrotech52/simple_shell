#include "shell.h"

/**
 * checkinteractivemode -check if the shell is in interactive mode
 * @info: address of a struct
 * Return: 1 if success else 0
*/
int checkinteractivemode(info_t *info)

{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isdelimiter - checks if a character is a delimeter
 * @c: character to check
 * @delim: delimiter string
 * Return: 1 if true else 0
*/

int isdelimiter(char c, char *delim)

{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * isalphabetic - check for alphabets
 * @c: the character to check
 * Return: 1 if alpha else 0
*/

int isalphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * convertstringstoint - converts strings to integers
 * @s: string to convert
 * Return: 0 is no int in string else converted numbers
*/

int convertstringstoint(char *s)
{
	int i, sign = 1, flag = 0, result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	return (sign == -1 ? -result : result);
}
