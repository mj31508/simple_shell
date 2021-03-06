#include "shell.h"

/**
 * _strlen - counts characters in string
 * @str: string to count characters from
 * Return: string's char count
 */
int _strlen(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}

/**
 * _strcmp - compares two strings for equality
 *
 * @s1: first string in comparison
 * @s2: second string in comparison
 *
 * Return: 0 if equal; 1 if not equal
 */

int _strcmp(char *s1, char *s2)
{
	for ( ; *s1 && (*s1 == *s2); s1++, s2++)
		;
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - duplicates a string to a newly allocated space
 * @str: string to duplicate
 * Return: returns pointer to duplicated string
 */
char *_strdup(char *str)
{
	char *dupe;

	if (!str)
		return (NULL);
	dupe = malloc(_strlen(str) + 1);
	if (!dupe)
		return (NULL);
	_strcpy(dupe, str);
	return (dupe);
}

/**
 * _strcat - concatenates two strings
 * @src: first string
 * @dest: second string
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int len, dlen, i;

	len = _strlen(src);
	dlen = _strlen(dest);
	for (i = 0; i < len && src[i] != '\0'; i++)
		dest[dlen + i] = src[i];
	dest[dlen + i] = '\0';
	return (dest);
}

/**
 * _strcpy - copy a string
 * @dest: string output
 * @src: string input
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int i, j;

	i = _strlen(src);
	for (j = 0; j < i; j++)
		dest[j] = src[j];
	dest[j] = '\0';
	return (dest);
}
