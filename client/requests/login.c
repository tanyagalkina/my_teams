/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t login_req(char **user_req, use_level_t *context_level)
{
    request_t new_req;

    new_req.type = LOGIN;
    strcpy(new_req.name, user_req[1]);
    return new_req;
}