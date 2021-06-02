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

static user_t *init_user(void)
{
    user_t *user = NULL;
    if ((user = (user_t *)malloc(sizeof(user_t))) == NULL)
        return NULL;
    if ((user->info = (user_info_t *)malloc(sizeof(user_info_t))) == NULL)
        return NULL;
    TAILQ_INIT(&user->subscribed_teams_head);
    TAILQ_INIT(&user->user_fds_head);

    return user;
}

static void load_team_for_user(FILE *file, user_t *user)
{
    char *line = NULL;
    size_t len = 0;
    user_subscribed_teams_t *sub = NULL;

    while (getline(&line, &len, file) != -1) {
        if (strncmp(line, "--- Teams End ---", 17) == 0)
            return;
        if (strncmp(line, "--- Teams Start ---", 19) == 0)
            continue;
        sub = malloc(sizeof(user_subscribed_teams_t));
        sscanf(line, "%36[^,],", sub->team_uuid);
        TAILQ_INSERT_TAIL(&user->subscribed_teams_head, sub, next);
    }
}

void restore_users(server_t *server)
{
    FILE *file = NULL;
    user_t *user = NULL;
    char *line = NULL;
    size_t len = 0;

    if ((file = fopen("save_users.txt", "r")) == NULL) {
        server_debug_print(WARNING, "No database file for 'users' found");
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if ((user = init_user()) == NULL)
            return;
        sscanf(line, "uuid:%36[^,],name:%32[^,]", user->info->user_uuid, \
user->info->user_name);
        load_team_for_user(file, user);
        server_event_user_loaded(user->info->user_uuid, user->info->user_name);
        TAILQ_INSERT_TAIL(&server->admin->user_head, user, next);
    }
    fclose(file);
}
