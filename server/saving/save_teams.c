/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../../include/server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

//@todo add channels to the saved file just like in save_users with subs
void save_teams(server_t *server)
{
    FILE *file = NULL;
    team_t *tmp = NULL;
    server_debug_print(INFO, "saving teams ...");

    if ((file = fopen("save_teams.txt", "w")) == NULL) {
        server_debug_print(ERROR, "Cannot open database file (write teams)");
        return;
    }

    TAILQ_FOREACH(tmp, &server->admin->team_head, next) {
        fprintf(file, "uuid:%s,name:%s,desc:%s,\n", tmp->info->team_uuid, \
tmp->info->team_name, tmp->info->team_description);
    }
}
