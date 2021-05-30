/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>

static bool is_subscribed_to_team(server_t *server, request_t *req, int fd)
{
    user_subscribed_teams_t *sub;
    user_t *user = get_user_by_fd(server, fd);
    TAILQ_FOREACH(sub, &user->subscribed_teams_head, next) {
        if (strcmp(sub->team_uuid, req->team_uuid) == 0) {
            server_debug_print(INFO, "User is already subscribed to the team");
            return true;
        }
    }
    return false;
}

static int append_team_to_user(user_t *user, const char *team_uuid)
{
    user_subscribed_teams_t *sub = malloc(sizeof(user_subscribed_teams_t));
    if (!sub)
        return FAILURE;

    strcpy(sub->team_uuid, team_uuid);
    TAILQ_INSERT_TAIL(&user->subscribed_teams_head, sub, next);
    return SUCCESS;
}

static int append_user_to_team(team_t *team, const char *user_uuid)
{
    team_user_info_t *info = NULL;

    if ((info = malloc(sizeof(team_user_info_t))) == NULL)
        return FAILURE;

    strcpy(info->user_uuid, user_uuid);
    TAILQ_INSERT_TAIL(&team->user_info_head, info, next);

    return SUCCESS;
}

int cmd_subscribe(server_t *server, request_t *req, int fd)
{
    user_t *user = get_user_by_fd(server, fd);
    const char *user_name = user->info->user_name;
    team_t *team = get_team_by_uuid(server, req->team_uuid);

    if (!team)
        return FAILURE;
    if (is_subscribed_to_team(server, req, fd))
        return FAILURE;
    if (append_team_to_user(user, req->team_uuid) == FAILURE)
        return FAILURE;
    if (append_user_to_team(team, user->info->user_uuid) == FAILURE)
        return FAILURE;
    server_event_user_subscribed(req->team_uuid, user_name);
    return SUCCESS;
}
