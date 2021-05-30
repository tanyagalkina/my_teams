/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../../include/server.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>
#include <string.h>

void restore_channel(FILE *file, team_t *team)
{
    channel_t *ch;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strncmp(line, "--- Channel End ---", 19) == 0)
            return;
        if (strncmp(line, "--- Channel Start ---", 21) == 0)
            continue;
        ch = malloc(sizeof(channel_t));
        ch->info= malloc(sizeof(channel_info_t));
        sscanf(line, "uuid:%36[^,],name:%32[^,],desc:%255[^,]", \
ch->info->channel_uuid, ch->info->channel_name, ch->info->channel_description);
        TAILQ_INSERT_TAIL(&team->channel_head, ch, next);
    }
}

static void setup_team(team_t *new_team, char *line)
{
    sscanf(line, "uuid:%36[^,],name:%32[^,],desc:%255[^,],", \
new_team->info->team_uuid, new_team->info->team_name, \
new_team->info->team_description);
    TAILQ_INIT(&new_team->channel_head);
    TAILQ_INIT(&new_team->user_info_head);
}

void restore_teams(server_t *server)
{
    FILE *file = NULL;
    team_t *team = NULL;
    char *line = NULL;
    size_t len = 0;

    if ((file = fopen("save_teams.txt", "r")) == NULL) {
        server_debug_print(WARNING, "No database file for 'teams' found");
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if ((team = (team_t *)malloc(sizeof(team_t))) == NULL)
            return;
        if ((team->info = malloc(sizeof(team_info_t))) == NULL)
            return;
        setup_team(team, line);
        restore_channel(file, team);
        TAILQ_INSERT_TAIL(&server->admin->team_head, team, next);
    }
    fclose(file);
}
