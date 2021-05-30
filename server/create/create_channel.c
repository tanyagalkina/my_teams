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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

channel_t *get_channel_by_name(team_t *team, const char *name)
{
    channel_t *ch;
    TAILQ_FOREACH(ch, &team->channel_head, next) {
        if (strcmp(ch->info->channel_name, name) == 0) {
            return ch;
        }
    }
    server_debug_print(WARNING, "There is no channel with that name in this \
team");
    return NULL;
}

static bool is_user_in_team(user_t *user, const char *team_uuid)
{
    user_subscribed_teams_t *team;

    TAILQ_FOREACH(team, &user->subscribed_teams_head, next) {
        if (strcmp(team->team_uuid, team_uuid) == 0)
            return true;
    }
    return false;
}

static void send_to_all(server_t *server, team_t *team, channel_t *ch)
{
    user_t *user;
    user_fds_t *fds;
    response_t r;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (!is_user_in_team(user, ch->info->channel_uuid))
            continue;
        strcpy(r.channel_uuid, ch->info->channel_uuid);
        strcpy(r.name, ch->info->channel_name);
        strcpy(r.description, ch->info->channel_description);
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

static int add_new_channel(team_t *team, request_t *req)
{
    channel_t *ch;
    channel_info_t *info;
    uuid_t binuuid;

    if ((ch = malloc(sizeof(channel_t))) == NULL)
        return FAILURE;
    if ((ch->info = malloc(sizeof(channel_info_t))) == NULL)
        return FAILURE;

    TAILQ_INIT(&ch->thread_head);
    uuid_generate_random(binuuid);
    strcpy(ch->info->channel_name, req->name);
    strcpy(ch->info->channel_description, req->description);
    uuid_unparse(binuuid, ch->info->channel_uuid);
    server_event_channel_created(team->info->team_uuid, \
ch->info->channel_uuid, ch->info->channel_name);
    TAILQ_INSERT_TAIL(&team->channel_head, ch, next);
    return SUCCESS;
}

static void team_not_exist(const char *team_uuid, user_t *user)
{
    response_t r;
    user_fds_t *fds;

    r.status_code = KO_UNKN_TEAM;
    r.level = CHANNEL;
    r.request_type = CT_CREATE;
    strcpy(r.team_uuid, team_uuid);

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

static void team_unauthorized(user_t *user)
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

static void channel_already_exist(user_t *user)
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

void create_new_channel(server_t *server, request_t *req, int fd)
{
    team_t *team = NULL;
    const char *ch_name = req->name;
    const char *ch_desc = req->description;

    if ((team = get_team_by_uuid(server, req->team_uuid)) == NULL) {
        team_not_exist(req->team_uuid, get_user_by_fd(server, fd));
        return;
    }
    if (get_channel_by_name(team, ch_name)) {
        server_debug_print(WARNING, "This channel already exists");
        return;
    }
    add_new_channel(team, req);
}
