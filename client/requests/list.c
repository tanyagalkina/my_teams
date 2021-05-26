/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t list_req(char *user_req, char *args, client_t *cl)
{
    request_t new_req;

    new_req.type = LIST;
    return new_req;
}