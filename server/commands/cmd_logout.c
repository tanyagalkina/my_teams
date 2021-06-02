/*
** EPITECH PROJECT, 2019
** handle_connection
** File description:
** handle_connection
*/

#include "../../include/server.h"
#include "../../include/commons.h"
#include "../../libs/myteams/logging_server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

static void send_response(int fd)
{
    response_t r;
    r.request_type = CT_LOGOUT;
    r.status_code = STATUS_OK;
    send(fd, &r, RESPONSE_SIZE, 0);
}

static void send_event(server_t *server, int fd)
{
    user_t *user = NULL;
    response_t r;
    user_fds_t *fds = NULL;

    r.request_type = ET_LOGGED_OUT;
    r.status_code = STATUS_OK;
    strcpy(r.user_uuid, get_user_by_fd(server, fd)->info->user_uuid);
    strcpy(r.name, get_user_by_fd(server, fd)->info->user_name);
    TAILQ_FOREACH(user, &server->admin->user_head, next) {
        if (user->info->user_status == US_LOGGED_IN) {
            TAILQ_FOREACH(fds, &user->user_fds_head, next) {
                send(fds->fd, &r, RESPONSE_SIZE, 0);}}}}

static bool is_still_logged_in(user_t *user)
{
    return !TAILQ_EMPTY(&user->user_fds_head);
}

int cmd_logout(server_t *server, request_t *req, int fd)
{
    user_t *user = NULL;
    user_fds_t *fds = NULL;
    user_fds_t *cp_fds = NULL;

    if ((user = get_user_by_fd(server, fd)) == NULL)
        return FAILURE;
    send_event(server, fd);
    send_response(fd);
    TAILQ_FOREACH(fds, &user->user_fds_head, next) {
        if (fds->fd == fd) {
            cp_fds = fds;
        }
    }
    TAILQ_REMOVE(&user->user_fds_head, cp_fds, next);
    if (!is_still_logged_in(user)) {
        user->info->user_status = US_LOGGED_OUT;
    }
    server_event_user_logged_out(user->info->user_uuid);
    return SUCCESS;
}