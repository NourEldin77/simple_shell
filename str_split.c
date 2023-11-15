#include "main.h"
#include <string.h>

/**
 * _strcpy - copy str
 * @src: source
 * @dest: destination
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strlen - get length of string
 * @s: string
 * Return: num
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; *s != '\0'; ++s)
	{
		++i;
	}
	return (i);
}

int _strcmp(char *str1, char *str2)
{
	int str1_len = _strlen(str1), str2_len = _strlen(str2);
	int i = 0;

	if (str1 == NULL || str2 == NULL)
	{
		return (-1);
	}	
	if (str1_len - str2_len == 0)
	{
		while (str1[i] == str2[i] && str1[i] != '\0')
		{
			i++;
		}
		return ((i == str1_len && i == str2_len) ? 0 : 1);
	}
	else
	{
		return (1);
	}
}

int _strncmp(char *str1, char *str2, unsigned int n)
{
	unsigned int i = 0;

	if (str1 == NULL || str2 == NULL || n == 0)
	{
		return (-1);
	}
	while (str1[i] == str2[i] && i < n && str1[i] != '\0')
	{
			i++;
	}

	return (i == n || (i < n && str1[i] == str2[i]) ? 0 : str1[i] - str2[i]);
}

char* _cat3(char* str1, char* str2, char* str3)
{
	int str_len1 = _strlen(str1), str_len2 = _strlen(str2),
		str_len3 = _strlen(str3);
	int full_len = str_len1 + str_len2 + str_len3, i;
	char* full_string = malloc((full_len + 1) * sizeof(char));

    for (i = 0; i < full_len; i++)
    {
        while (*str1 != '\0')
        {
            full_string[i] = *str1;
            str1++;
            i++;
        }
        while (*str2 != '\0')
        {
            full_string[i] = *str2;
            str2++;
            i++;
        }
        while (*str3 != '\0')
        {
            full_string[i] = *str3;
            str3++;
            i++;
        }
    }

    full_string[full_len] = '\0';
    return (full_string);
}

char *_strdup(char *str)
{
	int i = 0;
	int duplen = strlen(str);
	char *dup = (char *)malloc((duplen + 1) * sizeof(char));

	if (dup != NULL)
	{
		while (i < duplen)
		{
			dup[i] = str[i];
			i++;
		}
		dup[duplen] = '\0';
	}

	return (dup);
}

char **split(char *string, const char *del, int *toknum)
{
	char *dup_str = _strdup(string), *word = strtok(dup_str, del);
	char **arr_of_str;	
	int i, j;

	*toknum = 0;
	if (dup_str == NULL)
	{
		free(dup_str);
		perror("duplicate");
		exit(EXIT_FAILURE);
	}
	word = strtok(dup_str, del);
	while (word != NULL)
	{
		(*toknum)++;
		word = strtok(NULL, del);
	}

	arr_of_str = (char**)malloc((*toknum + 1) * sizeof(char*)); 

    if (arr_of_str == NULL)
    {
        perror("malloc1");
        free(dup_str);
        exit(EXIT_FAILURE);
    }

	_strcpy(dup_str, string);
	word = strtok(dup_str, del);
	for (i = 0; i < *toknum; i++)
	{
		while (*word == ' ')
		{
			word++;
		}
		arr_of_str[i] = _strdup(word);
		if (arr_of_str[i] == NULL)
        {
            perror("malloc2");
            for (j = 0; j < i; j++)
            {
                free(arr_of_str[j]);
            }
            free(arr_of_str);
            free(dup_str);
            exit(EXIT_FAILURE);
        }
		word = strtok(NULL, del);
	}
	arr_of_str[*toknum] = NULL;
	free (dup_str);
	return (arr_of_str);
}
