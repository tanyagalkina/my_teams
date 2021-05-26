/*
** EPITECH PROJECT, 2020
** commands
** File description:
** cmd_create
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"
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

    r.request_type = USERS;
    r.status_code = STATUS_OK;
    r.extern_body_size = how_many_users(server);
    r.extern_body_type = USER_TYPE;
    send(fd, &r, RESPONSE_SIZE, 0);
}

static void send_response(server_t *server, int fd)
{
    user_t *user = NULL;
    response_t r;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        r.status_code = STATUS_OK;
        strcpy(r.name, user->info->user_name);
        send(fd, &r, RESPONSE_SIZE, 0);
    }
}

int cmd_users(server_t *server, request_t *req, int fd)
{
    send_status(server, fd);
    send_response(server, fd);
    return SUCCESS;
}
