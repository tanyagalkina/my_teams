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

void save_users(server_t *server)
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
        fprintf(file, "uuid:%s,name:%s,\n", user->info->user_uuid, \
user->info->user_name);
        fprintf(file, "--- Teams Start ---\n");
        TAILQ_FOREACH(team, &user->subscribed_teams_head, next) {
            fprintf(file, "%s,\n", team->team_uuid);
        }
        fprintf(file, "--- Teams End ---\n");
    }
}
