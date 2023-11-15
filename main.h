#ifndef __HEADER__

#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int _strlen(char *s);
char *_strdup(char *str);
char **split(char *string, const char *del, int *counter);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, unsigned int n);
char* _cat3(char* str1, char* str2, char* str3);



#endif
