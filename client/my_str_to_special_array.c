/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/client.h"

int is_sep(char c, char const *sep)
{
    for (int i = 0; sep[i]; i += 1)
        if (sep[i] == c)
            return (1);
    return (0);
}

int counts_words_special(char const *str, char const *sep)
{
    int counter = 0;

    for (int i = 0; str[i];) {
        while (str[i] && is_sep(str[i], sep))
            i++;
        counter++;
        while (str[i] && !is_sep(str[i], sep))
            i++;
    }
    return (counter);
}

int counts_character_special(char const *str, int toto, char const *sep)
{
    int counter = 0;
    for (int i = toto; str[i] && !is_sep(str[i], sep); i++) {
        counter++;
    }
    return (counter);
}

char **my_str_to_special_array(char const *str, char const *sep)
{
    int l = 0;
    int count_words = counts_words_special(str, sep);
    int string_length = 0;
    char **array = malloc(sizeof(char *) * (count_words + 1));

    for (int i = 0; str[i]; i++) {
        if (!is_sep(str[i], sep)) {
            string_length = counts_character_special(str, i, sep);
            array[l] = malloc(sizeof(char) * (string_length + 1));
            for (int c = 0; c < string_length; c++) {
                array[l][c] = str[i];
                i++;
            }
            array[l][string_length] = '\0';
            l++;
        }
        if (!str[i]) break;
    }
    array[l] = NULL;
    return (array);
}
