#include "shell.h"

/**
 **_strncpy - String Copied
 *@dest: Destination of String to be Copied to
 *@src: Source string
 *@n: Amount of Characters to be copied
 *Return: Concatenated of the strings
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		++a;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			++b;
		}
	}
	return (s);
}
/**
 **_strncat -Two strings are Concatenated
 *@dest: First string
 *@src: Second string
 *@n: Amount of bytes to be maximally used
 *Return: Concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		++a;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		++a;
		++b;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}
/**
 **_strchr - Character in a String are located
 *@s: String to be parsed
 *@c: Character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
