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

static void cmd_user_error(server_t *server, request_t *req, int fd)
{
    response_t r;

    r.request_type = CT_USER;
    r.status_code = KO_UNKN_USER;
    strcpy(r.user_uuid, req->user_uuid);
    send(fd, &r, RESPONSE_SIZE, 0);
}

int cmd_user(server_t *server, request_t *req, int fd)
{
    response_t r;

    if (get_user_by_uuid(server, req->user_uuid) == NULL) {
        cmd_user_error(server, req, fd);
        return SUCCESS;
    }

    r.request_type = CT_USER;
    r.status_code = STATUS_OK;

    strcpy(r.user_uuid, get_user_by_fd(server, fd)->info->user_uuid);
    send(fd, &r, RESPONSE_SIZE, 0);
    return SUCCESS;
}
