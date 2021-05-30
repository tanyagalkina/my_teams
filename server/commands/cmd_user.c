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
#include <stdio.h>
#include <sys/queue.h>

static void cmd_user_error(server_t *server, request_t *req, int fd)
{
    response_t r;
    user_fds_t *fds;

    r.request_type = CT_USER;
    r.status_code = KO_UNKN_USER;
    strcpy(r.user_uuid, req->user_uuid);
    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
}

int cmd_user(server_t *server, request_t *req, int fd)
{
    response_t r;
    user_fds_t *fds;

    if (get_user_by_uuid(server, req->user_uuid) == NULL) {
        cmd_user_error(server, req, fd);
        return SUCCESS;
    }
    r.request_type = CT_USER;
    r.status_code = STATUS_OK;
    strcpy(r.user_uuid, get_user_by_fd(server, fd)->info->user_uuid);
    TAILQ_FOREACH(fds, &get_user_by_fd(server, fd)->user_fds_head, next) {
        send(fds->fd, &r, RESPONSE_SIZE, 0);
    }
    return SUCCESS;
}
