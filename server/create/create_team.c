/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

static void send_to_all(server_t *server, team_t *team)
{
    user_t *user;
    user_fds_t *fds;
    response_t r;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        r.request_type = ET_TEAM_CREAT;
        strcpy(r.team_uuid, team->info->team_uuid);
        strcpy(r.name, team->info->team_name);
        strcpy(r.description, team->info->team_description);
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

static void send_response(server_t *server, team_t *team, int fd)
{
    response_t r;
    user_fds_t *fds;
    r.request_type = CT_CREATE;
    r.level = TEAM;
    strcpy(r.team_uuid, team->info->team_uuid);
    strcpy(r.name, team->info->team_name);
    strcpy(r.description, team->info->team_description);
    send(fd, &r, RESPONSE_SIZE, 0);
}

static bool team_already_exists(server_t *server, const char *team_name)
{
    team_t *team;

    TAILQ_FOREACH(team, &server->admin->team_head, next) {
        if (strcmp(team->info->team_name, team_name) == 0) {
            return true;
        }
    }
    return false;
}

static int send_error_response(server_t *server, int fd)
{
    response_t r;

    r.status_code = KO_ERROR_EXISTS;
    r.request_type = CT_CREATE;
    r.level = TEAM;
    send(fd, &r, RESPONSE_SIZE, 0);

    return SUCCESS;
}

int create_new_team(server_t *server, request_t *req, int fd)
{
    team_t *team;
    uuid_t binuuid;
    const char *user_uuid = get_user_by_fd(server, fd)->info->user_uuid;

    if (team_already_exists(server, req->name))
        return send_error_response(server, fd);
    if ((team = malloc(sizeof(team_t))) == NULL) return FAILURE;
    if ((team->info = malloc(sizeof(team_info_t))) == NULL) return FAILURE;
    TAILQ_INIT(&team->channel_head);
    TAILQ_INIT(&team->user_info_head);
    uuid_generate_random(binuuid);
    strcpy(team->info->team_name, req->name);
    strcpy(team->info->team_description, req->description);
    uuid_unparse(binuuid, team->info->team_uuid);
    server_event_team_created(team->info->team_uuid, req->name, user_uuid);
    send_to_all(server, team);
    send_response(server, team, fd);
    TAILQ_INSERT_TAIL(&server->admin->team_head, team, next);
    return SUCCESS;
}
