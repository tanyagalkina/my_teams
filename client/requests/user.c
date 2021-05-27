/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t user_req(char *user_req, char *input, client_t *cl)
{
    request_t new_req;
    char **req_args;
    (void)cl;

    if (!count_quotes(2, input))
        return bad_request(QUOTES);
    if (NULL == (req_args = get_args(input, 1)))
        return bad_request(BAD_INPUT);

    new_req.type = CT_USER;
    strcpy(new_req.user_uuid, req_args[0]);
    return new_req;
}