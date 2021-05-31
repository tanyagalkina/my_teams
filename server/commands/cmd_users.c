/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <string.h>

static int how_many_users(server_t *server)
{
    user_t *user = NULL;
    int counter = 0;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        counter++;
    }
    return counter;
}

static void send_status(server_t *server, int fd)
{
    response_t r;
    user_fds_t *fds;

    r.request_type = CT_USERS;
    r.status_code = STATUS_OK;
    r.extern_body_size = how_many_users(server);
    r.extern_body_type = USER_TYPE;
    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

static void send_each(user_info_t *info, int fd, server_t *server)
{
    user_info_t u;
    user_fds_t *fds;

    strcpy(u.user_name, info->user_name);
    strcpy(u.user_uuid, info->user_uuid);
    u.user_status = info->user_status;

    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &u, sizeof(user_info_t), 0);
    }
}

static void send_response(server_t *server, int fd)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        send_each(user->info, fd, server);
    }
}

/* @todo implement this in client and ask how this should be. Think about if i can put this into the generic error functions */
static void cmd_users_unauthorized(int fd)
{
    response_t r;

    r.status_code = KO_UNAUTHOR;
    r.request_type = CT_USERS;

    send(fd, &r, RESPONSE_SIZE, 0);
}

int cmd_users(server_t *server, request_t *req, int fd)
{
    if (get_user_by_fd(server, fd) == NULL) {
        cmd_users_unauthorized(fd);
        return SUCCESS;
    }
    send_status(server, fd);
    send_response(server, fd);
    return SUCCESS;
}
