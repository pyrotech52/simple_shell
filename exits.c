#include "shell.h"

/**
 * _strncpy - Custom implementation of string copy
 * @dest: Destination string
 * @src: Source string
 * @n: Number of characters to copy
 * Return: Pointer to the destination string
 */
char _strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	while (i < n)
	{
		dest[i++] = '\0';
	}

	return (dest);
}

/**
 * _strncat - Custom implementation of string concatenation
 * @dest: Destination string
 * @src: Source string
 * @n: Maximum number of characters to concatenate
 * Return: Pointer to the destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	 size_t dest_len = 0;
	size_t i;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	if (i < n)
	{
		dest[dest_len + i] = '\0';
	}

	return (dest);
}

/**
 * _strchr - Custom implementation of character search in a string
 * @s: Input string
 * @c: Character to search for
 * Return: Pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{

	while (*s != '\0')
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}
