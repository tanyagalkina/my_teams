/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t login_req(char *user_req, char *input, use_level_t *context_level)
{
    request_t new_req;
    if (!count_quotes(2, input))
        return bad_request("please, include all the arguments in quotes\n");
    char **req_args = get_args(input, 1);

    new_req.type = LOGIN;
    strcpy(new_req.name, req_args[0]);
    return new_req;
}