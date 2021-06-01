/*
** EPITECH PROJECT, 2020
** my_teams
** File description:
** client/src
*/

#include "../include/client.h"

void init_client_stuff(client_t *client_stuff, int sock)
{
    client_stuff->sd = sock;
    client_stuff->context.context_level = TEAM;
    client_stuff->bytes = 0;
    client_stuff->logged_in = 0;
    client_stuff->own_name[0] = '\0';
    FD_ZERO(&client_stuff->master);
    FD_ZERO(&client_stuff->reading);
    FD_SET(sock, &client_stuff->master);
    FD_SET(0, &client_stuff->master);
}