/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t logout_req(char *user_req, char *args, client_t *cl)
{
    request_t new_req;
    (void)cl;

    new_req.type = LOGOUT;
    return new_req;
}