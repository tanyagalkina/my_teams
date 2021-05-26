/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t send_req(char *user_req, char *input, use_level_t *context_level)
{
    request_t new_req;
    if (!count_quotes(4, input))
        return bad_request("please, include all the arguments in quotes\n");
    char **req_args = get_args(input, 2);
    if (is_not_valid_uuid(req_args[0]))
        return bad_request("given uuid is not valid\n");

    strcpy(new_req.uuid, strdup(req_args[0]));
    strcpy(new_req.message, strdup(req_args[1]));
    new_req.type = SEND;
    return new_req;
}