/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include "../../include/commands.h"
#include <string.h>

bool if_user_exists(server_t *server, const char *name)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (strcmp(user->info->user_name, name) == 0) {
            return true;
        }
    }
    return false;
}

void error_not_exist(const char *uuid, user_t *user, int code, int level)
{
    response_t r;
    user_fds_t *fds;

    r.status_code = code;
    r.level = level;
    r.request_type = CT_CREATE;
    strcpy(r.team_uuid, uuid);

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

bool create_new_channel_is_authorized(team_t *team, const char *user_uuid)
{
    team_user_info_t *info;

    TAILQ_FOREACH(info, &team->user_info_head, next) {
        if (strcmp(info->user_uuid, user_uuid) == 0)
            return true;
    }
    return false;
}

void error_unauthorized(user_t *user)
{
    response_t r;
    user_fds_t *fds;

    r.status_code = KO_UNAUTHOR;
    r.level = CHANNEL;
    r.request_type = CT_CREATE;

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

void error_already_exist(user_t *user)
{
    response_t r;
    user_fds_t *fds;

    r.status_code = KO_ERROR_EXISTS;
    r.level = CHANNEL;
    r.request_type = CT_CREATE;

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}
