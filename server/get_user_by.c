/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/server.h"
#include <string.h>
#include <sys/queue.h>

user_t *get_user_by_uuid(server_t *server, const char *uuid)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (strcmp(user->info->user_uuid, uuid) == 0) {
            return user;
        }
    }
    server_debug_print(WARNING, "There is no user existing with that uuid");
    return NULL;
}

user_t *get_user_by_name(server_t *server, const char *name)
{
    user_t *user = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (strcmp(user->info->user_name, name) == 0) {
            return user;
        }
    }
    server_debug_print(WARNING, "There is no user existing with that name");
    return NULL;
}

user_t *get_user_by_fd(server_t *server, int fd)
{
    user_t *user = NULL;
    user_fds_t *fds = NULL;

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        TAILQ_FOREACH(fds, &user->user_fds_head, next) {
            if (fds->fd == fd)
                return user;
        }
    }
    server_debug_print(WARNING, "There is no user existing with that fd");
    return NULL;
}
