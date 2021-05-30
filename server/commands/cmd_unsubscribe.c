/*
** EPITECH PROJECT, 2020
** commons
** File description:
** myteams
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <sys/queue.h>
#include <string.h>
#include <stdio.h>

static int unsubscribe_from_team(user_t *user, const char *team_uuid)
{
    user_subscribed_teams_t *team;
    bool found = false;
    TAILQ_FOREACH(team, &user->subscribed_teams_head, next) {
        if (strcmp(team->team_uuid, team_uuid) == 0) {
            found = true;
            break;
        }
    }
    if (found == false) {
        server_debug_print(WARNING, "There is no team with that uuid");
        return FAILURE;
    }

    TAILQ_REMOVE(&user->subscribed_teams_head, team, next);
    return SUCCESS;
}

static int delete_user_from_team(const char *user_uuid, team_t *team)
{
    team_user_info_t *info;
    team_user_info_t *to_del;

    TAILQ_FOREACH(info, &team->user_info_head, next) {
        if (strcmp(info->user_uuid, user_uuid) == 0) {
            to_del = info;
        }
    }

    TAILQ_REMOVE(&team->user_info_head, to_del, next);
    return SUCCESS;
}

int cmd_unsubscribe(server_t *server, request_t *req, int fd)
{
    user_t *user = get_user_by_fd(server, fd);
    const char *team_uuid = req->team_uuid;

    printf("Trying to unsub from this team #%s#\n", team_uuid);
    if (!user)
        return FAILURE;

    if (unsubscribe_from_team(user, team_uuid) == FAILURE)
        return FAILURE;

    server_event_user_unsubscribed(team_uuid, user->info->user_uuid);
    return SUCCESS;
}
