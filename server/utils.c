/*
** EPITECH PROJECT, 2019
** utils
** File description:
** utils
*/

#include <stdlib.h>
#include <string.h>

void free_2d(char **s)
{
    for (int i = 0; s[i]; i++) {
        char *cur = s[i];
        free(cur);
    }
    free(s);
}

static char *cut_string(char *str)
{
    for (int i = 0; str[i + 1]; i++) {
        if (str[i] == '\r' && str[i + 1] == '\n') {
            str[i] = '\0';
            return str;
        }
    }
    return str;
}

static int how_many_parts(char *str, const char delimiter)
{
    str = cut_string(str);
    int count = 0;
    char *last_delim = NULL;
    char *tmp = str;

    while (*tmp) {
        if (delimiter == *tmp) {
            count++;
            last_delim = tmp;
        }
        tmp++;
    }
    count += last_delim < (tmp + strlen(tmp) - 1);
    return count;
}

char **split_string(char *str)
{
    char **result = NULL;
    int idx = 0;
    char delim[2] = {' ', 0 };
    int parts = how_many_parts(str, ' ');

    result = (char **)malloc(sizeof(char *) * (parts + 1));

    if (!result)
        return NULL;

    char *token = strtok(str, delim);
    while (token) {
        *(result + idx++) = strdup(token);
        token = strtok(0, delim);
    }
    *(result + idx) = 0;
    return result;
}
