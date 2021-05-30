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

static int how_many_teams(server_t *server)
{
    int counter = 0;
    team_t *team;

    TAILQ_FOREACH(team, &server->admin->team_head, next) {
        counter++;
    }
    return counter;
}

static void send_status(server_t *server, user_t *user)
{
    response_t r;
    user_fds_t *fds;

    r.request_type = CT_LIST;
    r.status_code = STATUS_OK;
    r.extern_body_size = how_many_teams(server);
    r.extern_body_type = TEAM_TYPE;

    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

static void list_teams(server_t *server, int fd)
{
    response_t r;
    team_t *team = NULL;
    user_fds_t *fds;
    user_t *user = get_user_by_fd(server, fd);
    send_status(server, user);

    TAILQ_FOREACH(team, &server->admin->team_head, next) {
        r.request_type = CT_LIST;
        r.status_code = STATUS_OK;
        strcpy(r.team_uuid, team->info->team_uuid);
        strcpy(r.name, team->info->team_name);
        strcpy(r.description, team->info->team_description);
        printf("teamname: %s\n", team->info->team_name);
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            send(fds->fd, &r, RESPONSE_SIZE, 0);
        }
    }
}

int cmd_list(server_t *server, request_t *req, int fd)
{
    switch(req->context_level) {
        case TEAM:
            server_debug_print(ERROR, "listing teams");
            list_teams(server, fd);
            break;
    }
    printf("the context level was %d\n", req->context_level);
    //printf("the name was %s\n", req->name);
    //printf("description was %s\n", req->description);
    return SUCCESS;
}
