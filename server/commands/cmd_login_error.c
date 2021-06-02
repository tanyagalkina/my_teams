/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../../include/commons.h"
#include "../../include/server.h"
#include "../../libs/myteams/logging_server.h"

bool cmd_login_check_existing_fd(server_t *server, int fd)
{
    user_t *user;
    user_fds_t *fds;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            if (fds->fd == fd)
                return true;
        }
    }
    return false;
}

int cmd_login_error(server_t *server, int fd)
{
    server_debug_print(ERROR, "todo_done?\n");
    error_already_exist(get_user_by_fd(server, fd));
    return SUCCESS;
}