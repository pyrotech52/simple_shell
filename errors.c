#include "shell.h"

/**
 *_eputs - Prints an Inputed String
 * @str: String to be Printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int c = 0;

	if (!str)
		return;
	while (str[c] != '\0')
	{
		_eputchar(str[c]);
		++c;
	}
}
/**
 * _eputchar - WRITES the Character x to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[++i] = c;
	return (1);
}
/**
 *_putsfd - PRINT an Inputed String
 * @str: String to be Printed
 * @fd: Filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
/**
 * _putfd - WRITE the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[++i] = c;
	return (1);
}


