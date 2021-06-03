/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

static int not_only_spases(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            return (1);
        ++i;
    }
    return (0);
}

char **get_args(char *input, int nb_args)
{
    int count = 0;
    char **result = malloc(sizeof(char *) * nb_args);
    char delim[] = {'"', 0};
    char *token;
    if (!count_quotes(nb_args * 2, input))
        return (NULL);
    token =  strtok(input, delim);
    while (count < nb_args && token != NULL) {
        token = strtok(NULL, delim);
        if (token != NULL && not_only_spases(token)) {
            result[count] = strdup(token);
            ++count;
        }
    }
    if (count == nb_args)
        return (result);
    return (NULL);
}

request_t bad_request(char *comment)
{
    request_t new_req;
    new_req.type = 84;
    strcpy(new_req.message, comment);
    return new_req;
}

int count_quotes(int nb_quotes, char *input)
{
    int i = 0;
    int count = 0;
    while (input[i])
    {
        if (input[i] == '"')
            ++count;
        ++i;
    }
    if (nb_quotes == count)
        return (1);
    return (0);
}

int is_not_valid_uuid(char *str)
{
    uuid_t test_uuid;
    return (0);
}