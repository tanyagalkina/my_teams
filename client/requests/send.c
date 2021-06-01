/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t send_req(char *input, client_t *cl)
{
    char **req_args;
    request_t new_req;
    (void)cl;

    if (!count_quotes(4, input))
        return bad_request(QUOTES);
    if (NULL == (req_args = get_args(input, 2)))
        return bad_request(BAD_INPUT);

    if (is_not_valid_uuid(req_args[0]))
        return bad_request(INVALID_UUID);

    strcpy(new_req.user_uuid, req_args[0]);
    strcpy(new_req.message, req_args[1]);
    new_req.type = CT_SEND;
    return new_req;
}