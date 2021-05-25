/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

int not_only_spases(char *str)
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
    char delim[] = {'"'};
    char *token =  strtok(input, delim);
    char **result = malloc(sizeof(char *) * nb_args);

    while (count < nb_args && token != NULL) {
        token = strtok(NULL, delim);
        if (token != NULL && not_only_spases(token)) {
           result[count] = strdup(token);
           ++count;
        }
    }
    if (count == nb_args)
        return result;
    return (NULL);
}

request_t bad_request(void)
{
    request_t new_req;
    new_req.type = 84;
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
    return (0);
}

request_t send_req(char *user_req, char *input, use_level_t *context_level)
{
    request_t new_req;
    if (!count_quotes(4, input))
        return bad_request();
    char **req_args = get_args(input, 2);
    if (is_not_valid_uuid(req_args[0]))
        return bad_request();

    strcpy(new_req.uuid, strdup(req_args[0]));
    strcpy(new_req.message, strdup(req_args[1]));
    new_req.type = SEND;
    return new_req;
}