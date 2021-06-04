/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void checkout(client_t *cl)
{
    request_t new_request;

    new_request.type = CT_LOGOUT;
    send(cl->sd, &new_request, sizeof(request_t), 0);
}
