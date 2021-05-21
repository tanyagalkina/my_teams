/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdlib.h>
#include <stdio.h>

void clean_teams(server_t **server)
{
    team_t *tmp;

    while ((tmp = (team_t *)TAILQ_FIRST(&(*server)->admin->team_head))) {
        TAILQ_REMOVE(&(*server)->admin->team_head, tmp, next);
        free(tmp);
    }
}

void cleanup(server_t *server)
{
    clean_teams(&server);
    free(server->admin->teams);
    free(server->admin);
    free(server);
}
