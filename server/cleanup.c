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
    free((*server)->admin->teams);
}

void clean_users(server_t **server)
{
    user_t *tmp;

    while ((tmp = (user_t *)TAILQ_FIRST(&(*server)->admin->user_head))) {
        TAILQ_REMOVE(&(*server)->admin->user_head, tmp, next);
        free(tmp->info);
        free(tmp);
    }
    free((*server)->admin->users);
}

void cleanup(server_t *server)
{
    clean_teams(&server);
    free(server->admin->teams);
    free(server->admin);
    free(server);
}
