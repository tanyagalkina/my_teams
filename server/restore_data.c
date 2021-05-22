/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <stdlib.h>
#include <stdio.h>

static void restore_teams(server_t *server)
{
    FILE *file = NULL;
    team_t *new_team = NULL;
    char *line = NULL;
    size_t len = 0;

    if ((file = fopen("save_teams.txt", "r")) == NULL) {
        server_debug_print(WARNING, "No database file for 'teams' found");
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if ((new_team = (team_t *)malloc(sizeof(team_t))) == NULL)
            return;
        sscanf(line, "%36[^,],%32[^,]", new_team->uuid, new_team->name);
        TAILQ_INSERT_TAIL(&server->admin->team_head, new_team, next);
    }
    fclose(file);
}

void restore_data(server_t *server)
{
    server_debug_print(INFO, "Starting getting the data");
    restore_teams(server);
    server_debug_print(INFO, "Done with getting the data");
}
