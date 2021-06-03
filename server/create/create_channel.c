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
        r.request_type = ET_CHANNEL_CREAT;
        strcpy(r.team_uuid, team->info->team_uuid);
        strcpy(r.channel_uuid, ch->info->channel_uuid);
        strcpy(r.name, ch->info->channel_name);
        strcpy(r.description, ch->info->channel_description);
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

static int add_new_channel(server_t *server, team_t *team, \
request_t *req, int fd)
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
    send_to_all(server, team, ch);
    channel_send_response(team, ch, fd);
    return SUCCESS;
}

void create_new_channel(server_t *server, request_t *req, int fd)
{
    team_t *team = NULL;
    user_t *user = get_user_by_fd(server, fd);
    const char *ch_name = req->name;
    const char *ch_desc = req->description;

    if ((team = get_team_by_uuid(server, req->team_uuid)) == NULL) {
        error_not_exist(req->team_uuid, user, KO_UNKN_TEAM, CHANNEL);
        return;
    }
    if (get_channel_by_name(team, ch_name)) {
        error_already_exist(user);
        return;
    }
    if (!create_new_channel_is_authorized(team, user->info->user_uuid)) {
        error_unauthorized(fd);
        return;
    }
    add_new_channel(server, team, req, fd);
}