/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../../include/client.h"

request_t unsubscribe_req(char *user_req, char *args, use_level_t *context_level)
{
    request_t new_req;

    new_req.type = UNSUBSCRIBE;
    return new_req;
}