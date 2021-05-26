/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"

int cmd_user(server_t *server, request_t *req, int fd)
{
    response_t r;

    r.request_type = USERS;
    r.status_code = STATUS_OK;

    // i have no idea where to put the information
    /* @todo implement this ... :^) */

    send(fd, &r, RESPONSE_SIZE, 0);
    return SUCCESS;
}
