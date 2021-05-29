/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include "../include/server.h"
#include "../include/commons.h"
#include <string.h>
#include <sys/queue.h>

team_t *get_team_by_uuid(server_t *server, const char *uuid)
{
    team_t *team;
    TAILQ_FOREACH(team, &server->admin->team_head, next) {
        if (strcmp(team->info->team_uuid, uuid) == 0) {
            return team;
        }
    }
    server_debug_print(INFO, "There is no team with that uuid");
    return NULL;
}
