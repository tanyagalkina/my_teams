/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t subscribed_req(char *user_req, char *input, use_level_t *context_level)
{
    request_t new_req;
    char **req_args;
    if (count_quotes(2, input)) {
        if (NULL == (req_args = get_args(input, 1)))
            return bad_request(BAD_INPUT);
        if (is_not_valid_uuid(req_args[0]))
            return bad_request(INVALID_UUID);

        new_req.type = SUBSCRIBED_UUID;
        strcpy(new_req.uuid, req_args[0]);
    }
    else if (count_quotes(0, input)) {
        new_req.type = SUBSCRIBED_BLANK;
    }
    else
        return bad_request(BAD_INPUT);
    return new_req;
}