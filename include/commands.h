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

#define COMMANDS 10

typedef int (*cmd_func)(server_t *, request_t *, int);

typedef struct command_t {
    int cmd_type;
    cmd_func f;
} command_t;

void send_error_response(server_t *server, request_t *req, int fd);
int create_new_team(server_t *server, request_t *req, int fd);
void create_new_channel(server_t *server, request_t *req, int fd);
void create_new_thread(server_t *server, request_t *req, int fd);
int cmd_login_error(server_t *server, int fd);
bool cmd_login_check_existing_fd(server_t *server, int fd);
bool create_new_channel_is_authorized(team_t *team, const char *user_uuid);
bool if_user_exists(server_t *server, const char *name);
int cmd_logout(server_t *server, request_t *req, int fd);
int cmd_login(server_t *server, request_t *req, int fd);
int cmd_create(server_t *server, request_t *req, int fd);
int cmd_users(server_t *server, request_t *req, int fd);
int cmd_user(server_t *server, request_t *req, int fd);
int cmd_send(server_t *server, request_t *req, int fd);
int cmd_messages(server_t *server, request_t *req, int fd);
int cmd_subscribe(server_t *server, request_t *req, int fd);
int cmd_unsubscribe(server_t *server, request_t *req, int fd);
int cmd_list(server_t *server, request_t *req, int fd);

static const command_t cmd_table[COMMANDS] = {
    { CT_LOGIN, cmd_login },
    { CT_LOGOUT, cmd_logout },
    { CT_CREATE, cmd_create},
    { CT_USERS, cmd_users},
    { CT_USER, cmd_user},
    { CT_SEND, cmd_send},
    { CT_MESSAGES, cmd_messages},
    { CT_SUBSCRIBE, cmd_subscribe},
    { CT_UNSUBSCRIBE, cmd_unsubscribe},
    { CT_LIST, cmd_list}
};

#endif //COMMANDS_H
