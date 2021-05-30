/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t login_req(char *user_req, char *input, client_t *cl)
{
    request_t new_req;
    char **req_args;
    (void)cl;

    if (!count_quotes(2, input))
        return bad_request(QUOTES);
    if (NULL == (req_args = get_args(strdup(input), 1)))
        return (bad_request(BAD_INPUT));
    printf("first arg: %s\n", req_args[0]);

    new_req.type = CT_LOGIN;
    strcpy(new_req.name, strdup(req_args[0]));
    if (cl->own_name[0] == '\0') {
        strcpy(cl->own_name, strdup(req_args[0]));
        cl->logged_in = 1;
        free (req_args);
        return new_req;
    } else {
        free (req_args);
        return (bad_request(ONE_USER));
    }

}