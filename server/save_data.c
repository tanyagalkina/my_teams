/*
** EPITECH PROJECT, 2019
** server
** File description:
** server
*/

#include "../include/server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <sys/types.h>

static void save_teams(server_t *server)
{
    FILE *file = NULL;
    team_t *tmp = NULL;
    server_debug_print(INFO, "saving teams ...");

    if ((file = fopen("save_teams.txt", "w")) == NULL) {
        server_debug_print(ERROR, "Cannot open database file (write teams)");
        return;
    }

    TAILQ_FOREACH(tmp, &server->admin->team_head, next) {
        fprintf(file, "uuid:%s,name:%s,\n", tmp->info->team_uuid, \
tmp->info->team_name);
    }
}

static void saving_users(server_t *server)
{
    FILE *file = NULL;
    user_t *user = NULL;
    user_subscribed_teams_t *team = NULL;

    server_debug_print(INFO, "saving users ...");
    if ((file = fopen("save_users.txt", "w")) == NULL) {
        server_debug_print(ERROR, "Cannot open database file (write users)");
        return;
    }

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        fprintf(file, "uuid:%s,name:%s,\nteams:", user->info->user_uuid, \
user->info->user_name);
        TAILQ_FOREACH(team, &user->subscribed_teams_head, next) {
            fprintf(file, "%s,", team->team_uuid);
        }
        fprintf(file, "\n");
    }
}

void save_data(server_t *server)
{
    server_debug_print(INFO, "starting to save now");
    saving_users(server);
}
