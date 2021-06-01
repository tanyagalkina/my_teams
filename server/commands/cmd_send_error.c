/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include <string.h>

void send_error_response(server_t *server, request_t *req, int fd)
{
    response_t r;
    user_fds_t *fds;

    r.request_type = CT_SEND;
    r.status_code = KO_UNKN_USER;
    strcpy(r.user_uuid, req->user_uuid);
    send(fd, &r, RESPONSE_SIZE, 0);
}
