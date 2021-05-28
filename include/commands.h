/*
** EPITECH PROJECT, 2019
** commands
** File description:
** commands
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "server.h"
#include "commons.h"

#define COMMANDS 6

typedef int (*cmd_func)(server_t *, request_t *, int);

typedef struct command_t {
    int cmd_type;
    cmd_func f;
} command_t;

int cmd_logout(server_t *server, request_t *req, int fd);
int cmd_login(server_t *server, request_t *req, int fd);
int cmd_create(server_t *server, request_t *req, int fd);
int cmd_users(server_t *server, request_t *req, int fd);
int cmd_user(server_t *server, request_t *req, int fd);
int cmd_send(server_t *server, request_t *req, int fd);

static const command_t cmd_table[COMMANDS] = {
    { CT_LOGIN, cmd_login },
    { CT_LOGOUT, cmd_logout },
    { CT_CREATE, cmd_create},
    { CT_USERS, cmd_users},
    { CT_USER, cmd_user},
    { CT_SEND, cmd_send},
};

#endif //COMMANDS_H
