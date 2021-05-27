/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../include/server.h"
#include "../include/commons.h"
#include "../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

static void send_response(server_t *server, int fd)
{
    user_t *user;
    response_t r;

    r.request_type = ET_LOGGED_OUT;
    r.status_code = STATUS_OK;
    strcpy(r.user_uuid, get_user_by_fd(server, fd)->info->user_uuid);
    strcpy(r.name, get_user_by_fd(server, fd)->info->user_name);

    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (user->info->user_status == US_LOGGED_IN) {
            for (int i = 0; i < MAX_FD_PER_USER; i++) {
                if (user->fds[i] != 0) {
                    send(user->fds[i], &r, RESPONSE_SIZE, 0);
                }
            }
        }
    }
}

static bool is_still_logged_in(user_t *user)
{
    for (int i = 0; i < MAX_FD_PER_USER; i++) {
        if (user->fds[i] != 0) {
            return true;
        }
    }
    return false;
}

int cmd_logout(server_t *server, request_t *req, int fd)
{
    user_t *user = NULL;

    if ((user = get_user_by_fd(server, fd)) == NULL)
        return FAILURE;

    send_response(server, fd);
    for (int i = 0; i < MAX_FD_PER_USER; i++) {
        if (user->fds[i] == fd) {
            user->fds[i] = 0;
        }
    }
    /*printf("name of logout: %s\n", req->name);*/
    if (!is_still_logged_in(user))
        user->info->user_status = US_LOGGED_OUT;
    server_event_user_logged_out(user->info->user_uuid);
    return SUCCESS;
}
