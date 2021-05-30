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
#include <sys/queue.h>

static void save_channels(team_t *team, FILE *file)
{
    channel_t *ch = NULL;

    fprintf(file, "--- Channel Start ---\n");

    TAILQ_FOREACH(ch, &team->channel_head, next) {
        fprintf(file, "uuid:%s,name:%s,desc:%s,\n", ch->info->channel_uuid, \
ch->info->channel_name, ch->info->channel_description);
    }
    fprintf(file, "--- Channel End ---\n");
}

void save_teams(server_t *server)
{
    FILE *file = NULL;
    team_t *team = NULL;
    server_debug_print(INFO, "saving teams ...");

    if ((file = fopen("save_teams.txt", "w")) == NULL) {
        server_debug_print(ERROR, "Cannot open database file (write teams)");
        return;
    }

    TAILQ_FOREACH(team, &server->admin->team_head, next) {
        fprintf(file, "uuid:%s,name:%s,desc:%s,\n", team->info->team_uuid, \
team->info->team_name, team->info->team_description);
        save_channels(team, file);
    }
}
